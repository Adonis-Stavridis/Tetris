#ifndef QUEUEVIEWER_HPP
#define QUEUEVIEWER_HPP

#include <vector>
#include <queue>

#include <SDL2/SDL_ttf.h>

#include "tetromino.hpp"

class QueueViewer
{
private:
  const char *text_;
  SDL_Color textColor_;
  SDL_Texture *textTexture_;

  SDL_Rect textRect_, rect0_, rect1_, rect2_, rect3_;

  std::vector<Tetromino> queue_;

public:
  QueueViewer(const int windowWidth);
  ~QueueViewer();

  void init(SDL_Renderer *renderer, TTF_Font *font);
  void start(const std::queue<Tetromino> queue);
  void draw(SDL_Renderer *renderer);
};

#endif // QUEUEVIEWER_HPP
