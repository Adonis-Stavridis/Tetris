#ifndef QUEUEVIEWER_HPP
#define QUEUEVIEWER_HPP

#include <vector>
#include <queue>

#include <SDL2/SDL_ttf.h>

#include "tetromino.hpp"
#include "textures.hpp"

class QueueViewer
{
private:
  const char *text_;
  SDL_Color textColor_;
  SDL_Texture *textTexture_;

  SDL_Rect textRect_;
  std::vector<SDL_Rect> tetroRects_;

  std::vector<Tetromino> queue_;

public:
  QueueViewer(const int windowWidth);
  ~QueueViewer();

  void init(SDL_Renderer *renderer, TTF_Font *font);
  void draw(SDL_Renderer *renderer);

  void updateQueue(const std::queue<Tetromino> queue);
};

#endif // QUEUEVIEWER_HPP
