#ifndef STARTGAME_HPP
#define STARTGAME_HPP

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Startgame
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
};

#endif // STARTGAME_HPP
