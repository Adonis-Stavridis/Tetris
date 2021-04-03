#ifndef SCORE_HPP
#define SCORE_HPP

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define FONT_SIZE 32

class Score
{
private:
  unsigned int value_;

  const char *text_;
  SDL_Color textColor_, valueColor_;

  SDL_Rect textRect_, valueRect_;
  SDL_Texture *textTexture_, *valueTexture_;

public:
  Score();
  ~Score();

  void init(SDL_Renderer *renderer, TTF_Font *font);
  void draw(SDL_Renderer *renderer);
};

#endif // SCORE_HPP
