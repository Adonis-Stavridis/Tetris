#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "colors.hpp"
#include "gamepage.hpp"
#include "startgame.hpp"
#include "ingame.hpp"
#include "endgame.hpp"
#include "pseudogame.hpp"
#include "scoregame.hpp"

#define FONT_PATH "assets/fonts/PressStart2P-vaV7.ttf"
#define FONT_SIZE 32

#define PAGE_NUMBER 5

/**
 * @class Game
 * 
 * @brief Main Game engine that will instantiate everything and loop during the
 * entire gaming session.
 * 
 */
class Game
{
private:
  std::string windowTitle_;
  int windowWidth_;
  int windowHeight_;

  SDL_Window *window_;
  SDL_Renderer *renderer_;

  TTF_Font *font_;
  SDL_Color bgColor_;

  bool running_;

  Startgame startgame_;
  Ingame ingame_;
  Endgame endgame_;
  Pseudogame pseudogame_;
  Scoregame scoregame_;

  GamePage *gamePage_;

public:
  /**
   * @brief Construct a new Game object
   * 
   */
  Game();

  /**
   * @brief Destroy the Game object
   * 
   */
  ~Game();

  /**
   * @brief Init Game object
   * 
   */
  void init();

  /**
   * @brief Run Game object (main loop)
   * 
   */
  void run();

  /**
   * @brief Draw instances in window
   * 
   */
  void draw();

  /**
   * @brief Quit Game
   * 
   */
  void quit();

  /**
   * @brief Check event in order to change page
   * 
   * @param action 
   */
  void checkEvent(PageAction action);
};

#endif //GAME_HPP
