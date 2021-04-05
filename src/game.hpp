#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "board.hpp"
#include "score.hpp"
#include "gamepage.hpp"
#include "startgame.hpp"
#include "ingame.hpp"

#define FONT_PATH "assets/fonts/PressStart2P-vaV7.ttf"
#define FONT_SIZE 32

#define PAGE_NUMBER 2

class Game
{
private:
  std::string windowTitle_;
  int windowWidth_;
  int windowHeight_;

  TTF_Font *font_;
  SDL_Color bgColor_;

  bool running_;
  SDL_Event event_;

  SDL_Window *window_;
  SDL_Renderer *renderer_;

  Startgame startgame_;
  Ingame ingame_;
  GamePage *gamePage_;

public:
  Game();
  Game(std::string windowTitle, int windowWidth, int windowHeight);
  ~Game();

  bool init();
  void run();
  void draw();
  void quit();

  void checkEvent(PageAction action);
};

#endif //GAME_HPP
