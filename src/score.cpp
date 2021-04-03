#include "score.hpp"

Score::Score()
    : value_(0),
      font_(nullptr),
      textColor_({0xFF, 0xFA, 0xFA, 0xFF}),
      valueColor_({0xFF, 0xD7, 0x00, 0xFF}),
      text_("Score")
{
  if (TTF_Init() < 0)
  {
    std::cerr << "Could not initialize TTF. TTF Error: " << TTF_GetError()
              << std::endl;
    exit(EXIT_FAILURE);
  }

  font_ = TTF_OpenFont("assets/fonts/PressStart2P-vaV7.ttf", FONT_SIZE);
  if (!font_)
  {
    std::cerr << "TTF_OpenFont failed: " << TTF_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }
}

Score::~Score()
{
  SDL_DestroyTexture(textTexture_);
  SDL_DestroyTexture(valueTexture_);

  TTF_Quit();
}

void Score::init(SDL_Renderer *renderer)
{
  SDL_Surface *tempSurface = TTF_RenderText_Blended(font_, text_, textColor_);
  textTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  int tempWidth, tempHeight;
  SDL_QueryTexture(textTexture_, NULL, NULL, &tempWidth, &tempHeight);
  textRect_ = {50, 50, tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);

  const char *valueText = std::to_string(value_).c_str();
  tempSurface = TTF_RenderText_Blended(font_, valueText, valueColor_);
  valueTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  SDL_QueryTexture(valueTexture_, NULL, NULL, &tempWidth, &tempHeight);
  valueRect_ =
      {textRect_.x + 10, textRect_.y + textRect_.h + 10, tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);
}

void Score::draw(SDL_Renderer *renderer)
{
  SDL_RenderCopy(renderer, textTexture_, nullptr, &textRect_);
  SDL_RenderCopy(renderer, valueTexture_, nullptr, &valueRect_);
}
