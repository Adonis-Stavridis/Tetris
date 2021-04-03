#ifndef SCORE_HPP
#define SCORE_HPP

#include <SDL2/SDL.h>

class Score
{
private:
  unsigned int value;

public:
  Score();
  ~Score();

  void draw(SDL_Renderer *renderer_);
};

#endif // SCORE_HPP
