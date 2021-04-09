#ifndef SCORE_HPP
#define SCORE_HPP

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define FONT_SIZE 32

class Score
{
private:
  const char *score_;
  unsigned int value_;
  std::string time_;

  SDL_Color scoreColor_, valueColor_, timeColor_;
  SDL_Rect scoreRect_, valueRect_, timeRect_;
  SDL_Texture *scoreTexture_, *valueTexture_, *timeTexture_;

public:
  Score();
  ~Score();

  void init(SDL_Renderer *renderer, TTF_Font *font);
  void draw(SDL_Renderer *renderer);
};

#endif // SCORE_HPP
