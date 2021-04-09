#include "score.hpp"

Score::Score()
    : score_("Score"),
      value_(0),
      time_("00:00"),
      scoreColor_({0xFF, 0xFA, 0xFA, 0xFF}),
      valueColor_({0xFF, 0xD7, 0x00, 0xFF}),
      timeColor_({0xFF, 0x63, 0x47, 0xFF})
{
}

Score::~Score()
{
  SDL_DestroyTexture(scoreTexture_);
  SDL_DestroyTexture(valueTexture_);
}

void Score::init(SDL_Renderer *renderer, TTF_Font *font)
{
  SDL_Surface *tempSurface = TTF_RenderText_Blended(font, score_, scoreColor_);
  scoreTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  int tempWidth, tempHeight;
  SDL_QueryTexture(scoreTexture_, NULL, NULL, &tempWidth, &tempHeight);
  scoreRect_ = {50, 50, tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);

  const char *valueText = std::to_string(value_).c_str();
  tempSurface = TTF_RenderText_Blended(font, valueText, valueColor_);
  valueTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  SDL_QueryTexture(valueTexture_, NULL, NULL, &tempWidth, &tempHeight);
  valueRect_ =
      {scoreRect_.x + 10, scoreRect_.y + scoreRect_.h + 10, tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);

  tempSurface = TTF_RenderText_Blended(font, time_.c_str(), timeColor_);
  timeTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  SDL_QueryTexture(timeTexture_, NULL, NULL, &tempWidth, &tempHeight);
  timeRect_ =
      {scoreRect_.x, valueRect_.y + valueRect_.h + 500, tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);
}

void Score::draw(SDL_Renderer *renderer)
{
  SDL_RenderCopy(renderer, scoreTexture_, nullptr, &scoreRect_);
  SDL_RenderCopy(renderer, valueTexture_, nullptr, &valueRect_);
  SDL_RenderCopy(renderer, timeTexture_, nullptr, &timeRect_);
}
