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
  // Draw the window of the game
  SDL_SetRenderDrawColor(renderer_, fillColor_.r, fillColor_.g, fillColor_.b,
                         fillColor_.a);
  SDL_RenderFillRect(renderer_, &rect_);

  // Draw the lines for the grid
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

  //Draw the spawn window
  SDL_SetRenderDrawColor(renderer_, fillColor_.r, fillColor_.g, fillColor_.b,
                         fillColor_.a);

  rect2_ = rect_;
  rect2_.x -= 225;
  rect2_.w = 200;
  rect2_.h = 200;
  SDL_RenderFillRect(renderer_, &rect2_);

  SDL_SetRenderDrawColor(renderer_, borderColor_.r, borderColor_.g,
                         borderColor_.b, borderColor_.a);
  SDL_RenderDrawRect(renderer_, &rect2_);

  SDL_SetRenderDrawColor(renderer_, gridColor_.r, gridColor_.g, gridColor_.b, gridColor_.a);

  for (int x = rect2_.x + 50; x < rect2_.x + rect2_.w; x += 50)
  {
    SDL_RenderDrawLine(renderer_, x, rect2_.y, x, rect2_.y + rect2_.h);
  }

  SDL_SetRenderDrawColor(renderer_, gridColor_.r, gridColor_.g, gridColor_.b, gridColor_.a);

  for (int y = rect2_.y + 50; y < rect2_.y + rect2_.h; y += 50)
  {
    SDL_RenderDrawLine(renderer_, rect2_.x, y, rect2_.x + rect2_.w, y);
  }

  draw2(renderer_, 0);
}

void Board::draw2(SDL_Renderer *renderer_, int k)
{
  int tmpx, tmpy;
  tmpx = rect2_.x;
  tmpy = rect2_.y;

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      if (tab[k].matrix[i][j] == 1)
      {
        rect2_.x = tmpx;
        rect2_.y = tmpy;
        rect2_.x = rect2_.x + j * 50 + 1;
        rect2_.y = rect2_.y + i * 50 + 51;
        rect2_.w = 50 - 1;
        rect2_.h = 50 - 1;
        SDL_SetRenderDrawColor(renderer_, tab[k].tetrominoColor.r, tab[k].tetrominoColor.g,tab[k].tetrominoColor.b, tab[k].tetrominoColor.a);
        SDL_RenderFillRect(renderer_, &rect2_);
      }
    }
  }
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
