#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <string>

#define MUSIC_PATH "assets/music/"

#define MUSIC_ENABLED false

namespace Music
{
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

  inline void close()
  {
    Mix_CloseAudio();
  }
} // namespace Music

#endif // MUSIC_HPP
