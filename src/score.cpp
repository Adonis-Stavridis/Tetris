#include "score.hpp"

Score::Score() : value(0)
{
}

Score::~Score()
{
}

void Score::draw(SDL_Renderer *renderer_)
{
  const char *text = "Score";

  SDL_assert(text);
  SDL_Color color = {0xFF, 0xFA, 0xFA, 0xFF};

  SDL_Surface *pSurface = TTF_RenderText_Blended(m_pFont, text, color);
  SDL_Texture *pTexture = SDL_CreateTextureFromSurface(m_pSdlRenderer, pSurface);
  int width, height;
  SDL_QueryTexture(pTexture, NULL, NULL, &width, &height);
  SDL_Rect dstRect = {x, y, width, height};
  SDL_RenderCopy(m_pSdlRenderer, pTexture, nullptr, &dstRect);
  SDL_DestroyTexture(pTexture);
  SDL_FreeSurface(pSurface);
}
