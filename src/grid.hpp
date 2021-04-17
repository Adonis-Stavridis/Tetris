#ifndef GRID_HPP
#define GRID_HPP

#include <stdlib.h>

#include <SDL2/SDL.h>

/**
 * @brief Grid Template
 * 
 * @tparam T 
 * @tparam W 
 * @tparam H 
 */
template <typename T, size_t W, size_t H>
class Grid
{
public:
  static_assert(W > 0, "Grid width must be > 0");
  static_assert(H > 0, "Grid height must be > 0");

private:
  T grid_[W][H];

public:
  /**
   * @brief Construct a new Grid object
   * 
   */
  inline Grid()
  {
  }

  /**
   * @brief Destroy the Grid object
   * 
   */
  inline ~Grid()
  {
  }

  /**
   * @brief Call lamda function for each cell in Grid
   * 
   * @tparam F 
   * @param lambda 
   */
  template <typename F>
  inline void foreach (F lambda)
  {
    for (auto &row : grid_)
      for (auto &cell : row)
        lambda(cell);
  }

  /**
   * @brief Subscript operator overload for Gris
   * 
   * @param i 
   * @return T* 
   */
  inline T *operator[](size_t i)
  {
    return grid_[i];
  }
};

/**
 * @brief GridRect structure to represent a Tetromino square
 * 
 */
struct GridRect
{
  bool set_;
  SDL_Color color_;

  /**
   * @brief Construct a new Grid Rect object
   * 
   */
  inline GridRect()
  {
    set_ = false;
  }

  /**
   * @brief Destroy the Grid Rect object
   * 
   */
  inline ~GridRect()
  {
  }

  /**
   * @brief Returns if GridRect is locked
   * 
   * @return true 
   * @return false 
   */
  inline bool locked()
  {
    return set_;
  }

  /**
   * @brief Returns GridRect's color
   * 
   * @return SDL_Color 
   */
  inline SDL_Color color()
  {
    return color_;
  }

  /**
   * @brief Locks GridRect with color
   * 
   * @param color 
   */
  inline void lock(SDL_Color color)
  {
    set_ = true;
    color_ = color;
  }

  /**
   * @brief Unlocks GridRect
   * 
   */
  inline void unlock()
  {
    set_ = false;
  }
};

#endif // GRID_HPP
