#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <set>

#include <SDL2/SDL.h>

#include "colors.hpp"
#include "tetromino.hpp"

#define WIDTH 10
#define HEIGHT 20

struct GridRect
{
  bool set_;
  SDL_Color color_;

  GridRect()
  {
    set_ = false;
  }

  bool locked()
  {
    return set_;
  }

  SDL_Color color()
  {
    return color_;
  }

  void lock(SDL_Color color)
  {
    set_ = true;
    color_ = color;
  }

  void unlock()
  {
    set_ = false;
  }
};

class Board
{
private:
  SDL_Rect rect_;
  SDL_Color fillColor_;
  SDL_Color borderColor_;
  SDL_Color gridColor_;

  SDL_Rect rect2_;
  SDL_Rect rect3_;

  GridRect grid_[WIDTH][HEIGHT];

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
