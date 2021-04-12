#ifndef INGAME_HPP
#define INGAME_HPP

#include <iostream>
#include <time.h>
#include <queue>
#include <chrono>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "gamepage.hpp"
#include "board.hpp"
#include "score.hpp"
#include "tetromino.hpp"

#define TETROQUEUE_SIZE 4

typedef std::chrono::_V2::system_clock::time_point TimeStamp;
typedef std::chrono::duration<double> Duration;

class Ingame : public GamePage
{
private:
  TimeStamp startTime_;
  Duration curTime_;

  int timeToFall_;
  int timeToPass_;

  Board board_;
  Score score_;

  Tetromino *curTetromino_;

  std::queue<Tetromino> tetroQueue_;

  Tetromino *initTetroQueue();
  Tetromino *getTetroQueue();
  Tetromino spawnTetromino();

  void updateTime();
  void tetroFall();

  void tetroTranslate(TetrominoTranslation translation);
  void tetroRotate(TetrominoRotation rotation);

public:
  Ingame(const int windowWidth_, const int windowHeight_);
  ~Ingame();

  void init(SDL_Renderer *renderer, TTF_Font *font);
  void draw(SDL_Renderer *renderer);
  void start();
  PageAction handleInput(SDL_Event event);
};

#endif // INGAME_HPP
