#ifndef COLORS_HPP
#define COLORS_HPP

#include <SDL2/SDL.h>

/**
 * @brief A collection of colors
 * 
 */
namespace Colors
{

  /**
   * @brief Matt black color (background)
   * 
   * @return const SDL_Color 
   */
  inline const SDL_Color background()
  {
    return {0x28, 0x28, 0x28, 0xFF};
  }

  /**
   * @brief Gold color
   * 
   * @return const SDL_Color 
   */
  inline const SDL_Color gold()
  {
    return {0xFF, 0xD7, 0x00, 0xFF};
  }

  /**
   * @brief Snow color (main text color)
   * 
   * @return const SDL_Color 
   */
  inline const SDL_Color snow()
  {
    return {0xFF, 0xFA, 0xFA, 0xFF};
  }

  /**
   * @brief Darkgrey color
   * 
   * @return const SDL_Color 
   */
  inline const SDL_Color darkgrey()
  {
    return {0x40, 0x40, 0x40, 0xFF};
  }

  /**
   * @brief Grey color
   * 
   * @return const SDL_Color 
   */
  inline const SDL_Color grey()
  {
    return {0x50, 0x50, 0x50, 0xFF};
  }

  /**
   * @brief Tomato color
   * 
   * @return const SDL_Color 
   */
  inline const SDL_Color tomato()
  {
    return {0xFF, 0x63, 0x47, 0xFF};
  }

  /**
   * @brief Orange color
   * 
   * @return const SDL_Color 
   */
  inline const SDL_Color orange()
  {
    return {0xFF, 0xA5, 0x00, 0xFF};
  }

  /**
   * @brief Dodgerblue color
   * 
   * @return const SDL_Color 
   */
  inline const SDL_Color dodgerblue()
  {
    return {0x1E, 0x90, 0xFF, 0xFF};
  }

  /**
   * @brief Mediumseagreen color
   * 
   * @return const SDL_Color 
   */
  inline const SDL_Color mediumseagreen()
  {
    return {0x3C, 0xB3, 0x71, 0xFF};
  }

  /**
   * @brief Slateblue color
   * 
   * @return const SDL_Color 
   */
  inline const SDL_Color slateblue()
  {
    return {0x6A, 0x5A, 0xCD, 0xFF};
  }

  /**
   * @brief Violet color
   * 
   * @return const SDL_Color 
   */
  inline const SDL_Color violet()
  {
    return {0xEE, 0x82, 0xEE, 0xFF};
  }

  /**
   * @brief Azure color
   * 
   * @return const SDL_Color 
   */
  inline const SDL_Color azure()
  {
    return {0xF0, 0xFF, 0xFF, 0xFF};
  }

} // namespace Colors

#endif // COLOLS_HPP
