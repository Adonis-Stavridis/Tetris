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
  {
    switch (event.key.keysym.sym)
    {
    case SDLK_LEFT:
      std::cout << "KEY: LEFT" << std::endl;
      break;

    case SDLK_RIGHT:
      std::cout << "KEY: RIGHT" << std::endl;
      break;

    case SDLK_UP:
      std::cout << "KEY: UP" << std::endl;
      break;

    case SDLK_DOWN:
      std::cout << "KEY: DOWN" << std::endl;
      break;

    case SDLK_ESCAPE:
      return PageAction::Quit;
      break;

    // ! TO REMOVE : TEMPORARY
    case SDLK_SPACE:
      return PageAction::NextPage;
      break;

    default:
      break;
    }
  }

  return PageAction::None;
}
