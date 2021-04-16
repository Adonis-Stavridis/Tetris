#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/**
 * @brief Handle textures
 * 
 */
namespace Textures
{
  // A default value for optional references
  static int defaultValue = 0;

  /**
   * @brief Create a texture 
   * 
   * @param font 
   * @param text 
   * @param color 
   * @param renderer 
   * @param width 
   * @param height 
   * @return SDL_Texture* 
   */
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
