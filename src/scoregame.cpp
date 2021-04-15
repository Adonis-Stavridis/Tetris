#include "scoregame.hpp"

Scoregame::Scoregame()
    : text_("Table of Highscores"),
      textColor_(Colors::gold()),
      pseudoColor_(Colors::dodgerblue()),
      score_(0),
      music_(nullptr)
{
}

Scoregame::~Scoregame()
{
  // SDL_DestroyTexture(textTexture_);

  Mix_FreeMusic(music_);
}

void Scoregame::init(SDL_Renderer *renderer, TTF_Font *font,
                     const int windowWidth, const int windowHeight,
                     Endgame *endgame, Pseudogame *pseudogame)
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
  pseudogame_ = pseudogame;
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
  for (int i = 0; i < 9; i++)
  {
    SDL_RenderCopy(renderer, pseudoTexture_[i], nullptr, &pseudoRect_[i]);
  }

  return PageAction::None;
}

void Scoregame::start()
{
  pseudo_ = pseudogame_->getPseudo();
  score_ = endgame_->getScore();
  pseudo_.erase(
      remove_if(pseudo_.begin(), pseudo_.end(), isspace), pseudo_.end());

  high_.clear();

  std::ifstream inputFile;
  inputFile.open("highscores.csv");

  std::string line;
  std::string name;
  uint scoreFile;

  // Read pseudo and score in the file
  while (std::getline(inputFile, line))
  {
    std::istringstream iss(line);
    iss >> name >> scoreFile;
    high_.push_back(std::make_pair(name, scoreFile));
  }
  inputFile.close();

  size_t idx;
  for (idx = 0; idx < high_.size(); idx++)
  {
    if (score_ >= high_[idx].second)
    {
      break;
    }
  }
  high_.insert(high_.begin() + idx, std::make_pair(pseudo_, score_));

  if (high_.size() > 9)
    high_.pop_back();

  std::ofstream outputFile;
  outputFile.open("highscores.csv");

  for (const auto &pair : high_)
  {
    outputFile << pair.first << " " << pair.second << "\n";
  }
  outputFile.close();

  int n = 100;
  for (size_t i = 0; i < 9; i++)
  {
    int tempWidth, tempHeight;

    std::string highscore = std::to_string(i + 1) + ". ";
    if (i < high_.size())
    {
      highscore += high_[i].first + " - " + std::to_string(high_[i].second);
    }

    SDL_Surface *tempSurface = TTF_RenderText_Blended(font_, highscore.c_str(), pseudoColor_);
    pseudoTexture_[i] = SDL_CreateTextureFromSurface(renderer_, tempSurface);
    SDL_QueryTexture(pseudoTexture_[i], NULL, NULL, &tempWidth, &tempHeight);
    tempWidth /= 2;
    tempHeight /= 2;

    if (i < 3)
    {
      int tmp = n * (i + 1);
      pseudoRect_[i] = {textRect_.x + 100, textRect_.y + 100 + tmp, tempWidth, tempHeight};
    }

    else if (i > 2 && i < 6)
    {
      int tmp = n * ((i % 3) + 1);
      pseudoRect_[i] = {textRect_.x + 500, textRect_.y + 100 + tmp, tempWidth, tempHeight};
    }

    else
    {
      int tmp = n * ((i % 3) + 1);
      pseudoRect_[i] = {textRect_.x + 900, textRect_.y + 100 + tmp, tempWidth, tempHeight};
    }

    SDL_FreeSurface(tempSurface);
  }

#ifdef MUSIC_ENABLED
  if (Mix_PlayMusic(music_, -1) == -1)
  {
    std::cerr << "Mix_PlayMusic failed!" << std::endl;
    exit(EXIT_FAILURE);
  }
#endif
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
