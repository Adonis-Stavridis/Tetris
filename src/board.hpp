#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <set>

#include <SDL2/SDL.h>

#include "colors.hpp"
#include "tetromino.hpp"
#include "grid.hpp"

#define WIDTH 10
#define HEIGHT 20

/**
 * @brief Board containing locked Tetrominos
 * 
 */
class Board
{
private:
  SDL_Rect rect_;
  SDL_Color fillColor_;
  SDL_Color borderColor_;
  SDL_Color gridColor_;

  SDL_Rect rect2_;
  SDL_Rect rect3_;

  Grid<GridRect, WIDTH, HEIGHT> grid_;

  uint checkLines(std::set<int> changedLines);

public:
  /**
   * @brief Construct a new Board object
   * 
   * @param windowWidth 
   * @param windowHeight 
   */
  Board(const int windowWidth, const int windowHeight);

  /**
   * @brief Destroy the Board object
   * 
   */
  ~Board();

  /**
   * @brief Reset board
   * 
   */
  void start();

  /**
   * @brief Draw the Board's component's
   * 
   * @param renderer 
   * @param tetromino 
   * @param ghost 
   */
  void draw(SDL_Renderer *renderer, const Tetromino &tetromino,
            const Tetromino &ghost);

  /**
   * @brief Returns if there is a collision for the Tetromino
   * 
   * @param tetromino 
   * @return true 
   * @return false 
   */
  bool collision(const Tetromino &tetromino);

  /**
   * @brief Returns if a Tetromino is lockable
   * 
   * @param tetromino 
   * @return true 
   * @return false 
   */
  bool lockable(const Tetromino &tetromino);

  /**
   * @brief Locks a Tetromino to the board
   * 
   * @param tetromino 
   * @return int 
   */
  int lock(const Tetromino &tetromino);
};

#endif // BOARD_HPP
