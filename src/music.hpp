#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <string>

#define MUSIC_PATH "assets/music/"

namespace Music
{
  inline std::string path(const char *music)
  {
    std::string path(MUSIC_PATH);
    path += music;
    path += ".mp3";

    return path;
  }
} // namespace Music

#endif // MUSIC_HPP
