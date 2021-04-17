#ifndef PSEUDOGAME_HPP
#define PSEUDOGAME_HPP

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "gamepage.hpp"
#include "endgame.hpp"
#include "colors.hpp"

/**
 * @brief Username selection Game page
 * 
 */
class Pseudogame : public GamePage
{
private:
  const char *text_;
  SDL_Color textColor_, pseudoColor_, endColor_;

  SDL_Rect textRect_, pseudoRect_, endRect_;
  SDL_Texture *textTexture_, *pseudoTexture_, *endTexture_;

  int cpt_;
  std::string pseudo_;

  SDL_Renderer *renderer_;
  TTF_Font *font_;
  Endgame *endgame_;

public:
  /**
   * @brief Construct a new Pseudogame object
   * 
   */
  Pseudogame();

  /**
   * @brief Destroy the Pseudogame object
   * 
   */
  ~Pseudogame();

  /**
   * @brief Init Pseudogame object
   * 
   * @param renderer 
   * @param font 
   * @param windowWidth 
   * @param windowHeight 
   * @param endgame 
   */
  void init(SDL_Renderer *renderer, TTF_Font *font, const int windowWidth,
            const int windowHeight, Endgame *endgame);

  /**
   * @brief Draw Pseugame's components
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
   * @brief Get the Pseudo value
   * 
   * @return std::string 
   */
  inline std::string getPseudo()
  {
    return pseudo_;
  }
};

#endif // PSEUDOGAME_HPP
