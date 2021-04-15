#include "scoreviewer.hpp"

ScoreViewer::ScoreViewer()
    : score_("Score"),
      scoreValue_(0),
      level_("Level"),
      levelValue_(0),
      lines_("Lines"),
      linesValue_(0),
      time_("00:00"),
      textColor_(Colors::snow()),
      valueColor_(Colors::gold()),
      timeColor_(Colors::tomato())
{
}

ScoreViewer::~ScoreViewer()
{
  // SDL_DestroyTexture(scoreTexture_);
  // SDL_DestroyTexture(scoreValueTexture_);
  // SDL_DestroyTexture(levelTexture_);
  // SDL_DestroyTexture(levelValueTexture_);
  // SDL_DestroyTexture(linesTexture_);
  // SDL_DestroyTexture(linesValueTexture_);
  // SDL_DestroyTexture(timeTexture_);
}

void ScoreViewer::init(SDL_Renderer *renderer, TTF_Font *font)
{
  SDL_Surface *tempSurface = TTF_RenderText_Blended(font, score_, textColor_);
  scoreTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  int tempWidth, tempHeight;
  SDL_QueryTexture(scoreTexture_, NULL, NULL, &tempWidth, &tempHeight);
  scoreRect_ = {50, 50, tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);

  const char *scoreValueText = std::to_string(scoreValue_).c_str();
  tempSurface = TTF_RenderText_Blended(font, scoreValueText, valueColor_);
  scoreValueTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  SDL_QueryTexture(scoreValueTexture_, NULL, NULL, &tempWidth, &tempHeight);
  scoreValueRect_ =
      {scoreRect_.x + 10, scoreRect_.y + scoreRect_.h + 10,
       tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);

  tempSurface = TTF_RenderText_Blended(font, level_, textColor_);
  levelTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  SDL_QueryTexture(levelTexture_, NULL, NULL, &tempWidth, &tempHeight);
  levelRect_ = {scoreRect_.x, scoreValueRect_.y + scoreValueRect_.h + 50,
                tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);

  const char *levelValueText = std::to_string(levelValue_).c_str();
  tempSurface = TTF_RenderText_Blended(font, levelValueText, valueColor_);
  levelValueTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  SDL_QueryTexture(levelValueTexture_, NULL, NULL, &tempWidth, &tempHeight);
  levelValueRect_ =
      {levelRect_.x + 10, levelRect_.y + levelRect_.h + 10,
       tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);

  tempSurface = TTF_RenderText_Blended(font, lines_, textColor_);
  linesTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  SDL_QueryTexture(linesTexture_, NULL, NULL, &tempWidth, &tempHeight);
  linesRect_ = {levelRect_.x, levelValueRect_.y + levelValueRect_.h + 50,
                tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);

  const char *linesValueText = std::to_string(linesValue_).c_str();
  tempSurface = TTF_RenderText_Blended(font, linesValueText, valueColor_);
  linesValueTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  SDL_QueryTexture(linesValueTexture_, NULL, NULL, &tempWidth, &tempHeight);
  linesValueRect_ =
      {linesRect_.x + 10, linesRect_.y + linesRect_.h + 10,
       tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);

  tempSurface = TTF_RenderText_Blended(font, time_.c_str(), timeColor_);
  timeTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  SDL_QueryTexture(timeTexture_, NULL, NULL, &tempWidth, &tempHeight);
  timeRect_ =
      {scoreRect_.x, scoreValueRect_.y + scoreValueRect_.h + 500, tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);

  font_ = font;
}

void ScoreViewer::draw(SDL_Renderer *renderer, uint scoreValue, uint levelValue,
                       uint lines, std::chrono::duration<double> curTime)
{
  SDL_RenderCopy(renderer, scoreTexture_, nullptr, &scoreRect_);
  updateScore(renderer, scoreValue);
  SDL_RenderCopy(renderer, scoreValueTexture_, nullptr, &scoreValueRect_);
  SDL_RenderCopy(renderer, levelTexture_, nullptr, &levelRect_);
  updateLevel(renderer, levelValue);
  SDL_RenderCopy(renderer, levelValueTexture_, nullptr, &levelValueRect_);
  SDL_RenderCopy(renderer, linesTexture_, nullptr, &linesRect_);
  updateLines(renderer, lines);
  SDL_RenderCopy(renderer, linesValueTexture_, nullptr, &linesValueRect_);
  updateTime(renderer, curTime);
  SDL_RenderCopy(renderer, timeTexture_, nullptr, &timeRect_);
}

void ScoreViewer::updateScore(SDL_Renderer *renderer, uint scoreValue)
{
  if (scoreValue_ == scoreValue)
    return;

  scoreValue_ = scoreValue;
  const std::string scoreString = std::to_string(scoreValue_);

  SDL_Surface *tempSurface = TTF_RenderText_Blended(
      font_, scoreString.c_str(), valueColor_);
  scoreValueTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  int tempWidth, tempHeight;
  SDL_QueryTexture(scoreValueTexture_, NULL, NULL, &tempWidth, &tempHeight);
  scoreValueRect_ =
      {scoreRect_.x + 10, scoreRect_.y + scoreRect_.h + 10,
       tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);
}

void ScoreViewer::updateLevel(SDL_Renderer *renderer, uint levelValue)
{
  if (levelValue_ == levelValue)
    return;

  levelValue_ = levelValue;
  const std::string levelString = std::to_string(levelValue_);

  SDL_Surface *tempSurface = TTF_RenderText_Blended(
      font_, levelString.c_str(), valueColor_);
  levelValueTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  int tempWidth, tempHeight;
  SDL_QueryTexture(levelValueTexture_, NULL, NULL, &tempWidth, &tempHeight);
  levelValueRect_ =
      {levelRect_.x + 10, levelRect_.y + levelRect_.h + 10,
       tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);
}

void ScoreViewer::updateLines(SDL_Renderer *renderer, uint linesValue)
{
  if (linesValue_ == linesValue)
    return;

  linesValue_ = linesValue;
  const std::string linesString = std::to_string(linesValue_);

  SDL_Surface *tempSurface = TTF_RenderText_Blended(
      font_, linesString.c_str(), valueColor_);
  linesValueTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  int tempWidth, tempHeight;
  SDL_QueryTexture(linesValueTexture_, NULL, NULL, &tempWidth, &tempHeight);
  linesValueRect_ =
      {linesRect_.x + 10, linesRect_.y + linesRect_.h + 10,
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
