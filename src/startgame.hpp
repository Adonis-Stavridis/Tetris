#ifndef STARTGAME_HPP
#define STARTGAME_HPP

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "gamepage.hpp"

class Startgame : public GamePage
{
private:
  const char *text_;
  SDL_Color textColor_;

  SDL_Rect textRect_;
  SDL_Texture *textTexture_;

public:
  Startgame();
  ~Startgame();

  void init(SDL_Renderer *renderer, TTF_Font *font,
            const int windowWidth, const int windowHeight);
  void draw(SDL_Renderer *renderer);
  void start();
  PageAction handleInput(SDL_Event event);
};

#endif // STARTGAME_HPP
