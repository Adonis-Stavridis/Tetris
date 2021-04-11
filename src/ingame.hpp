#ifndef INGAME_HPP
#define INGAME_HPP

#include <iostream>
#include <time.h>
#include <queue>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "gamepage.hpp"
#include "board.hpp"
#include "score.hpp"
#include "tetromino.hpp"

#define TETROQUEUE_SIZE 4

class Ingame : public GamePage
{
private:
  Board board_;
  Score score_;

  Tetromino *curTetromino_;

  std::queue<Tetromino> tetroQueue_;

  Tetromino *initTetroQueue();
  Tetromino spawnTetromino();

public:
  Ingame(const int windowWidth_, const int windowHeight_);
  ~Ingame();

  void init(SDL_Renderer *renderer, TTF_Font *font);
  void draw(SDL_Renderer *renderer);
  void start();
  PageAction handleInput(SDL_Event event);
};

#endif // INGAME_HPP

// std::queue<int> updateRandomTetro();
