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

void Board::lock(const Tetromino &tetromino)
{
  const Matrix tetroMatrix = tetromino.getMatrix();
  const size_t isize = tetroMatrix.size();
  const size_t jsize = tetroMatrix[0].size();
  const int tetroPosX = tetromino.getPosX();
  const int tetroPosY = tetromino.getPosY();
  const SDL_Color tetroColor = tetromino.getColor();

  for (size_t i = 0; i < isize; i++)
  {
    for (size_t j = 0; j < jsize; j++)
    {
      int ivalue = static_cast<int>(i);
      int jvalue = static_cast<int>(j);

      int iPos = tetroPosX + ivalue;
      int jPos = tetroPosY + jvalue;

      if (tetroMatrix[i][j])
        grid_[iPos][jPos].lock(tetroColor);
    }
  }
}

// /***** Draw the spawn window *****/
// // The left window for the current tetromino

// // Draw the window
// SDL_SetRenderDrawColor(renderer, fillColor_.r, fillColor_.g, fillColor_.b,
//                        fillColor_.a);

// rect2_ = rect_;
// rect2_.x -= 225;
// rect2_.w = 200;
// rect2_.h = 200;
// SDL_RenderFillRect(renderer, &rect2_);

// // Draw the lines for the grid
// // Value 50 is the size of the cell for the left window maybe
// //--> maybe create a variable CELL to use and modify for each rectangle
// SDL_SetRenderDrawColor(renderer, borderColor_.r, borderColor_.g,
//                        borderColor_.b, borderColor_.a);
// SDL_RenderDrawRect(renderer, &rect2_);

// SDL_SetRenderDrawColor(renderer, gridColor_.r, gridColor_.g, gridColor_.b,
//                        gridColor_.a);

// for (int x = rect2_.x + 50; x < rect2_.x + rect2_.w; x += 50)
// {
//   SDL_RenderDrawLine(renderer, x, rect2_.y, x, rect2_.y + rect2_.h);
// }

// SDL_SetRenderDrawColor(renderer, gridColor_.r, gridColor_.g, gridColor_.b,
//                        gridColor_.a);

// for (int y = rect2_.y + 50; y < rect2_.y + rect2_.h; y += 50)
// {
//   SDL_RenderDrawLine(renderer, rect2_.x, y, rect2_.x + rect2_.w, y);
// }

// /***** Draw the spawn window for the next fourth tetromino *****/
// // Draw the window
// SDL_SetRenderDrawColor(renderer, fillColor_.r, fillColor_.g, fillColor_.b,
//                        fillColor_.a);
// rect3_ = rect_;
// rect3_.x += rect_.w + 50;
// rect3_.w = 192; //initially 160 but 192 fit more cause 6 col --> better renderer
// SDL_RenderFillRect(renderer, &rect3_);

// SDL_SetRenderDrawColor(renderer, borderColor_.r, borderColor_.g,
//                        borderColor_.b, borderColor_.a);
// SDL_RenderDrawRect(renderer, &rect3_);

// // Draw the lines for the grid
// SDL_SetRenderDrawColor(renderer, gridColor_.r, gridColor_.g, gridColor_.b,
//                        gridColor_.a);
// for (int x = rect3_.x + 32; x < rect3_.x + rect3_.w; x += 32)
// {
//   SDL_RenderDrawLine(renderer, x, rect3_.y, x, rect3_.y + rect3_.h);
// }

// SDL_SetRenderDrawColor(renderer, gridColor_.r, gridColor_.g, gridColor_.b,
//                        gridColor_.a);
// for (int y = rect3_.y + 32; y < rect3_.y + rect3_.h; y += 32)
// {
//   SDL_RenderDrawLine(renderer, rect3_.x, y, rect3_.x + rect3_.w, y);
// }

// //Tmp is use here to draw the tetromino
// //We won't modify the original queue here
// std::queue<int> tmp = randomTetromino_;

// //To jump the fist line to have a spacing with the border for the right window
// int spaceLine = 64;

// //To do not erase the x and y because at each iteration it's modifying
// int tmpx, tmpy;
// tmpx = rect2_.x;
// tmpy = rect2_.y;

// //First tetromino -> left window
// drawTetrominoSpawn(renderer, tmp.front(), true, spaceLine, tmpx, tmpy);
// tmp.pop();

// //To do not erase the x and y because at each iteration it's modifying
// tmpx = rect3_.x;
// tmpy = rect3_.y;
// //Fourth others tetromino -> right winodw
// while (!tmp.empty())
// {
//   drawTetrominoSpawn(renderer, tmp.front(), false, spaceLine, tmpx, tmpy);
//   tmp.pop();
//   //To jump 2 lines between 2 tetrominos
//   spaceLine += 128;
// }

// void Board::drawTetrominoSpawn(SDL_Renderer *renderer, int nbTypeTetro,
//                                bool b, int spaceLine, int tmpx, int tmpy)
// {
//   //  4 is the size of the matrix of the structure tetro
//   // --> we could replace 4 by the size
//   for (int i = 0; i < 4; i++)
//   {
//     for (int j = 0; j < 4; j++)
//     {
//       //If 1 we draw a square
//       if (tab[nbTypeTetro].matrix[i][j] == 1)
//       {
//         // boolean to know if we are on the left or right window
//         // for height and width we do -1 to know draw on the golden lines of the grid
//         // for the y : 50 is the cell size and 51 is to jump of one row to center the tetromino
//         if (b == true)
//         {
//           rect2_.x = tmpx;
//           rect2_.y = tmpy;
//           rect2_.y = rect2_.y + i * 50 + 51;
//           rect2_.w = 50 - 1;
//           rect2_.h = 50 - 1;

//           // To center the type one of tetromino : the yellow square
//           // for the x : 50 is the cell size and 51 is to shift of one column to center the tetromino
//           if (nbTypeTetro == 1)
//           {
//             rect2_.x = rect2_.x + j * 50 + 51;
//           }
//           else
//           {
//             rect2_.x = rect2_.x + j * 50 + 1;
//           }
//         }
//         // right window, 32 is the size of cell
//         // it's the same thing just we add spaceLine for the y to jump more rows
//         else
//         {
//           rect3_.x = tmpx + 32;
//           rect3_.y = tmpy;
//           rect3_.y = rect3_.y + i * 32 + spaceLine + 1;
//           rect3_.w = 32 - 1;
//           rect3_.h = 32 - 1;

//           if (nbTypeTetro == 1)
//           {
//             rect3_.x = rect3_.x + j * 32 + 33;
//           }
//           else
//           {
//             rect3_.x = rect3_.x + j * 32 + 1;
//           }
//         }
//         SDL_SetRenderDrawColor(renderer, tab[nbTypeTetro].tetrominoColor.r,
//                                tab[nbTypeTetro].tetrominoColor.g,
//                                tab[nbTypeTetro].tetrominoColor.b,
//                                tab[nbTypeTetro].tetrominoColor.a);

//         if (b == true)
//           SDL_RenderFillRect(renderer, &rect2_);
//         else
//           SDL_RenderFillRect(renderer, &rect3_);
//       }
//     }
//   }
// }
