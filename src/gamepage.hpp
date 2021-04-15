#ifndef GAMEPAGE_HPP
#define GAMEPAGE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "music.hpp"

// #define MUSIC_ENABLED 1

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
