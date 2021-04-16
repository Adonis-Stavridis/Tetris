#ifndef STARTGAME_HPP
#define STARTGAME_HPP

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "gamepage.hpp"
#include "textures.hpp"

/**
 * @brief First page of Game
 * 
 */
class Startgame : public GamePage
{
private:
  const char *text_;
  SDL_Color textColor_;

  SDL_Rect textRect_;
  SDL_Texture *textTexture_;

  Mix_Music *music_;

public:
  /**
   * @brief Construct a new Startgame object
   * 
   */
  Startgame();

  /**
   * @brief Destroy the Startgame object
   * 
   */
  ~Startgame();

  /**
   * @brief Init Startgame object
   * 
   * @param renderer 
   * @param font 
   * @param windowWidth 
   * @param windowHeight 
   */
  void init(SDL_Renderer *renderer, TTF_Font *font,
            const int windowWidth, const int windowHeight);

  /**
   * @brief Draw page's components
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
};

#endif // STARTGAME_HPP
