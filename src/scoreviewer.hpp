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
  uint scoreValue_;
  const char *level_;
  uint levelValue_;
  std::string time_;

  SDL_Color scoreColor_, valueColor_, timeColor_;
  SDL_Rect scoreRect_, scoreValueRect_, levelRect_, levelValueRect_, timeRect_;
  SDL_Texture *scoreTexture_, *scoreValueTexture_, *levelTexture_,
      *levelValueTexture_, *timeTexture_;

  TTF_Font *font_;

  void updateScore(SDL_Renderer *renderer, uint scoreValue);
  void updateLevel(SDL_Renderer *renderer, uint levelValue);
  void updateTime(SDL_Renderer *renderer,
                  std::chrono::duration<double> curTime);

public:
  ScoreViewer();
  ~ScoreViewer();

  void init(SDL_Renderer *renderer, TTF_Font *font);
  void draw(SDL_Renderer *renderer, uint scoreValue, uint levelValue,
            std::chrono::duration<double> curTime);
};

#endif // SCOREVIEWER_HPP
