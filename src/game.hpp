#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "colors.hpp"
#include "gamepage.hpp"
#include "startgame.hpp"
#include "ingame.hpp"
#include "endgame.hpp"

#define FONT_PATH "assets/fonts/PressStart2P-vaV7.ttf"
#define FONT_SIZE 32

#define PAGE_NUMBER 3

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

  GamePage *gamePage_;

public:
  Game();
  ~Game();

  void init();
  void run();
  void draw();
  void quit();

  void checkEvent(PageAction action);
};

#endif //GAME_HPP
