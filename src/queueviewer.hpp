#ifndef QUEUEVIEWER_HPP
#define QUEUEVIEWER_HPP

#include <vector>
#include <queue>

#include <SDL2/SDL_ttf.h>

#include "tetromino.hpp"
#include "textures.hpp"

/**
 * @brief Right-side Tetromino Queue Viewer
 * 
 */
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
  /**
   * @brief Construct a new Queue Viewer object
   * 
   * @param windowWidth 
   */
  QueueViewer(const int windowWidth);

  /**
   * @brief Destroy the Queue Viewer object
   * 
   */
  ~QueueViewer();

  /**
   * @brief Init Queue Viewer object
   * 
   * @param renderer 
   * @param font 
   */
  void init(SDL_Renderer *renderer, TTF_Font *font);

  /**
   * @brief Draw Queue Viewer
   * 
   * @param renderer 
   */
  void draw(SDL_Renderer *renderer);

  /**
   * @brief Update queue
   * 
   * @param queue 
   */
  void updateQueue(const std::queue<Tetromino> queue);
};

#endif // QUEUEVIEWER_HPP
