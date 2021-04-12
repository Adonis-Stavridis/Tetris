#include "tetromino.hpp"

Tetromino::Tetromino(TetrominoType tetroType)
    : posX_(4),
      posY_(0)
{
  switch (tetroType)
  {
  case TetrominoType::I:
    matrix_ = {{{0, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 0, 0}}};
    color_ = Colors::tomato();
    posX_ -= 1;
    break;

  case TetrominoType::J:
    matrix_ = {{{0, 1, 0},
                {0, 1, 0},
                {1, 1, 0}}};
    color_ = Colors::orange();
    break;

  case TetrominoType::L:
    matrix_ = {{{0, 1, 0},
                {0, 1, 0},
                {0, 1, 1}}};
    color_ = Colors::dodgerblue();
    break;

  case TetrominoType::O:
    matrix_ = {{{1, 1},
                {1, 1}}};
    color_ = Colors::mediumseagreen();
    break;

  case TetrominoType::S:
    matrix_ = {{{0, 1, 1},
                {1, 1, 0},
                {0, 0, 0}}};
    color_ = Colors::slateblue();
    break;

  case TetrominoType::T:
    matrix_ = {{{1, 1, 1},
                {0, 1, 0},
                {0, 0, 0}}};
    color_ = Colors::violet();
    break;

  case TetrominoType::Z:
    matrix_ = {{{1, 1, 0},
                {0, 1, 1},
                {0, 0, 0}}};
    color_ = Colors::azure();
    break;

  default:
    std::cerr << "Tetromino Error : Unknown TetrominoType."
              << std::endl;
    exit(EXIT_FAILURE);
    break;
  }

  setupRandomRotation();
  posY_ = -setupPosY();
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
  Matrix newMatrix = matrix_;
  size_t isize = matrix_.size();
  size_t jsize = matrix_[0].size();

  switch (rotation)
  {
  case TetrominoRotation::CCW:
    for (size_t i = 0; i < isize; i++)
    {
      for (size_t j = 0; j < jsize; j++)
      {
        newMatrix[i][j] = matrix_[jsize - j - 1][i];
      }
    }
    break;

  case TetrominoRotation::CW:
    for (size_t i = 0; i < isize; i++)
    {
      for (size_t j = 0; j < jsize; j++)
      {
        newMatrix[i][j] = matrix_[j][isize - i - 1];
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

void Tetromino::setupRandomRotation()
{
  int numberRotation = rand() % 4;

  for (int i = 0; i < numberRotation; i++)
    rotate(TetrominoRotation::CW);
}

int Tetromino::setupPosY()
{
  size_t isize = matrix_.size();
  size_t jsize = matrix_[0].size();
  size_t low = 0;

  for (size_t i = isize; i-- > 0;)
  {
    for (size_t j = jsize; j-- > 0;)
    {
      if (matrix_[i][j])
      {
        low = std::max(low, j);
        break;
      }
    }
  }

  return static_cast<int>(low);
}
