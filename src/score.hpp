#ifndef SCORE_HPP
#define SCORE_HPP

#include <iostream>
#include <chrono>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define FONT_SIZE 32

class Score
{
private:
  const char *score_;
  unsigned int value_;
  std::string time_;
  std::chrono::_V2::system_clock::time_point startTime_;

  SDL_Color scoreColor_, valueColor_, timeColor_;
  SDL_Rect scoreRect_, valueRect_, timeRect_;
  SDL_Texture *scoreTexture_, *valueTexture_, *timeTexture_;

  TTF_Font *font_;

  void updateTime(SDL_Renderer *renderer);

public:
  Score();
  ~Score();

  void init(SDL_Renderer *renderer, TTF_Font *font);
  void draw(SDL_Renderer *renderer);
  void start();
};

#endif // SCORE_HPP
