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
  tetroRects_.reserve(4);

  tetroRects_[0] =
      {textRect_.x + textRect_.w - 175,
       textRect_.y + textRect_.h + 50, 175, 175};
  tetroRects_[1] =
      {tetroRects_[0].x + tetroRects_[0].w - 100,
       tetroRects_[0].y + tetroRects_[0].h + 20, 100, 100};
  tetroRects_[2] =
      {tetroRects_[1].x, tetroRects_[1].y + tetroRects_[1].h + 20, 100, 100};
  tetroRects_[3] =
      {tetroRects_[2].x, tetroRects_[2].y + tetroRects_[2].h + 20, 100, 100};
}

void QueueViewer::draw(SDL_Renderer *renderer)
{
  SDL_RenderCopy(renderer, textTexture_, nullptr, &textRect_);

  for (size_t idx = 0; idx < queue_.size(); idx++)
  {
    const Tetromino &tetromino = queue_[idx];

    const Matrix tetroMatrix = tetromino.getMatrix();
    const size_t isize = tetroMatrix.size();
    const size_t jsize = tetroMatrix[0].size();
    const SDL_Color tetroColor = tetromino.getColor();

    const int tetroWidth = tetromino.getWidth() + 1;
    const int tetroHeight = tetromino.getHeight() + 1;
    const int maxWidthHeight = std::max(tetroWidth, tetroHeight);

    SDL_SetRenderDrawColor(renderer, tetroColor.r, tetroColor.g, tetroColor.b,
                           tetroColor.a);
    for (size_t i = 0; i < isize; i++)
    {
      for (size_t j = 0; j < jsize; j++)
      {
        if (tetroMatrix[i][j])
        {
          int ivalue = static_cast<int>(i);
          int jvalue = static_cast<int>(j);

          SDL_Rect tetroRect =
              {tetroRects_[idx].x +
                   (tetroRects_[idx].w / maxWidthHeight) * ivalue + 1,
               tetroRects_[idx].y +
                   (tetroRects_[idx].h / maxWidthHeight) * jvalue + 1,
               (tetroRects_[idx].w / maxWidthHeight) - 1,
               (tetroRects_[idx].h / maxWidthHeight) - 1};
          SDL_RenderFillRect(renderer, &tetroRect);
        }
      }
    }

    SDL_SetRenderDrawColor(renderer, textColor_.r, textColor_.g, textColor_.b,
                           textColor_.a);
    SDL_RenderDrawRect(renderer, &tetroRects_[idx]);
  }
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
