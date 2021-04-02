#ifndef GAME_HPP
#define GAME_HPP

#include <string>

#include "SDL2/SDL.h"
#include "SDL2/SDL_events.h"

class Game
{
private:
  std::string windowTitle_;
  int windowWidth_;
  int windowHeight_;
  bool running_;
  SDL_Event event_;
  int boardPositionX_;
  int boardPositionY_;

  // TetrisBoard board_;
  // Texture blockTexture_;
  SDL_Window *window_;
  SDL_Surface *windowSurface_;
  SDL_Renderer *renderer_;

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
