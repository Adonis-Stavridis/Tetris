#ifndef GRID_HPP
#define GRID_HPP

#include <stdlib.h>

#include <SDL2/SDL.h>

template <typename T, size_t W, size_t H>
class Grid
{
public:
  static_assert(W > 0, "Grid width must be > 0");
  static_assert(H > 0, "Grid height must be > 0");

private:
  T grid_[W][H];

public:
  inline Grid()
  {
  }

  inline ~Grid()
  {
  }

  template <typename F>
  inline void foreach (F lambda)
  {
    for (auto &row : grid_)
      for (auto &cell : row)
        lambda(cell);
  }

  inline T *operator[](size_t i)
  {
    return grid_[i];
  }
};

struct GridRect
{
  bool set_;
  SDL_Color color_;

  inline GridRect()
  {
    set_ = false;
  }

  inline bool locked()
  {
    return set_;
  }

  inline SDL_Color color()
  {
    return color_;
  }

  inline void lock(SDL_Color color)
  {
    set_ = true;
    color_ = color;
  }

  inline void unlock()
  {
    set_ = false;
  }
};

#endif // GRID_HPP
