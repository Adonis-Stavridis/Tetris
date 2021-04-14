#include "scoregame.hpp"

Scoregame::Scoregame()
    : text_("Table of Highscores"),
      textColor_(Colors::gold()),
      music_(nullptr)
{
}

Scoregame::~Scoregame()
{
  SDL_DestroyTexture(textTexture_);

  Mix_FreeMusic(music_);
}

void Scoregame::init(SDL_Renderer *renderer, TTF_Font *font,
                     const int windowWidth, const int windowHeight, Endgame *endgame)
{
  SDL_Surface *tempSurface = TTF_RenderText_Blended(font, text_, textColor_);
  textTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  int tempWidth, tempHeight;
  SDL_QueryTexture(textTexture_, NULL, NULL, &tempWidth, &tempHeight);
  tempWidth *= 2;
  tempHeight *= 2;
  textRect_ = {(windowWidth / 2) - (tempWidth / 2),
               (windowHeight / 4) - (tempHeight / 2), tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);

  endgame_ = endgame;
  renderer_ = renderer;
  font_ = font;

  music_ = Mix_LoadMUS(Music::path("new_theme").c_str());
  if (!music_)
  {
    std::cerr << "Mix_LoadMUS failed!" << std::endl;
    exit(EXIT_FAILURE);
  }
}

PageAction Scoregame::draw(SDL_Renderer *renderer)
{
  SDL_RenderCopy(renderer, textTexture_, nullptr, &textRect_);

  return PageAction::None;
}

void Scoregame::start()
{
  if (Mix_PlayMusic(music_, -1) == -1)
  {
    std::cerr << "Mix_PlayMusic failed!" << std::endl;
    exit(EXIT_FAILURE);
  }
}

PageAction Scoregame::handleInput(SDL_Event event)
{
  if (event.type == SDL_KEYDOWN)
  {
    switch (event.key.keysym.sym)
    {

    case SDLK_ESCAPE:
      return PageAction::Quit;
      break;

    case SDLK_SPACE:
      return PageAction::NextPage;
      break;

    default:
      break;
    }
  }

  return PageAction::None;
}
