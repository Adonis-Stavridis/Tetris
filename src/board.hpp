#ifndef BOARD_HPP
#define BOARD_HPP

#include <SDL2/SDL.h>

class Board
{
private:
  SDL_Rect rect_;
  SDL_Color fillColor_;
  SDL_Color borderColor_;
  SDL_Color line_;

  int boardArray_[10][20];

public:
  Board(const int windowWidth, const int windowHeight);
  ~Board();

  void draw(SDL_Renderer *renderer_);
  void initBoard();
};

#endif // BOARD_HPP
