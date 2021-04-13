#include "scoreviewer.hpp"

ScoreViewer::ScoreViewer()
    : score_("Score"),
      value_(0),
      time_("00:00"),
      scoreColor_(Colors::snow()),
      valueColor_(Colors::gold()),
      timeColor_(Colors::tomato())
{
}

ScoreViewer::~ScoreViewer()
{
  SDL_DestroyTexture(scoreTexture_);
  SDL_DestroyTexture(valueTexture_);
  SDL_DestroyTexture(timeTexture_);
}

void ScoreViewer::init(SDL_Renderer *renderer, TTF_Font *font)
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
      {scoreRect_.x + 10, scoreRect_.y + scoreRect_.h + 10,
       tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);

  tempSurface = TTF_RenderText_Blended(font, time_.c_str(), timeColor_);
  timeTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  SDL_QueryTexture(timeTexture_, NULL, NULL, &tempWidth, &tempHeight);
  timeRect_ =
      {scoreRect_.x, valueRect_.y + valueRect_.h + 500, tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);

  font_ = font;
}

void ScoreViewer::draw(SDL_Renderer *renderer, uint scoreValue,
                       std::chrono::duration<double> curTime)
{
  SDL_RenderCopy(renderer, scoreTexture_, nullptr, &scoreRect_);
  updateScore(renderer, scoreValue);
  SDL_RenderCopy(renderer, valueTexture_, nullptr, &valueRect_);
  updateTime(renderer, curTime);
  SDL_RenderCopy(renderer, timeTexture_, nullptr, &timeRect_);
}

void ScoreViewer::start()
{
  value_ = 0;
}

void ScoreViewer::updateScore(SDL_Renderer *renderer, uint scoreValue)
{
  if (value_ == scoreValue)
    return;

  value_ = scoreValue;
  const std::string scoreString = std::to_string(value_);

  SDL_Surface *tempSurface = TTF_RenderText_Blended(
      font_, scoreString.c_str(), valueColor_);
  valueTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  int tempWidth, tempHeight;
  SDL_QueryTexture(valueTexture_, NULL, NULL, &tempWidth, &tempHeight);
  valueRect_ =
      {scoreRect_.x + 10, scoreRect_.y + scoreRect_.h + 10,
       tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);
}

void ScoreViewer::updateTime(SDL_Renderer *renderer,
                             std::chrono::duration<double> curTime)
{
  uint minutes =
      std::chrono::duration_cast<std::chrono::minutes>(curTime).count();
  uint seconds =
      std::chrono::duration_cast<std::chrono::seconds>(curTime).count() %
      60;

  std::string newTime;
  if (minutes < 10)
    newTime += "0";
  newTime += std::to_string(minutes);
  newTime += ':';
  if (seconds < 10)
    newTime += "0";
  newTime += std::to_string(seconds);

  if (newTime != time_)
  {
    time_ = newTime;
    SDL_Surface *tempSurface = TTF_RenderText_Blended(
        font_, time_.c_str(), timeColor_);
    timeTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
  }
}
