#ifndef INGAME_HPP
#define INGAME_HPP

#include <iostream>
#include <time.h>
#include <queue>
#include <chrono>
#include <array>
#include <algorithm>
#include <random>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "gamepage.hpp"
#include "board.hpp"
#include "scoreviewer.hpp"
#include "tetromino.hpp"

#define TETROQUEUE_SIZE 4

#define AXEL_F_MUSIC "assets/music/axel_f.mp3"
#define BLUE_MUSIC "assets/music/blue.mp3"
#define BOHEMIAN_RHAPSODY_MUSIC "assets/music/bohemian_rhapsody.mp3"
#define HARDER_BETTER_FASTER_STRONGER_MUSIC \
  "assets/music/harder_better_faster_stronger.mp3"
#define RASPUTIN_MUSIC "assets/music/rasputin.mp3"
#define MUSIC_NUMBER 5

typedef std::chrono::_V2::system_clock::time_point TimeStamp;
typedef std::chrono::duration<double> Duration;

class Ingame : public GamePage
{
private:
  TimeStamp startTime_;
  Duration curTime_;

  int timeToFall_;
  int timeToPass_;

  bool endgame_;

  uint lineClear_;
  uint level_;
  uint score_;

  Board board_;
  ScoreViewer scoreViewer_;

  Tetromino *curTetromino_;

  std::queue<Tetromino> tetroQueue_;

  std::array<Mix_Music *, MUSIC_NUMBER> music_;

  Tetromino *initTetroQueue();
  Tetromino *getTetroQueue();
  Tetromino spawnTetromino();

  void updateTime();
  void tetroFall();

  void tetroTranslate(TetrominoTranslation translation);
  void tetroRotate(TetrominoRotation rotation);

  void updateScore(uint lines);

public:
  Ingame(const int windowWidth_, const int windowHeight_);
  ~Ingame();

  void init(SDL_Renderer *renderer, TTF_Font *font);
  PageAction draw(SDL_Renderer *renderer);
  void start();
  PageAction handleInput(SDL_Event event);

  inline uint getScore()
  {
    return score_;
  }

  inline Duration getTime()
  {
    return curTime_;
  }

  inline uint getLevel()
  {
    return level_;
  }
};

#endif // INGAME_HPP
