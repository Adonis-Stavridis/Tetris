#include "SDL.h"

#include "game.hpp"

int main()
{
  Game game;

  if (!game.init())
  {
    std::cerr << "Game Error: Failed to init game" << std::endl;
    exit(EXIT_FAILURE);
  }

  game.run();

  game.quit();

  return 0;
}
