#ifndef GAMEPAGE_HPP
#define GAMEPAGE_HPP

#include <SDL2/SDL.h>

enum PageAction
{
  None = 0,
  NextPage,
  Quit
};

class GamePage
{
public:
  virtual PageAction draw(SDL_Renderer *renderer) = 0;
  virtual void start() = 0;
  virtual PageAction handleInput(SDL_Event event) = 0;
};

#endif // GAMEPAGE_HPP
