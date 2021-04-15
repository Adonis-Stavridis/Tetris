#include "queueviewer.hpp"

QueueViewer::QueueViewer(const int windowWidth)
    : text_("Tetrominos"),
      textColor_(Colors::snow()),
      textTexture_(nullptr),
      textRect_({windowWidth - 50, 50, 0, 0})
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
  textRect_ = {textRect_.x - tempWidth, 50, tempWidth, tempHeight};
  SDL_FreeSurface(tempSurface);

  queue_.reserve(4);
}

void QueueViewer::draw(SDL_Renderer *renderer)
{
  SDL_RenderCopy(renderer, textTexture_, nullptr, &textRect_);

  // for (const Tetromino &tetro : queue_)
  // {
  // }
}

void QueueViewer::updateQueue(std::queue<Tetromino> queue)
{
  queue_.clear();

  while (!queue.empty())
  {
    Tetromino tetro = queue.front();
    queue_.push_back(tetro);
    queue.pop();
  }
}
