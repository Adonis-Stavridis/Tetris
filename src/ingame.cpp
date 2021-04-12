#include "ingame.hpp"

Ingame::Ingame(const int windowWidth_, const int windowHeight_)
    : startTime_(std::chrono::system_clock::now()),
      curTime_(std::chrono::system_clock::now() - startTime_),
      timeToFall_(1000),
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
  board_.draw(renderer, curTetromino_);
  score_.draw(renderer, curTime_);
}

void Ingame::start()
{
  startTime_ = std::chrono::system_clock::now();
  curTime_ = std::chrono::system_clock::now() - startTime_;

  curTetromino_ = initTetroQueue();
  score_.start();
}

PageAction Ingame::handleInput(SDL_Event event)
{
  if (event.type == SDL_KEYDOWN)
  {
    switch (event.key.keysym.sym)
    {
    case SDLK_LEFT:
      curTetromino_->translate(TetrominoTranslation::Left);
      break;

    case SDLK_RIGHT:
      curTetromino_->translate(TetrominoTranslation::Right);
      break;

    case SDLK_DOWN:
      curTetromino_->translate(TetrominoTranslation::Down);
      break;

    case SDLK_z:
      curTetromino_->rotate(TetrominoRotation::CCW);
      break;

    case SDLK_x:
      curTetromino_->rotate(TetrominoRotation::CW);
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
  static int timeToPass =
      std::chrono::duration_cast<std::chrono::milliseconds>(curTime_).count() + timeToFall_;

  int tempTime =
      std::chrono::duration_cast<std::chrono::milliseconds>(curTime_).count();

  if (tempTime > timeToPass)
  {
    timeToPass += timeToFall_;
    curTetromino_->translate(TetrominoTranslation::Down);
  }
}

// std::queue<int> Ingame::updateRandomTetro()
// {
//   int random;
//   srand(time(NULL));
//   // Fill the queue to always see the next tetromino + actual tetromino
//   while (board_.randomTetromino_.size() < 5)
//   {
//     // std::cout << "IM IN" << std::endl;
//     random = rand() % 7;
//     // std::cout << random << std::endl;
//     board_.randomTetromino_.push(random);
//   }
//   return board_.randomTetromino_;
// }
