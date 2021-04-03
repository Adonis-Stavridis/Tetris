#include "board.hpp"

Board::Board(const int windowWidth, const int windowHeight)
    : rect_({windowWidth / 2 - 200, 50, 400, windowHeight - 100}),
<<<<<<< HEAD
      color_({0x40, 0x40, 0x40, 0xFF}),
      border_({0xFF, 0xD7, 0x00, 0xFF}),
      line_({0xFF,0xFF,0xFF,0xFF})
=======
      fillColor_({0x40, 0x40, 0x40, 0xFF}),
      borderColor_({0xFF, 0xD7, 0x00, 0xFF})
>>>>>>> 16775ce9ff7960db2d49c2ceaaaa554f33bc05e1
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

  SDL_SetRenderDrawColor(renderer_, line_.r, line_.g, line_.b, line_.a);
  for (int x = rect_.x+40; x < rect_.x + rect_.w; x += 40)
  {
    SDL_RenderDrawLine(renderer_, x, rect_.y, x, rect_.y + rect_.h);
  }
  SDL_SetRenderDrawColor(renderer_, line_.r, line_.g, line_.b, line_.a);
  for (int y = rect_.y+31; y < rect_.y + rect_.h; y += 31)
  {
    SDL_RenderDrawLine(renderer_, rect_.x, y, rect_.x + rect_.w, y );
  }
}
