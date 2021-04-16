#ifndef GAMEPAGE_HPP
#define GAMEPAGE_HPP

#include <SDL2/SDL.h>

#include "music.hpp"

/**
 * @brief A collection of Page Actions
 * 
 */
enum PageAction
{
  None = 0, ///< Do nothing
  NextPage, ///< Go to next page
  Quit      ///< Quit game
};

/**
 * @brief Abstract Game Page
 * 
 */
class GamePage
{
public:
  /**
   * @brief Draw function to be called to compute logic and render page and its
   * components
   * 
   * @param renderer 
   * @return PageAction 
   */
  virtual PageAction draw(SDL_Renderer *renderer) = 0;

  /**
   * @brief Start function to be called once before page is about to be 
   * displayed
   * 
   */
  virtual void start() = 0;

  /**
   * @brief Input handler function for a single page
   * 
   * @param event 
   * @return PageAction 
   */
  virtual PageAction handleInput(SDL_Event event) = 0;
};

#endif // GAMEPAGE_HPP
