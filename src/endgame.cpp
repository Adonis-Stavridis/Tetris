#include "endgame.hpp"

Endgame::Endgame()
    : text_("GAME OVER !"),
      textColor_(Colors::tomato()),
      scoreColor_(Colors::gold()),
      timeColor_(Colors::snow()),
      score_(0)
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

  std::string scoreStd = "Score : " + std::to_string(score_);

  tempSurface = TTF_RenderText_Blended(font, scoreStd.c_str(), scoreColor_);
  scoreTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  SDL_QueryTexture(scoreTexture_, NULL, NULL, &tempWidth, &tempHeight);
  scoreRect_ = {textRect_.x, textRect_.y + 60, tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);

  std::string timeStd = "Time : 00:00";

  tempSurface = TTF_RenderText_Blended(font, timeStd.c_str(), timeColor_);
  timeTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  SDL_QueryTexture(timeTexture_, NULL, NULL, &tempWidth, &tempHeight);
  timeRect_ = {scoreRect_.x, scoreRect_.y + 60, tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);
}

PageAction Endgame::draw(SDL_Renderer *renderer)
{
  SDL_RenderCopy(renderer, textTexture_, nullptr, &textRect_);
  SDL_RenderCopy(renderer, scoreTexture_, nullptr, &scoreRect_);
  SDL_RenderCopy(renderer, timeTexture_, nullptr, &timeRect_);

  return PageAction::None;
}

void Endgame::start()
{
  score_ = ingame_->getScore();
  time_ = ingame_->getTime();

  updateTime(renderer_, time_);

  std::string scoreStd = "Score : " + std::to_string(score_);
  std::string timeStd = "Time : ";

  int tempWidth, tempHeight;
  SDL_Surface *tempSurface = TTF_RenderText_Blended(font_, scoreStd.c_str(), scoreColor_);
  scoreTexture_ = SDL_CreateTextureFromSurface(renderer_, tempSurface);
  SDL_QueryTexture(scoreTexture_, NULL, NULL, &tempWidth, &tempHeight);
  scoreRect_ = {scoreRect_.x, scoreRect_.y, tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);

  tempSurface = TTF_RenderText_Blended(font_, timeStd.c_str(), timeColor_);
  SDL_QueryTexture(timeTexture_, NULL, NULL, &tempWidth, &tempHeight);
  timeRect_ = {timeRect_.x, timeRect_.y, tempWidth, tempHeight};
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

void Endgame::updateTime(SDL_Renderer *renderer,
                             std::chrono::duration<double> time)
{
  uint minutes =
      std::chrono::duration_cast<std::chrono::minutes>(time).count();
  uint seconds =
      std::chrono::duration_cast<std::chrono::seconds>(time).count() %
      60;

  std::string newTime = "Time : ";
  if (minutes < 10)
    newTime += "0";
  newTime += std::to_string(minutes);
  newTime += ':';
  if (seconds < 10)
    newTime += "0";
  newTime += std::to_string(seconds);
  
  SDL_Surface *tempSurface = TTF_RenderText_Blended(
        font_, newTime.c_str(), timeColor_);
  timeTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  SDL_FreeSurface(tempSurface);
}