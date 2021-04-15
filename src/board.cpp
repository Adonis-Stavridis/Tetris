#include "board.hpp"

Board::Board(const int windowWidth, const int windowHeight)
    : rect_({windowWidth / 2 - 160, windowHeight / 2 - 320, 320, 640}),
      fillColor_(Colors::darkgrey()),
      borderColor_(Colors::gold()),
      gridColor_(Colors::grey())
{
}

Board::~Board()
{
}

void Board::start()
{
  for (int i = 0; i < WIDTH; i++)
  {
    for (int j = 0; j < HEIGHT; j++)
    {
      grid_[i][j].unlock();
    }
  }
}

void Board::draw(SDL_Renderer *renderer, const Tetromino &tetromino)
{
  SDL_SetRenderDrawColor(renderer, fillColor_.r, fillColor_.g, fillColor_.b,
                         fillColor_.a);
  SDL_RenderFillRect(renderer, &rect_);

  const Matrix tetroMatrix = tetromino.getMatrix();
  const size_t isize = tetroMatrix.size();
  const size_t jsize = tetroMatrix[0].size();
  const int tetroPosX = tetromino.getPosX();
  const int tetroPosY = tetromino.getPosY();
  const SDL_Color tetroColor = tetromino.getColor();

  SDL_SetRenderDrawColor(renderer, tetroColor.r, tetroColor.g, tetroColor.b,
                         tetroColor.a);
  for (size_t i = 0; i < isize; i++)
  {
    for (size_t j = 0; j < jsize; j++)
    {
      int ivalue = static_cast<int>(i);
      int jvalue = static_cast<int>(j);

      int iPos = tetroPosX + ivalue;
      int jPos = tetroPosY + jvalue;

      if (jPos >= 0 && tetroMatrix[i][j])
      {
        SDL_Rect tetroRect = {rect_.x + 32 * (iPos),
                              rect_.y + 32 * (jPos),
                              32,
                              32};
        SDL_RenderFillRect(renderer, &tetroRect);
      }
    }
  }

  for (int i = 0; i < WIDTH; i++)
  {
    for (int j = 0; j < HEIGHT; j++)
    {
      if (grid_[i][j].locked())
      {
        SDL_Color gridColor = grid_[i][j].color();
        SDL_Rect gridRect = {rect_.x + 32 * i,
                             rect_.y + 32 * j,
                             32,
                             32};

        SDL_SetRenderDrawColor(renderer, gridColor.r, gridColor.g, gridColor.b,
                               gridColor.a);
        SDL_RenderFillRect(renderer, &gridRect);
      }
    }
  }

  SDL_SetRenderDrawColor(renderer, gridColor_.r, gridColor_.g, gridColor_.b,
                         gridColor_.a);
  for (int x = rect_.x + 32; x < rect_.x + rect_.w; x += 32)
  {
    SDL_RenderDrawLine(renderer, x, rect_.y, x, rect_.y + rect_.h);
  }

  SDL_SetRenderDrawColor(renderer, gridColor_.r, gridColor_.g, gridColor_.b,
                         gridColor_.a);
  for (int y = rect_.y + 32; y < rect_.y + rect_.h; y += 32)
  {
    SDL_RenderDrawLine(renderer, rect_.x, y, rect_.x + rect_.w, y);
  }

  SDL_SetRenderDrawColor(renderer, borderColor_.r, borderColor_.g,
                         borderColor_.b, borderColor_.a);
  SDL_RenderDrawRect(renderer, &rect_);
}

bool Board::collision(const Tetromino &tetromino)
{
  const Matrix tetroMatrix = tetromino.getMatrix();
  const size_t isize = tetroMatrix.size();
  const size_t jsize = tetroMatrix[0].size();
  const int tetroPosX = tetromino.getPosX();
  const int tetroPosY = tetromino.getPosY();

  for (size_t i = 0; i < isize; i++)
  {
    for (size_t j = 0; j < jsize; j++)
    {
      int ivalue = static_cast<int>(i);
      int jvalue = static_cast<int>(j);

      int iPos = tetroPosX + ivalue;
      int jPos = tetroPosY + jvalue;

      if (tetroMatrix[i][j] && (iPos < 0 || iPos >= WIDTH || jPos >= HEIGHT ||
                                (jPos >= 0 && grid_[iPos][jPos].locked())))
        return true;
    }
  }

  return false;
}

bool Board::lockable(const Tetromino &tetromino)
{
  const Matrix tetroMatrix = tetromino.getMatrix();
  const size_t isize = tetroMatrix.size();
  const size_t jsize = tetroMatrix[0].size();
  const int tetroPosX = tetromino.getPosX();
  const int tetroPosY = tetromino.getPosY();

  for (size_t i = 0; i < isize; i++)
  {
    for (size_t j = 0; j < jsize; j++)
    {
      int ivalue = static_cast<int>(i);
      int jvalue = static_cast<int>(j);

      int iPos = tetroPosX + ivalue;
      int jPos = tetroPosY + jvalue;

      if (tetroMatrix[i][j] && (jPos >= HEIGHT ||
                                (jPos >= 0 && grid_[iPos][jPos].locked())))
        return true;
    }
  }

  return false;
}

int Board::lock(const Tetromino &tetromino)
{
  const Matrix tetroMatrix = tetromino.getMatrix();
  const size_t isize = tetroMatrix.size();
  const size_t jsize = tetroMatrix[0].size();
  const int tetroPosX = tetromino.getPosX();
  const int tetroPosY = tetromino.getPosY();
  const SDL_Color tetroColor = tetromino.getColor();

  std::set<int> changedLines;

  for (size_t i = 0; i < isize; i++)
  {
    for (size_t j = 0; j < jsize; j++)
    {
      int ivalue = static_cast<int>(i);
      int jvalue = static_cast<int>(j);

      int iPos = tetroPosX + ivalue;
      int jPos = tetroPosY + jvalue;

      if (tetroMatrix[i][j])
      {
        if (jPos < 0)
          return -1;

        grid_[iPos][jPos].lock(tetroColor);
        changedLines.insert(jPos);
      }
    }
  }

  return checkLines(changedLines);
}

uint Board::checkLines(std::set<int> changedLines)
{
  uint rmLines = 0;

  for (int line : changedLines)
  {
    bool skip = false;

    for (int i = 0; i < WIDTH; i++)
    {
      if (!grid_[i][line].locked())
        skip = true;
    }

    for (int i = 0; i < WIDTH && !skip; i++)
    {
      for (int j = line; j > 0; j--)
      {
        if (grid_[i][j - 1].locked())
          grid_[i][j].lock(grid_[i][j - 1].color());
        else
          grid_[i][j].unlock();
      }
    }

    if (!skip)
      rmLines += 1;
  }

  return rmLines;
}
