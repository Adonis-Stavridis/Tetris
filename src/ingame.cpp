#include "ingame.hpp"

Ingame::Ingame(const int windowWidth_, const int windowHeight_)
    : startTime_(std::chrono::system_clock::now()),
      curTime_(std::chrono::system_clock::now() - startTime_),
      timeToFall_(1000),
      timeToPass_(timeToFall_),
      endgame_(false),
      lineClear_(0),
      level_(0),
      score_(0),
      board_(Board(windowWidth_, windowHeight_)),
      scoreViewer_(ScoreViewer()),
      curTetromino_(nullptr)
{
}

Ingame::~Ingame()
{
}

void Ingame::init(SDL_Renderer *renderer, TTF_Font *font)
{
  srand(time(NULL));

  scoreViewer_.init(renderer, font);
}

PageAction Ingame::draw(SDL_Renderer *renderer)
{
  updateTime();
  tetroFall();

  board_.draw(renderer, *curTetromino_);
  scoreViewer_.draw(renderer, score_, level_, curTime_);

  if (endgame_)
    return PageAction::NextPage;

  return PageAction::None;
}

void Ingame::start()
{
  startTime_ = std::chrono::system_clock::now();
  curTime_ = std::chrono::system_clock::now() - startTime_;

  timeToFall_ = 1000;
  timeToPass_ =
      std::chrono::duration_cast<std::chrono::milliseconds>(curTime_).count() + timeToFall_;

  endgame_ = false;

  lineClear_ = 0;
  level_ = 0;
  score_ = 0;

  curTetromino_ = initTetroQueue();

  board_.start();
  scoreViewer_.start();
}

PageAction Ingame::handleInput(SDL_Event event)
{
  if (event.type == SDL_KEYDOWN)
  {
    switch (event.key.keysym.sym)
    {
    case SDLK_LEFT:
      tetroTranslate(TetrominoTranslation::Left);
      break;

    case SDLK_RIGHT:
      tetroTranslate(TetrominoTranslation::Right);
      break;

    case SDLK_DOWN:
      tetroTranslate(TetrominoTranslation::Down);
      break;

    case SDLK_z:
      tetroRotate(TetrominoRotation::CCW);
      break;

    case SDLK_x:
      tetroRotate(TetrominoRotation::CW);
      break;

    case SDLK_ESCAPE:
      return PageAction::Quit;
      break;

    // ! TO REMOVE : TEMPORARY
    case SDLK_SPACE:
      return PageAction::NextPage;
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
  return &tetroQueue_.front();
}

Tetromino *Ingame::getTetroQueue()
{
  tetroQueue_.pop();
  tetroQueue_.push(spawnTetromino());

  return &tetroQueue_.front();
}

Tetromino Ingame::spawnTetromino()
{
  TetrominoType tetroType =
      static_cast<TetrominoType>(rand() % TetrominoType::num);

  return Tetromino(tetroType);
}

void Ingame::updateTime()
{
  curTime_ = std::chrono::system_clock::now() - startTime_;
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

  if (translation == TetrominoTranslation::Down &&
      board_.lockable(tempTetro))
  {
    int lines = board_.lock(*curTetromino_);
    if (lines < 0)
      endgame_ = true;
    else
    {
      updateScore(lines);
      curTetromino_ = getTetroQueue();
    }
  }
}

void Ingame::tetroRotate(TetrominoRotation rotation)
{
  Tetromino tempTetro = *curTetromino_;

  tempTetro.rotate(rotation);
  if (!board_.collision(tempTetro))
    *curTetromino_ = tempTetro;
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
}
