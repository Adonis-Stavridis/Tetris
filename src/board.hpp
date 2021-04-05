#ifndef BOARD_HPP
#define BOARD_HPP

#include <SDL2/SDL.h>

class Board
{
private:
  SDL_Rect rect_;
  SDL_Color fillColor_;
  SDL_Color borderColor_;
  SDL_Color gridColor_;

  SDL_Rect rect2_;
  SDL_Color cell_;
  int boardArray_[10][20];

  struct tetromino
  {
    int matrix[4][4];
  };

  tetromino tab[7] =
  {
    {
      {{1,1,1,0}
      ,{1,0,0,0}
      ,{0,0,0,0}
      ,{0,0,0,0}}
    },
    {
      {{1,1,1,1}
      ,{0,0,0,0}
      ,{0,0,0,0}
      ,{0,0,0,0}}
    },
    {
      {{1,1,0,0}
      ,{1,1,0,0}
      ,{0,0,0,0}
      ,{0,0,0,0}}
    },
    {
      {{1,1,1,0}
      ,{0,1,0,0}
      ,{0,0,0,0}
      ,{0,0,0,0}}
    },
    {
      {{1,1,1,0}
      ,{0,0,1,0}
      ,{0,0,0,0}
      ,{0,0,0,0}}
    },
    {
      {{1,1,0,0}
      ,{0,1,1,0}
      ,{0,0,0,0}
      ,{0,0,0,0}}
    },
    {
      {{0,1,1,0}
      ,{1,1,0,0}
      ,{0,0,0,0}
      ,{0,0,0,0}}
    }
  };

public:
  Board(const int windowWidth, const int windowHeight);
  ~Board();

  void draw(SDL_Renderer *renderer_);
  void draw2(SDL_Renderer *renderer_, int k);
  void initBoard();
};

#endif // BOARD_HPP
