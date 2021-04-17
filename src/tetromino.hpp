#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>

#include "colors.hpp"

/**
 * @brief Matrix is a 2d dynamic array
 * 
 */
typedef std::vector<std::vector<bool>> Matrix;

/**
 * @brief Collection of Tetromino types
 * 
 */
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

/**
 * @brief Collection of possible Tetromino translations
 * 
 */
enum TetrominoTranslation
{
  Left = 0,
  Right,
  Down
};

/**
 * @brief Collection of possible Tetromino rotations
 * 
 */
enum TetrominoRotation
{
  CCW = 0,
  CW
};

/**
 * @brief Tetromino class
 * 
 */
class Tetromino
{
private:
  Matrix matrix_;
  int posX_, posY_;
  SDL_Color color_;

  /**
   * @brief Rotate Tetromino randomly at spawn
   * 
   */
  void setupRandomRotation();

public:
  /**
   * @brief Construct a new Tetromino object
   * 
   */
  Tetromino();

  /**
   * @brief Construct a new Tetromino object
   * 
   * @param tetroType 
   */
  Tetromino(TetrominoType tetroType);

  /**
   * @brief Destroy the Tetromino object
   * 
   */
  ~Tetromino();

  /**
   * @brief Get matrix
   * 
   * @return const Matrix 
   */
  const Matrix getMatrix() const;

  /**
   * @brief Get posX
   * 
   * @return int 
   */
  int getPosX() const;

  /**
   * @brief Get posY
   * 
   * @return int 
   */
  int getPosY() const;

  /**
   * @brief Get color
   * 
   * @return const SDL_Color 
   */
  const SDL_Color getColor() const;

  /**
   * @brief Get width
   * 
   * @return int 
   */
  int getWidth() const;

  /**
   * @brief Get height
   * 
   * @return int 
   */
  int getHeight() const;

  /**
   * @brief Translate tetromino
   * 
   * @param translation 
   */
  void translate(TetrominoTranslation translation);

  /**
   * @brief Rotate Tetromino
   * 
   * @param rotation 
   */
  void rotate(TetrominoRotation rotation);

  /**
   * @brief Draw Tetromino in rect
   * 
   * @param rect 
   */
  void draw(SDL_Renderer *renderer, SDL_Rect rect) const;

  /**
   * @brief Draw Tetromino as ghost in rect
   * 
   * @param rect 
   */
  void drawGhost(SDL_Renderer *renderer, SDL_Rect rect) const;
};

#endif // TETROMINO_HPP
