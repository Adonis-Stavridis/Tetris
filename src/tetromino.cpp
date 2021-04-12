#include "tetromino.hpp"

Tetromino::Tetromino(TetrominoType tetroType)
    : posX_(4),
      posY_(0)
{
  switch (tetroType)
  {
  case TetrominoType::I:
    matrix_ = {{{1, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 0, 0, 0}}};
    color_ = Colors::tomato();
    break;

  case TetrominoType::J:
    matrix_ = {{{0, 1, 0, 0},
                {0, 1, 0, 0},
                {1, 1, 0, 0},
                {0, 0, 0, 0}}};
    color_ = Colors::orange();
    break;

  case TetrominoType::L:
    matrix_ = {{{1, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 1, 0, 0},
                {0, 0, 0, 0}}};
    color_ = Colors::dodgerblue();
    break;

  case TetrominoType::O:
    matrix_ = {{{1, 1, 0, 0},
                {1, 1, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0}}};
    color_ = Colors::mediumseagreen();
    break;

  case TetrominoType::S:
    matrix_ = {{{0, 1, 1, 0},
                {1, 1, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0}}};
    color_ = Colors::slateblue();
    break;

  case TetrominoType::T:
    matrix_ = {{{1, 1, 1, 0},
                {0, 1, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0}}};
    color_ = Colors::violet();
    break;

  case TetrominoType::Z:
    matrix_ = {{{1, 1, 0, 0},
                {0, 1, 1, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0}}};
    color_ = Colors::azure();
    break;

  default:
    std::cerr << "Tetromino Error : Unknown TetrominoType."
              << std::endl;
    exit(EXIT_FAILURE);
    break;
  }
}

Tetromino::~Tetromino()
{
}

Matrix Tetromino::getMatrix()
{
  return matrix_;
}

int Tetromino::getPosX()
{
  return posX_;
}

int Tetromino::getPosY()
{
  return posY_;
}

SDL_Color Tetromino::getColor()
{
  return color_;
}

void Tetromino::translate(TetrominoTranslation translation)
{
  switch (translation)
  {
  case TetrominoTranslation::Left:
    posX_--;
    break;

  case TetrominoTranslation::Right:
    posX_++;
    break;

  case TetrominoTranslation::Down:
    posY_++;
    break;

  default:
    break;
  }
}

void Tetromino::rotate(TetrominoRotation rotation)
{
  Matrix newMatrix;

  switch (rotation)
  {
  case TetrominoRotation::CCW:
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
      for (int j = 0; j < MATRIX_SIZE; j++)
      {
        newMatrix[i][j] = matrix_[MATRIX_SIZE - j - 1][i];
      }
    }
    break;

  case TetrominoRotation::CW:
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
      for (int j = 0; j < MATRIX_SIZE; j++)
      {
        newMatrix[i][j] = matrix_[j][MATRIX_SIZE - i - 1];
      }
    }
    break;

  default:
    std::cerr << "Tetromino Error : Unknown TetrominoRotation."
              << std::endl;
    exit(EXIT_FAILURE);
    break;
  }

  matrix_ = newMatrix;
}

// std::queue<int> Tetromino::randomTetromino()
// {
//   int random;
//   srand(time(NULL));
//   // Fill the queue to always see the next tetromino + actual tetromino
//   while(randomTetromino_.size() < 5)
//   {
//     std::cout << "IM IN" <Left< std::endl;
//     random = rand() % 7;
//     std::cout << random << std::endl;
//     randomTetromino_.push(random);
//   }
//   return randomTetromino_;
// }

// Tetromino::tetromino Tetromino::rotate(tetromino t)
// {
//   tetromino tmp = t;
//   for(int i = 0; i < MATRIX_SIZE; i++)
//   {
//     for(int j = 0; j < MATRIX_SIZE; j++)
//       {
//         t.matrix[j][i] = tmp.matrix[i][j];
//       }
//   }
//   return t;
// }

// void Tetromino::move(tetromino t, int x, int y)
// {
//   t.pos.first += x;
//   t.pos.second += y;
// }
