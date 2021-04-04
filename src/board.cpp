#include "board.hpp"

Board::Board(const int windowWidth, const int windowHeight)
    : rect_({windowWidth / 2 - 160, windowHeight / 2 - 320, 320, 640}),
      fillColor_({0x40, 0x40, 0x40, 0xFF}),
      borderColor_({0xFF, 0xD7, 0x00, 0xFF}),
      gridColor_({0x80, 0x80, 0x80, 0xFF})
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

  SDL_SetRenderDrawColor(renderer_, gridColor_.r, gridColor_.g, gridColor_.b, gridColor_.a);
  for (int x = rect_.x + 32; x < rect_.x + rect_.w; x += 32)
  {
    SDL_RenderDrawLine(renderer_, x, rect_.y, x, rect_.y + rect_.h);
  }
  
  SDL_SetRenderDrawColor(renderer_, gridColor_.r, gridColor_.g, gridColor_.b, gridColor_.a);
  for (int y = rect_.y + 32; y < rect_.y + rect_.h; y += 32)
  {
    SDL_RenderDrawLine(renderer_, rect_.x, y, rect_.x + rect_.w, y);
  }

  SDL_SetRenderDrawColor(renderer_, borderColor_.r, borderColor_.g,
                         borderColor_.b, borderColor_.a);
  SDL_RenderDrawRect(renderer_, &rect_);
}

void Board::initBoard()
{
  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 20; j++)
    {
      boardArray_[i][j] = 0;
    }
  }
}
