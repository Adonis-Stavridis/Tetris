#ifndef BOARD_HPP
#define BOARD_HPP

#include <SDL2/SDL.h>

class Board
{
private:
  SDL_Rect rect_;
<<<<<<< HEAD
  SDL_Color color_;
  SDL_Color border_;
  SDL_Color line_;
=======
  SDL_Color fillColor_;
  SDL_Color borderColor_;
>>>>>>> 16775ce9ff7960db2d49c2ceaaaa554f33bc05e1

public:
  Board(const int windowWidth, const int windowHeight);
  ~Board();

  void draw(SDL_Renderer *renderer_);
};

#endif // BOARD_HPP
