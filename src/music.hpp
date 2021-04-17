#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <string>
#include <SDL2/SDL_mixer.h>

#define MUSIC_PATH "assets/music/"

#define MUSIC_ENABLED false

/**
 * @brief Set of functions to handle Music and Sound
 * 
 */
namespace Music
{
  /**
   * @brief Init Music module
   * 
   */
  inline void init()
  {
    if (Mix_OpenAudio(
            44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
      std::cerr << "Mix_OpenAudio failed: " << Mix_GetError() << std::endl;
      exit(EXIT_FAILURE);
    }

    Mix_VolumeMusic(MIX_MAX_VOLUME / 5);
  }

  /**
   * @brief Load a music mp3 file
   * 
   * @param filename 
   * @return Mix_Music* 
   */
  inline Mix_Music *load(const char *filename)
  {
    std::string path(MUSIC_PATH);
    path += filename;
    path += ".mp3";

    Mix_Music *music = Mix_LoadMUS(path.c_str());
    if (!music)
    {
      std::cerr << "Mix_LoadMUS failed!" << std::endl;
      exit(EXIT_FAILURE);
    }

    return music;
  }

  /**
   * @brief Play music
   * 
   * @param music 
   * @param loop 
   */
  inline void play(Mix_Music *music, bool loop = true)
  {
    if (!MUSIC_ENABLED)
      return;

    int loopVal = loop ? -1 : 1;

    if (Mix_PlayMusic(music, loopVal) == -1)
    {
      std::cerr << "Mix_PlayMusic failed!" << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  /**
   * @brief Close Music module
   * 
   */
  inline void close()
  {
    Mix_CloseAudio();
  }
} // namespace Music

#endif // MUSIC_HPP
