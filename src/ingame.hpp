#ifndef INGAME_HPP
#define INGAME_HPP

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "gamepage.hpp"
#include "board.hpp"
#include "score.hpp"

class Ingame : public GamePage
{
private:
  Board board_;
  Score score_;

public:
  Ingame(const int windowWidth_, const int windowHeight_);
  ~Ingame();

  void init(SDL_Renderer *renderer, TTF_Font *font);
  void draw(SDL_Renderer *renderer);
  void start();
  PageAction handleInput(SDL_Event event);
};

#endif // INGAME_HPP

// std::queue<int> updateRandomTetro();
