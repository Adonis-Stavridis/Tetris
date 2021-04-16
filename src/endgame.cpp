#include "endgame.hpp"

Endgame::Endgame()
    : text_("GAME OVER !"),
      textColor_(Colors::tomato()),
      scoreColor_(Colors::gold()),
      timeColor_(Colors::mediumseagreen()),
      levelColor_(Colors::dodgerblue()),
      linesColor_(Colors::violet()),
      endColor_(Colors::snow()),
      score_(0),
      level_(0),
      lines_(0),
      music_(nullptr)
{
}

Endgame::~Endgame()
{
  // SDL_DestroyTexture(textTexture_);
  // SDL_DestroyTexture(scoreTexture_);
  // SDL_DestroyTexture(timeTexture_);
  // SDL_DestroyTexture(levelTexture_);
  // SDL_DestroyTexture(endTexture_);

  Mix_FreeMusic(music_);
}

void Endgame::init(SDL_Renderer *renderer, TTF_Font *font,
                   const int windowWidth, const int windowHeight,
                   Ingame *ingame)
{
  ingame_ = ingame;
  renderer_ = renderer;
  font_ = font;

  int tempWidth, tempHeight;

  textTexture_ = Textures::create(font, text_, textColor_, renderer, tempWidth,
                                  tempHeight);
  tempWidth *= 2;
  tempHeight *= 2;
  textRect_ = {(windowWidth / 2) - (tempWidth / 2),
               (windowHeight / 4) - (tempHeight / 2), tempWidth, tempHeight};

  std::string scoreStd = "Score : " + std::to_string(score_);
  scoreTexture_ = Textures::create(font, scoreStd.c_str(), scoreColor_, renderer,
                                   tempWidth, tempHeight);
  scoreRect_ = {textRect_.x + 150, textRect_.y + 120, tempWidth, tempHeight};

  std::string levelStd = "Level : " + std::to_string(level_);
  levelTexture_ = Textures::create(font, levelStd.c_str(), levelColor_, renderer,
                                   tempWidth, tempHeight);
  levelRect_ = {scoreRect_.x, scoreRect_.y + 60, tempWidth, tempHeight};

  std::string linesStd = "Lines : " + std::to_string(lines_);
  linesTexture_ = Textures::create(font, linesStd.c_str(), linesColor_, renderer,
                                   tempWidth, tempHeight);
  linesRect_ = {levelRect_.x, levelRect_.y + 60, tempWidth, tempHeight};

  std::string timeStd = "Time  : 00:00";
  timeTexture_ = Textures::create(font, timeStd.c_str(), timeColor_, renderer,
                                  tempWidth, tempHeight);
  timeRect_ = {linesRect_.x, linesRect_.y + 60, tempWidth, tempHeight};

  endTexture_ = Textures::create(font, "Press [space] to CONTINUE", endColor_,
                                 renderer, tempWidth, tempHeight);
  endRect_ = {(windowWidth / 2) - (tempWidth / 2),
              windowHeight - tempHeight - 120,
              tempWidth, tempHeight};

  music_ = Music::load("new_theme");
}

PageAction Endgame::draw(SDL_Renderer *renderer)
{
  SDL_RenderCopy(renderer, textTexture_, nullptr, &textRect_);
  SDL_RenderCopy(renderer, scoreTexture_, nullptr, &scoreRect_);
  SDL_RenderCopy(renderer, levelTexture_, nullptr, &levelRect_);
  SDL_RenderCopy(renderer, linesTexture_, nullptr, &linesRect_);
  SDL_RenderCopy(renderer, timeTexture_, nullptr, &timeRect_);
  SDL_RenderCopy(renderer, endTexture_, nullptr, &endRect_);

  return PageAction::None;
}

void Endgame::start()
{
  score_ = ingame_->getScore();
  time_ = ingame_->getTime();
  level_ = ingame_->getLevel();
  lines_ = ingame_->getLines();

  int tempWidth, tempHeight;

  std::string scoreStd = "Score : " + std::to_string(score_);
  scoreTexture_ = Textures::create(font_, scoreStd.c_str(), scoreColor_,
                                   renderer_, tempWidth, tempHeight);
  scoreRect_ = {textRect_.x + 150, textRect_.y + 120, tempWidth, tempHeight};

  std::string levelStd = "Level : " + std::to_string(level_);
  levelTexture_ = Textures::create(font_, levelStd.c_str(), levelColor_,
                                   renderer_, tempWidth, tempHeight);
  levelRect_ = {scoreRect_.x, scoreRect_.y + 60, tempWidth, tempHeight};

  std::string linesStd = "Lines : " + std::to_string(lines_);
  linesTexture_ = Textures::create(font_, linesStd.c_str(), linesColor_,
                                   renderer_, tempWidth, tempHeight);
  linesRect_ = {levelRect_.x, levelRect_.y + 60, tempWidth, tempHeight};

  updateTime(time_);

  Music::play(music_);
}

PageAction Endgame::handleInput(SDL_Event event)
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

void Endgame::updateTime(std::chrono::duration<double> time)
{
  uint minutes =
      std::chrono::duration_cast<std::chrono::minutes>(time).count();
  uint seconds =
      std::chrono::duration_cast<std::chrono::seconds>(time).count() %
      60;

  std::string newTime = "Time  : ";
  if (minutes < 10)
    newTime += "0";
  newTime += std::to_string(minutes);
  newTime += ':';
  if (seconds < 10)
    newTime += "0";
  newTime += std::to_string(seconds);

  timeTexture_ = Textures::create(font_, newTime.c_str(), timeColor_, renderer_);
}
