#include "board.hpp"

Board::Board(const int windowWidth, const int windowHeight)
    : rect_({windowWidth / 2 - 200, 50, 400, windowHeight - 100}),
      fillColor_({0x40, 0x40, 0x40, 0xFF}),
      borderColor_({0xFF, 0xD7, 0x00, 0xFF})
{
}

Board::~Board()
{
}

void Board::draw(SDL_Renderer *renderer_)
{
  SDL_SetRenderDrawColor(renderer_, fillColor_.r, fillColor_.g, fillColor_.b,
                         fillColor_.a);
  SDL_RenderFillRect(renderer_, &rect_);

  SDL_SetRenderDrawColor(renderer_, borderColor_.r, borderColor_.g,
                         borderColor_.b, borderColor_.a);
  SDL_RenderDrawRect(renderer_, &rect_);
}
