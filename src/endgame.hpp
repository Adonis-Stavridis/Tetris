#ifndef ENDGAME_HPP
#define ENDGAME_HPP

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "gamepage.hpp"
#include "ingame.hpp"
#include "colors.hpp"
#include "textures.hpp"

/**
 * @brief Game over page
 * 
 */
class Endgame : public GamePage
{
private:
  const char *text_;
  SDL_Color textColor_, scoreColor_, timeColor_, levelColor_, linesColor_,
      endColor_;

  SDL_Rect textRect_, scoreRect_, timeRect_, levelRect_, linesRect_, endRect_;
  SDL_Texture *textTexture_, *scoreTexture_, *timeTexture_, *levelTexture_,
      *linesTexture_, *endTexture_;

  //To get score + time and print them
  uint score_;
  uint level_;
  uint lines_;
  std::chrono::duration<double> time_;

  SDL_Renderer *renderer_;
  TTF_Font *font_;

  Ingame *ingame_;

  Mix_Music *music_;

public:
  /**
   * @brief Construct a new Endgame object
   * 
   */
  Endgame();

  /**
   * @brief Destroy the Endgame object
   * 
   */
  ~Endgame();

  /**
   * @brief Init the Endgame object
   * 
   * @param renderer 
   * @param font 
   * @param windowWidth 
   * @param windowHeight 
   * @param ingame 
   */
  void init(SDL_Renderer *renderer, TTF_Font *font, const int windowWidth,
            const int windowHeight, Ingame *ingame);

  /**
   * @brief Draw Endgame's components
   * 
   * @param renderer 
   * @return PageAction 
   */
  PageAction draw(SDL_Renderer *renderer);

  /**
   * @brief Reset page's components
   * 
   */
  void start();

  /**
   * @brief Handle inputs
   * 
   * @param event 
   * @return PageAction 
   */
  PageAction handleInput(SDL_Event event);

  /**
   * @brief Update time texture
   * 
   * @param time 
   */
  void updateTime(std::chrono::duration<double> time);

  /**
   * @brief Get the Score value
   * 
   * @return uint 
   */
  inline uint getScore()
  {
    return score_;
  }
};

#endif // ENDGAME_HPP
