#include "ingame.hpp"

Ingame::Ingame(const int windowWidth_, const int windowHeight_)
    : startTime_(std::chrono::system_clock::now()),
      curTime_(std::chrono::system_clock::now() - startTime_),
      timeToFall_(1000),
      timeToPass_(timeToFall_),
      board_(Board(windowWidth_, windowHeight_)),
      score_(Score()),
      curTetromino_(nullptr)
{
}

Ingame::~Ingame()
{
}

void Ingame::init(SDL_Renderer *renderer, TTF_Font *font)
{
  srand(time(NULL));

  score_.init(renderer, font);
}

void Ingame::draw(SDL_Renderer *renderer)
{
  updateTime();
  tetroFall();
  board_.draw(renderer, *curTetromino_);
  score_.draw(renderer, curTime_);
}

void Ingame::start()
{
  startTime_ = std::chrono::system_clock::now();
  curTime_ = std::chrono::system_clock::now() - startTime_;

  timeToFall_ = 1000;
  timeToPass_ =
      std::chrono::duration_cast<std::chrono::milliseconds>(curTime_).count() + timeToFall_;

  curTetromino_ = initTetroQueue();
  score_.start();
}

PageAction Ingame::handleInput(SDL_Event event)
{
  if (event.type == SDL_KEYDOWN)
  {
    Tetromino tempTetro = *curTetromino_;

    switch (event.key.keysym.sym)
    {
    case SDLK_LEFT:
      tempTetro.translate(TetrominoTranslation::Left);
      if (!board_.sideCollision(tempTetro))
        *curTetromino_ = tempTetro;
      break;

    case SDLK_RIGHT:
      tempTetro.translate(TetrominoTranslation::Right);
      if (!board_.sideCollision(tempTetro))
        *curTetromino_ = tempTetro;
      break;

    case SDLK_DOWN:
      tempTetro.translate(TetrominoTranslation::Down);
      if (!board_.sideCollision(tempTetro))
        *curTetromino_ = tempTetro;
      break;

    case SDLK_z:
      tempTetro.rotate(TetrominoRotation::CCW);
      if (!board_.sideCollision(tempTetro))
        *curTetromino_ = tempTetro;
      break;

    case SDLK_x:
      tempTetro.rotate(TetrominoRotation::CW);
      if (!board_.sideCollision(tempTetro))
        *curTetromino_ = tempTetro;
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
    curTetromino_->translate(TetrominoTranslation::Down);
  }
}
