#include "board.hpp"

Board::Board(const int windowWidth, const int windowHeight)
    : rect_({windowWidth / 2 - 200, 50, 400, windowHeight - 100}),
      color_({0x40, 0x40, 0x40, 0xFF}),
      border_({0xFF, 0xD7, 0x00, 0xFF})
{
}

Board::~Board()
{
}

void Board::draw(SDL_Renderer *renderer_)
{
  SDL_SetRenderDrawColor(renderer_, color_.r, color_.g, color_.b, color_.a);
  SDL_RenderFillRect(renderer_, &rect_);

  SDL_SetRenderDrawColor(renderer_, border_.r, border_.g, border_.b, border_.a);
  SDL_RenderDrawRect(renderer_, &rect_);
}
