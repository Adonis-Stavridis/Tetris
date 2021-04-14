#include "pseudogame.hpp"

Pseudogame::Pseudogame()
    : text_("Enter a nickname :"),
      textColor_(Colors::gold()),
      pseudoColor_(Colors::dodgerblue()),
      endColor_(Colors::snow()),
      cpt_(0),
      pseudo_("_ _ _ _"),
      music_(nullptr)
{
}

Pseudogame::~Pseudogame()
{
  // SDL_DestroyTexture(textTexture_);
  // SDL_DestroyTexture(pseudoTexture_);
  // SDL_DestroyTexture(endTexture_);

  Mix_FreeMusic(music_);
}

void Pseudogame::init(SDL_Renderer *renderer, TTF_Font *font,
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

  tempSurface = TTF_RenderText_Blended(font, pseudo_.c_str(), pseudoColor_);
  pseudoTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  SDL_QueryTexture(pseudoTexture_, NULL, NULL, &tempWidth, &tempHeight);
  tempWidth *= 2;
  tempHeight *= 2;
  pseudoRect_ = {textRect_.x + (textRect_.w / 4), textRect_.y + 200, tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);

  tempSurface = TTF_RenderText_Blended(font, "Press [space] to CONTINUE", endColor_);
  endTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  SDL_QueryTexture(endTexture_, NULL, NULL, &tempWidth, &tempHeight);
  endRect_ = {(windowWidth / 2) - (tempWidth / 2), pseudoRect_.y + 220, tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);

  music_ = Mix_LoadMUS(Music::path("new_theme").c_str());
  if (!music_)
  {
    std::cerr << "Mix_LoadMUS failed!" << std::endl;
    exit(EXIT_FAILURE);
  }
}

PageAction Pseudogame::draw(SDL_Renderer *renderer)
{
  SDL_RenderCopy(renderer, textTexture_, nullptr, &textRect_);
  SDL_RenderCopy(renderer, pseudoTexture_, nullptr, &pseudoRect_);
  if(pseudo_[6] != '_')
    SDL_RenderCopy(renderer, endTexture_, nullptr, &endRect_);

  return PageAction::None;
}

void Pseudogame::start()
{
  int tempWidth, tempHeight;
  pseudo_ = "_ _ _ _";
  cpt_ = 0;
  SDL_Surface *tempSurface = TTF_RenderText_Blended(font_, pseudo_.c_str(), pseudoColor_);
  pseudoTexture_ = SDL_CreateTextureFromSurface(renderer_, tempSurface);
  SDL_QueryTexture(pseudoTexture_, NULL, NULL, &tempWidth, &tempHeight);
  tempWidth *= 2;
  tempHeight *= 2;
  pseudoRect_ = {pseudoRect_.x, pseudoRect_.y, tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);

  if (Mix_PlayMusic(music_, -1) == -1)
  {
    std::cerr << "Mix_PlayMusic failed!" << std::endl;
    exit(EXIT_FAILURE);
  }
}

PageAction Pseudogame::handleInput(SDL_Event event)
{
  if (event.type == SDL_KEYDOWN)
  {
    switch (event.key.keysym.sym)
    {
    case SDLK_BACKSPACE:
      if (cpt_ > 0)
      {
        cpt_ -= 2;
        pseudo_[cpt_] = '_';

        int tempWidth, tempHeight;

        SDL_Surface *tempSurface = TTF_RenderText_Blended(font_, pseudo_.c_str(), pseudoColor_);
        pseudoTexture_ = SDL_CreateTextureFromSurface(renderer_, tempSurface);
        SDL_QueryTexture(pseudoTexture_, NULL, NULL, &tempWidth, &tempHeight);
        tempWidth *= 2;
        tempHeight *= 2;
        pseudoRect_ = {pseudoRect_.x, pseudoRect_.y, tempWidth, tempHeight};
        SDL_FreeSurface(tempSurface);
      }
      break;

    case SDLK_ESCAPE:
      return PageAction::Quit;
      break;

    case SDLK_SPACE:
      if (pseudo_[6] != '_')
        return PageAction::NextPage;
      break;

    default:
      const char *k = SDL_GetKeyName(event.key.keysym.sym);

      if (strlen(k) == 1 && isalpha(k[0]))
      {
        pseudo_[cpt_] = k[0];
        if (cpt_ < 8)
          cpt_ += 2;

        int tempWidth, tempHeight;

        SDL_Surface *tempSurface = TTF_RenderText_Blended(font_, pseudo_.c_str(), pseudoColor_);
        pseudoTexture_ = SDL_CreateTextureFromSurface(renderer_, tempSurface);
        SDL_QueryTexture(pseudoTexture_, NULL, NULL, &tempWidth, &tempHeight);
        tempWidth *= 2;
        tempHeight *= 2;
        pseudoRect_ = {pseudoRect_.x, pseudoRect_.y, tempWidth, tempHeight};
        SDL_FreeSurface(tempSurface);
      }
      break;
    }
  }

  return PageAction::None;
}
