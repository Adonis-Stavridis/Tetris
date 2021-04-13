#include "endgame.hpp"

Endgame::Endgame()
    : text_("GAME OVER !"),
      textColor_({0xFF, 0xFA, 0xFA, 0xFF})

{
}

Endgame::~Endgame()
{
  SDL_DestroyTexture(textTexture_);
}

void Endgame::init(SDL_Renderer *renderer, TTF_Font *font,
                     const int windowWidth, const int windowHeight, Ingame *ingame)
{
  SDL_Surface *tempSurface = TTF_RenderText_Blended(font, text_, textColor_);
  textTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  int tempWidth, tempHeight;
  SDL_QueryTexture(textTexture_, NULL, NULL, &tempWidth, &tempHeight);
  textRect_ = {(windowWidth / 2) - (tempWidth / 2),
               (windowHeight / 2) - (tempHeight / 2), tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);

  ingame_ = ingame;
  renderer_ = renderer;
  font_ = font;
  score_ = 0;
  std::string scoreStd = "Score : " + std::to_string(score_);

  tempSurface = TTF_RenderText_Blended(font, scoreStd.c_str(), textColor_);
  scoreTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  SDL_QueryTexture(scoreTexture_, NULL, NULL, &tempWidth, &tempHeight);
  scoreRect_ = {textRect_.x, textRect_.y + 60, textRect_.w, textRect_.h};
  SDL_FreeSurface(tempSurface);
}

PageAction Endgame::draw(SDL_Renderer *renderer)
{
  SDL_RenderCopy(renderer, textTexture_, nullptr, &textRect_);
  SDL_RenderCopy(renderer, scoreTexture_, nullptr, &scoreRect_);

  return PageAction::None;
}

void Endgame::start()
{
  score_ = ingame_->getScore();
  std::string scoreStd = "Score : " + std::to_string(score_);
  
  int tempWidth, tempHeight;
  SDL_Surface *tempSurface = TTF_RenderText_Blended(font_, scoreStd.c_str(), textColor_);
  scoreTexture_ = SDL_CreateTextureFromSurface(renderer_, tempSurface);
  SDL_QueryTexture(scoreTexture_, NULL, NULL, &tempWidth, &tempHeight);
  scoreRect_ = {scoreRect_.x, scoreRect_.y, scoreRect_.w, scoreRect_.h};
  SDL_FreeSurface(tempSurface);
}

PageAction Endgame::handleInput(SDL_Event event)
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
