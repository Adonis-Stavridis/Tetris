#include "ingame.hpp"

Ingame::Ingame(const int windowWidth_, const int windowHeight_)
    : board_(Board(windowWidth_, windowHeight_)),
      score_(Score())
{
}

Ingame::~Ingame()
{
}

void Ingame::init(SDL_Renderer *renderer, TTF_Font *font)
{
  score_.init(renderer, font);
}

void Ingame::draw(SDL_Renderer *renderer)
{
  board_.draw(renderer);
  score_.draw(renderer);
}

PageAction Ingame::handleInput(SDL_Event event)
{
  if (event.type == SDL_KEYDOWN)
    return PageAction::NextPage;

  return PageAction::None;
}
