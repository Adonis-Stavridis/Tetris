#ifndef BOARD_HPP
#define BOARD_HPP

#include <SDL2/SDL.h>
#include <iostream>

#include "colors.hpp"

#define WIDTH 10
#define HEIGHT 22
#define VHEIGHT 20

class Board
{
private:
  SDL_Rect rect_;
  SDL_Color fillColor_;
  SDL_Color borderColor_;
  SDL_Color gridColor_;

  SDL_Rect rect2_;
  SDL_Rect rect3_;

  uint board_[WIDTH][HEIGHT];

public:
  Board(const int windowWidth, const int windowHeight);
  ~Board();

  void draw(SDL_Renderer *renderer);
};

#endif // BOARD_HPP

// //A METTRE DANS UNE AUTRE CLASSE
// struct tetromino
// {
//   int matrix[4][4];
//   SDL_Color tetrominoColor;
// };

// tetromino tab[7] =
//     {
//         {
//             {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
//             {0x00, 0xFF, 0xFF, 0xFF},
//         },
//         {{{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
//          {0xFF, 0xFF, 0x0, 0xFF}},
//         {{{1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
//          {0x8B, 0x00, 0x8B, 0xFF}},
//         {{{1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
//          {0xFF, 0x8C, 0x00, 0xFF}},
//         {{{1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
//          {0x00, 0x00, 0xFF, 0xFF}},
//         {{{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
//          {0xFF, 0x00, 0x00, 0xFF}},
//         {{{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
//          {0x00, 0xFF, 0x00, 0xFF}}};

// void drawTetrominoSpawn(SDL_Renderer *renderer_, int k, bool b,
//                         int spaceLine, int x, int y);
// // A METTRE DANS UNE AUTRE CLASSE
// std::queue<int> randomTetromino_;
