#include "ingame.hpp"

Ingame::Ingame(const int windowWidth, const int windowHeight)
    : startTime_(std::chrono::system_clock::now()),
      curTime_(std::chrono::system_clock::now() - startTime_),
      timeToFall_(1000),
      timeToPass_(timeToFall_),
      endgame_(false),
      lineClear_(0),
      level_(0),
      score_(0),
      board_(Board(windowWidth, windowHeight)),
      scoreViewer_(ScoreViewer()),
      queueViewer_(QueueViewer(windowWidth)),
      curTetromino_(nullptr),
      ghostTetromino_(Tetromino()),
      curMusic_(0)
{
}

Ingame::~Ingame()
{
  for (Mix_Music *music : music_)
    Mix_FreeMusic(music);
}

void Ingame::init(SDL_Renderer *renderer, TTF_Font *font)
{
  srand(time(NULL));

  scoreViewer_.init(renderer, font);
  queueViewer_.init(renderer, font);

  music_[0] = Music::load("axel_f");
  music_[1] = Music::load("blue");
  music_[2] = Music::load("bohemian_rhapsody");
  music_[3] = Music::load("harder_better_faster_stronger");
  music_[4] = Music::load("rasputin");

  for (int i = 0; i < MUSIC_NUMBER; i++)
  {
    if (!music_[i])
    {
      std::cerr << "Mix_LoadMUS failed!" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
}

PageAction Ingame::draw(SDL_Renderer *renderer)
{
  updateTime();
  tetroFall();

  board_.draw(renderer, *curTetromino_, ghostTetromino_);
  scoreViewer_.draw(renderer);
  queueViewer_.draw(renderer);

  if (endgame_)
    return PageAction::NextPage;

  if (!Mix_PlayingMusic())
    playMusic();

  return PageAction::None;
}

void Ingame::start()
{
  board_.start();

  startTime_ = std::chrono::system_clock::now();
  curTime_ = std::chrono::system_clock::now() - startTime_;

  timeToFall_ = 1000;
  timeToPass_ =
      std::chrono::duration_cast<std::chrono::milliseconds>(curTime_).count() +
      timeToFall_;

  endgame_ = false;

  lineClear_ = 0;
  level_ = 0;
  score_ = 0;

  curTetromino_ = initTetroQueue();
  updateGhost();

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(music_.begin(), music_.end(), std::default_random_engine(seed));

  curMusic_ = 0;

  scoreViewer_.updateTime(curTime_);
  scoreViewer_.updateScore(score_);
  scoreViewer_.updateLevel(level_);
  scoreViewer_.updateLines(lineClear_);

  playMusic();
}

PageAction Ingame::handleInput(SDL_Event event)
{
  if (event.type == SDL_KEYDOWN)
  {
    switch (event.key.keysym.sym)
    {
    case SDLK_LEFT:
      tetroTranslate(TetrominoTranslation::Left);
      updateGhost();
      break;

    case SDLK_RIGHT:
      tetroTranslate(TetrominoTranslation::Right);
      updateGhost();
      break;

    case SDLK_DOWN:
      tetroTranslate(TetrominoTranslation::Down);
      break;

    case SDLK_UP:
      hardDrop();
      break;

    case SDLK_z:
      tetroRotate(TetrominoRotation::CCW);
      updateGhost();
      break;

    case SDLK_x:
      tetroRotate(TetrominoRotation::CW);
      updateGhost();
      break;

    case SDLK_SPACE:
      hardDrop();
      break;

    case SDLK_ESCAPE:
      return PageAction::Quit;
      break;

    default:
      break;
    }
  }

  return PageAction::None;
}

Tetromino *Ingame::initTetroQueue()
{
  std::queue<Tetromino> tempQueue;

  for (int i = 0; i < TETROQUEUE_SIZE; i++)
    tempQueue.push(spawnTetromino());

  tetroQueue_.swap(tempQueue);

  queueViewer_.updateQueue(tetroQueue_);

  return &tetroQueue_.front();
}

Tetromino *Ingame::getTetroQueue()
{
  tetroQueue_.pop();
  tetroQueue_.push(spawnTetromino());

  queueViewer_.updateQueue(tetroQueue_);

  return &tetroQueue_.front();
}

Tetromino Ingame::spawnTetromino()
{
  TetrominoType tetroType =
      static_cast<TetrominoType>(rand() % TetrominoType::num);

  Tetromino newTetro = Tetromino(tetroType);

  if (board_.collision(newTetro))
    endgame_ = true;

  return newTetro;
}

void Ingame::updateTime()
{
  curTime_ = std::chrono::system_clock::now() - startTime_;

  scoreViewer_.updateTime(curTime_);
}

void Ingame::tetroFall()
{
  int tempTime =
      std::chrono::duration_cast<std::chrono::milliseconds>(curTime_).count();

  if (tempTime > timeToPass_)
  {
    timeToPass_ += timeToFall_;
    tetroTranslate(TetrominoTranslation::Down);
  }
}

void Ingame::tetroTranslate(TetrominoTranslation translation)
{
  Tetromino tempTetro = *curTetromino_;

  tempTetro.translate(translation);

  if (!board_.collision(tempTetro))
    *curTetromino_ = tempTetro;

  if (translation == TetrominoTranslation::Down && board_.lockable(tempTetro))
  {
    tetroLock();
  }
}

void Ingame::tetroRotate(TetrominoRotation rotation)
{
  Tetromino tempTetro = *curTetromino_;

  tempTetro.rotate(rotation);
  if (!board_.collision(tempTetro))
    *curTetromino_ = tempTetro;
}

void Ingame::tetroLock()
{
  int lines = board_.lock(*curTetromino_);
  if (lines < 0)
    endgame_ = true;
  else
  {
    updateScore(lines);
    curTetromino_ = getTetroQueue();
    updateGhost();
  }
}

void Ingame::updateGhost()
{
  Tetromino tempTetro = *curTetromino_;
  Tetromino prevTetro = tempTetro;

  tempTetro.translate(TetrominoTranslation::Down);

  while (!board_.collision(tempTetro))
  {
    prevTetro = tempTetro;
    tempTetro.translate(TetrominoTranslation::Down);
  }

  ghostTetromino_ = prevTetro;
}

void Ingame::hardDrop()
{
  *curTetromino_ = ghostTetromino_;
  tetroLock();
}

void Ingame::updateScore(uint lines)
{
  const uint scorePerLine[5] = {0, 40, 100, 300, 1200};

  score_ += scorePerLine[lines] * (level_ + 1);

  lineClear_ += lines;

  uint currentLevel = level_;
  level_ = lineClear_ / 10;

  if (level_ > currentLevel)
  {
    timeToFall_ -= 100;
  }

  scoreViewer_.updateScore(score_);
  scoreViewer_.updateLevel(level_);
  scoreViewer_.updateLines(lineClear_);
}

void Ingame::playMusic()
{
  Music::play(music_[curMusic_], false);
  curMusic_ = (curMusic_ + 1) % MUSIC_NUMBER;
}
