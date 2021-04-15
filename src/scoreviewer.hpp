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
  const char *lines_;
  uint linesValue_;
  std::string time_;

  SDL_Color textColor_, valueColor_, timeColor_;
  SDL_Rect scoreRect_, scoreValueRect_, levelRect_, levelValueRect_, linesRect_,
      linesValueRect_, timeRect_;
  SDL_Texture *scoreTexture_, *scoreValueTexture_, *levelTexture_,
      *levelValueTexture_, *linesTexture_, *linesValueTexture_, *timeTexture_;

  SDL_Renderer *renderer_;
  TTF_Font *font_;

public:
  ScoreViewer();
  ~ScoreViewer();

  void init(SDL_Renderer *renderer, TTF_Font *font);
  void draw(SDL_Renderer *renderer);

  void updateScore(uint scoreValue);
  void updateLevel(uint levelValue);
  void updateLines(uint linesValue);
  void updateTime(std::chrono::duration<double> curTime);
};

#endif // SCOREVIEWER_HPP
