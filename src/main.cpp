#include "SDL.h"

#include "game.hpp"

int main()
{
  Game game;

  game.init();

  game.run();

  game.quit();

  return 0;
}
