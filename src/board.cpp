#include "board.hpp"

Board::Board(const int windowWidth, const int windowHeight)
    : rect_({50, 50, windowWidth - 100, windowHeight - 100}),
      color_({0x80, 0x80, 0x80, 0xFF})
{
}

Board::~Board()
{
}

void Board::draw(SDL_Renderer *renderer_)
{
  SDL_SetRenderDrawColor(renderer_, color_.r, color_.g, color_.b, color_.a);
  SDL_RenderFillRect(renderer_, &rect_);
}
