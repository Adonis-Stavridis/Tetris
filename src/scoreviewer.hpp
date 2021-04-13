#ifndef SCOREVIEWER_HPP
#define SCOREVIEWER_HPP

#include <iostream>
#include <chrono>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "colors.hpp"

#define FONT_SIZE 32

class ScoreViewer
{
private:
  const char *score_;
  unsigned int value_;
  std::string time_;

  SDL_Color scoreColor_, valueColor_, timeColor_;
  SDL_Rect scoreRect_, valueRect_, timeRect_;
  SDL_Texture *scoreTexture_, *valueTexture_, *timeTexture_;

  TTF_Font *font_;

  void updateScore(SDL_Renderer *renderer, uint scoreValue);
  void updateTime(SDL_Renderer *renderer,
                  std::chrono::duration<double> curTime);

public:
  ScoreViewer();
  ~ScoreViewer();

  void init(SDL_Renderer *renderer, TTF_Font *font);
  void draw(SDL_Renderer *renderer, uint scoreValue,
            std::chrono::duration<double> curTime);
  void start();
};

#endif // SCOREVIEWER_HPP
