#ifndef BOARD_HPP
#define BOARD_HPP

#include <SDL2/SDL.h>

class Board
{
private:
  SDL_Rect rect_;
  SDL_Color color_;
  SDL_Color border_;
  SDL_Color line_;

public:
  Board(const int windowWidth, const int windowHeight);
  ~Board();

  void draw(SDL_Renderer *renderer_);
};

#endif // BOARD_HPP
