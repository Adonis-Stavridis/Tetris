#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace Textures
{
  static int defaultValue = 0;

  inline SDL_Texture *create(TTF_Font *font, const char *text, SDL_Color color,
                           SDL_Renderer *renderer, int &width = defaultValue,
                           int &height = defaultValue)
  {
    SDL_Surface *tempSurface = TTF_RenderText_Blended(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    SDL_FreeSurface(tempSurface);

    return texture;
  }
} // namespace Textures

#endif // TEXTURES_HPP
