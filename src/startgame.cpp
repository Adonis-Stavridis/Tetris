#include "startgame.hpp"

Startgame::Startgame()
    : text_("Press any key to START"),
      textColor_({0xFF, 0xFA, 0xFA, 0xFF}),
      music_(nullptr)
{
}

Startgame::~Startgame()
{
  // SDL_DestroyTexture(textTexture_);

  Mix_FreeMusic(music_);
}

void Startgame::init(SDL_Renderer *renderer, TTF_Font *font,
                     const int windowWidth, const int windowHeight)
{
  int tempWidth, tempHeight;
  textTexture_ = Textures::init(font, text_, textColor_, renderer, tempWidth,
                                tempHeight);
  textRect_ = {(windowWidth / 2) - (tempWidth / 2),
               (windowHeight / 2) - (tempHeight / 2), tempWidth, tempHeight};

  music_ = Music::load("theme");
}

PageAction Startgame::draw(SDL_Renderer *renderer)
{
  SDL_RenderCopy(renderer, textTexture_, nullptr, &textRect_);

  return PageAction::None;
}

void Startgame::start()
{
  Music::play(music_);
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
