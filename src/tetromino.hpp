#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>

#include "colors.hpp"

typedef std::vector<std::vector<bool>> Matrix;

enum TetrominoType
{
  I = 0,
  J,
  L,
  O,
  S,
  T,
  Z,
  num
};

enum TetrominoTranslation
{
  Left = 0,
  Right,
  Down
};

enum TetrominoRotation
{
  CCW = 0,
  CW
};

class Tetromino
{
private:
  Matrix matrix_;
  SDL_Color color_;
  int posX_, posY_;

  void setupRandomRotation();
  int setupPosY();

public:
  Tetromino(TetrominoType tetroType);
  ~Tetromino();

  Matrix getMatrix();
  int getPosX();
  int getPosY();
  SDL_Color getColor();

  void translate(TetrominoTranslation translation);
  void rotate(TetrominoRotation rotation);
};

#endif // TETROMINO_HPP

// std::queue<int> randomTetromino_;

// std::queue<int> randomTetromino();
// tetromino rotate(tetromino t);
// void move(tetromino t, int x, int y);
