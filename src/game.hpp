#ifndef GAME_HPP
#define GAME_HPP

#include <string>

#include "SDL2/SDL.h"

#include "board.hpp"

enum GameState
{
  Menu = 0,
  Ingame = 1,
  Score = 2
};

class Game
{
private:
  std::string windowTitle_;
  int windowWidth_;
  int windowHeight_;
  Board board_;

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
  void loadMedia();
};

#endif //GAME_HPP
