#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace Textures
{
  inline SDL_Texture *init(TTF_Font *font, const char *text, SDL_Color color,
                           SDL_Renderer *renderer, int &width, int &height)
  {
    SDL_Surface *tempSurface = TTF_RenderText_Blended(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    SDL_FreeSurface(tempSurface);

    return texture;
  }
} // namespace Textures

#endif // TEXTURES_HPP
