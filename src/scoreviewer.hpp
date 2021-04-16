#ifndef SCOREVIEWER_HPP
#define SCOREVIEWER_HPP

#include <iostream>
#include <chrono>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "colors.hpp"

#define FONT_SIZE 32

/**
 * @brief Left-side Score Viewer
 * 
 */
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
  /**
   * @brief Construct a new Score Viewer object
   * 
   */
  ScoreViewer();

  /**
   * @brief Destroy the Score Viewer object
   * 
   */
  ~ScoreViewer();

  /**
   * @brief Init ScoreViewer
   * 
   * @param renderer 
   * @param font 
   */
  void init(SDL_Renderer *renderer, TTF_Font *font);

  /**
   * @brief Draw ScoreViewer's components
   * 
   * @param renderer 
   */
  void draw(SDL_Renderer *renderer);

  /**
   * @brief Update score texture
   * 
   * @param scoreValue 
   */
  void updateScore(uint scoreValue);

  /**
   * @brief Update level texture
   * 
   * @param levelValue 
   */
  void updateLevel(uint levelValue);

  /**
   * @brief Update lines value
   * 
   * @param linesValue 
   */
  void updateLines(uint linesValue);

  /**
   * @brief Update time value
   * 
   * @param curTime 
   */
  void updateTime(std::chrono::duration<double> curTime);
};

#endif // SCOREVIEWER_HPP
