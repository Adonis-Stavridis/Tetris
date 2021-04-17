#ifndef SCOREGAME_HPP
#define SCOREGAME_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <utility>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "gamepage.hpp"
#include "endgame.hpp"
#include "pseudogame.hpp"
#include "colors.hpp"

/**
 * @brief Score Game page
 * 
 */
class Scoregame : public GamePage
{
private:
  const char *text_;
  SDL_Color textColor_, pseudoColor_;

  SDL_Rect textRect_;
  SDL_Texture *textTexture_;

  std::array<SDL_Rect, 9> pseudoRect_;
  std::array<SDL_Texture *, 9> pseudoTexture_;

  SDL_Renderer *renderer_;
  TTF_Font *font_;
  Endgame *endgame_;
  Pseudogame *pseudogame_;

  uint score_;
  std::string pseudo_;

  std::vector<std::pair<std::string, uint>> high_;

public:
  /**
   * @brief Construct a new Scoregame object
   * 
   */
  Scoregame();

  /**
   * @brief Destroy the Scoregame object
   * 
   */
  ~Scoregame();

  /**
   * @brief Init Scoregame object
   * 
   * @param renderer 
   * @param font 
   * @param windowWidth 
   * @param windowHeight 
   * @param endgame 
   * @param Pseudogame 
   */
  void init(SDL_Renderer *renderer, TTF_Font *font, const int windowWidth,
            const int windowHeight, Endgame *endgame, Pseudogame *Pseudogame);
  
  /**
   * @brief Draw Scoregame's components
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

#endif // SCOREGAME_HPP
