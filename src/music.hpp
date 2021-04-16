#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <string>

#define MUSIC_PATH "assets/music/"

#define MUSIC_ENABLED false

namespace Music
{
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
} // namespace Music

#endif // MUSIC_HPP
