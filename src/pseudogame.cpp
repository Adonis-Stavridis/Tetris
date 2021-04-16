#include "pseudogame.hpp"

Pseudogame::Pseudogame()
    : text_("Enter username"),
      textColor_(Colors::gold()),
      pseudoColor_(Colors::dodgerblue()),
      endColor_(Colors::snow()),
      cpt_(0),
      pseudo_("_ _ _ _")
{
}

Pseudogame::~Pseudogame()
{
  // SDL_DestroyTexture(textTexture_);
  // SDL_DestroyTexture(pseudoTexture_);
  // SDL_DestroyTexture(endTexture_);
}

void Pseudogame::init(SDL_Renderer *renderer, TTF_Font *font,
                      const int windowWidth, const int windowHeight,
                      Endgame *endgame)
{
  endgame_ = endgame;
  renderer_ = renderer;
  font_ = font;

  int tempWidth, tempHeight;
  textTexture_ = Textures::create(font, text_, textColor_, renderer, tempWidth,
                                  tempHeight);
  tempWidth *= 2;
  tempHeight *= 2;
  textRect_ = {(windowWidth / 2) - (tempWidth / 2),
               (windowHeight / 4) - (tempHeight / 2), tempWidth, tempHeight};

  pseudoTexture_ = Textures::create(font, pseudo_.c_str(), pseudoColor_,
                                    renderer, tempWidth, tempHeight);
  tempWidth *= 2;
  tempHeight *= 2;
  pseudoRect_ = {textRect_.x + (textRect_.w / 4), textRect_.y + 200, tempWidth,
                 tempHeight};

  endTexture_ = Textures::create(font, "Press [space] to CONTINUE", endColor_,
                                 renderer, tempWidth, tempHeight);
  endRect_ = {(windowWidth / 2) - (tempWidth / 2),
              windowHeight - tempHeight - 120,
              tempWidth, tempHeight};
}

PageAction Pseudogame::draw(SDL_Renderer *renderer)
{
  SDL_RenderCopy(renderer, textTexture_, nullptr, &textRect_);
  SDL_RenderCopy(renderer, pseudoTexture_, nullptr, &pseudoRect_);
  if (pseudo_[6] != '_')
    SDL_RenderCopy(renderer, endTexture_, nullptr, &endRect_);

  return PageAction::None;
}

void Pseudogame::start()
{
  pseudo_ = "_ _ _ _";
  cpt_ = 0;

  pseudoTexture_ = Textures::create(font_, pseudo_.c_str(), pseudoColor_,
                                    renderer_);
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

        pseudoTexture_ = Textures::create(font_, pseudo_.c_str(), pseudoColor_,
                                          renderer_);
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

        pseudoTexture_ = Textures::create(font_, pseudo_.c_str(), pseudoColor_,
                                          renderer_);
      }
      break;
    }
  }

  return PageAction::None;
}
