#ifndef COLORS_HPP
#define COLORS_HPP

#include <SDL2/SDL.h>

namespace Colors
{

  inline const SDL_Color background()
  {
    return {0x28, 0x28, 0x28, 0xFF};
  }

  inline const SDL_Color gold()
  {
    return {0xFF, 0xD7, 0x00, 0xFF};
  }

  inline const SDL_Color snow()
  {
    return {0xFF, 0xFA, 0xFA, 0xFF};
  }

  inline const SDL_Color tomato()
  {
    return {0xFF, 0x63, 0x47, 0xFF};
  }

  inline const SDL_Color darkgrey()
  {
    return {0x40, 0x40, 0x40, 0xFF};
  }

  inline const SDL_Color grey()
  {
    return {0x50, 0x50, 0x50, 0xFF};
  }

} // namespace Colors

#endif
