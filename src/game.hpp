#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "board.hpp"
#include "score.hpp"

#define FONT_SIZE 32

enum GameState
{
  Startgame = 0,
  Ingame = 1,
  Endgame = 2
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
