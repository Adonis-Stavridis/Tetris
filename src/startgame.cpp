#include "startgame.hpp"

Startgame::Startgame()
    : text_("Press any key to START"),
      textColor_({0xFF, 0xFA, 0xFA, 0xFF})
{
}

Startgame::~Startgame()
{
  SDL_DestroyTexture(textTexture_);
}

void Startgame::init(SDL_Renderer *renderer, TTF_Font *font,
                     const int windowWidth, const int windowHeight)
{
  SDL_Surface *tempSurface = TTF_RenderText_Blended(font, text_, textColor_);
  textTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  int tempWidth, tempHeight;
  SDL_QueryTexture(textTexture_, NULL, NULL, &tempWidth, &tempHeight);
  textRect_ = {(windowWidth / 2) - (tempWidth / 2),
               (windowHeight / 2) - (tempHeight / 2), tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);
}

void Startgame::draw(SDL_Renderer *renderer)
{
  SDL_RenderCopy(renderer, textTexture_, nullptr, &textRect_);
}

void Startgame::start()
{
}

PageAction Startgame::handleInput(SDL_Event event)
{
  if (event.type == SDL_KEYDOWN)
  {
    if (event.key.keysym.sym == SDLK_ESCAPE)
      return PageAction::Quit;
    else
      return PageAction::NextPage;
  }

  return PageAction::None;
}
