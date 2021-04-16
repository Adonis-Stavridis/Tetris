#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <set>

#include <SDL2/SDL.h>

#include "colors.hpp"
#include "tetromino.hpp"
#include "grid.hpp"

#define WIDTH 10
#define HEIGHT 20

class Board
{
private:
  SDL_Rect rect_;
  SDL_Color fillColor_;
  SDL_Color borderColor_;
  SDL_Color gridColor_;

  SDL_Rect rect2_;
  SDL_Rect rect3_;

  Grid<GridRect, WIDTH, HEIGHT> grid_;

  uint checkLines(std::set<int> changedLines);

public:
  Board(const int windowWidth, const int windowHeight);
  ~Board();

  void start();
  void draw(SDL_Renderer *renderer, const Tetromino &tetromino,
            const Tetromino &ghost);
  bool collision(const Tetromino &tetromino);
  bool lockable(const Tetromino &tetromino);
  int lock(const Tetromino &tetromino);
};

#endif // BOARD_HPP
