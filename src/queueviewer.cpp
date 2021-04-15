#include "queueviewer.hpp"

QueueViewer::QueueViewer(const int windowWidth)
    : text_("Tetrominos"),
      textColor_(Colors::snow()),
      textTexture_(nullptr),
      textRect_({50, windowWidth - 50, 0, 0})
{
}

QueueViewer::~QueueViewer()
{
  // SDL_DestroyTexture(textTexture_);
}

void QueueViewer::init(SDL_Renderer *renderer, TTF_Font *font)
{
  SDL_Surface *tempSurface = TTF_RenderText_Blended(font, text_, textColor_);
  textTexture_ = SDL_CreateTextureFromSurface(renderer, tempSurface);
  int tempWidth, tempHeight;
  SDL_QueryTexture(textTexture_, NULL, NULL, &tempWidth, &tempHeight);
  textRect_ = {50, textRect_.y - tempWidth, tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);
}

void QueueViewer::start(std::queue<Tetromino> queue)
{
  while (!queue.empty())
  {
    queue.pop();
  }
}

void QueueViewer::draw(SDL_Renderer *renderer)
{
  SDL_RenderCopy(renderer, textTexture_, nullptr, &textRect_);

  // for (const Tetromino &tetro : queue_)
  // {
  // }
}
