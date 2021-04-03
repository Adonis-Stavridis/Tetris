#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "board.hpp"
#include "score.hpp"
#include "startgame.hpp"

#define FONT_SIZE 32

enum GameState
{
  StartgameState = 0,
  IngameState = 1,
  EndgameState = 2
};

class Game
{
private:
  std::string windowTitle_;
  int windowWidth_;
  int windowHeight_;
  
  Board board_;
  Score score_;

  TTF_Font *font_;
  SDL_Color bgColor_;

  bool running_;
  SDL_Event event_;

  SDL_Window *window_;
  SDL_Renderer *renderer_;

  GameState state_;

  Startgame startgame_;

public:
  Game();
  Game(std::string windowTitle, int windowWidth, int windowHeight);
  ~Game();

  bool init();
  void run();
  void draw();
  void quit();
};

#endif //GAME_HPP
