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

#include "gamepage.hpp"
#include "board.hpp"
#include "scoreviewer.hpp"
#include "queueviewer.hpp"
#include "tetromino.hpp"

#define TETROQUEUE_SIZE 4

#define MUSIC_NUMBER 5

typedef std::chrono::_V2::system_clock::time_point TimeStamp;
typedef std::chrono::duration<double> Duration;

/**
 * @brief Main game page
 * 
 */
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
  QueueViewer queueViewer_;

  Tetromino *curTetromino_;
  Tetromino ghostTetromino_;

  std::queue<Tetromino> tetroQueue_;

  std::array<Mix_Music *, MUSIC_NUMBER> music_;
  uint curMusic_;

  /**
   * @brief Initialize Tetromino queue
   * 
   * @return Tetromino* 
   */
  Tetromino *initTetroQueue();

  /**
   * @brief Get the front of the Tetromino queue and append a Tetromino to the 
   * back
   * 
   * @return Tetromino* 
   */
  Tetromino *getTetroQueue();

  /**
   * @brief Get a random Tetromino
   * 
   * @return Tetromino 
   */
  Tetromino spawnTetromino();

  /**
   * @brief Update ingame time
   * 
   */
  void updateTime();

  /**
   * @brief Make Tetromino fall at different intervals
   * 
   */
  void tetroFall();

  /**
   * @brief Translate Tetromino in a certain direction
   * 
   * @param translation 
   */
  void tetroTranslate(TetrominoTranslation translation);

  /**
   * @brief Rotate Tetromino in a certain direction
   * 
   * @param rotation 
   */
  void tetroRotate(TetrominoRotation rotation);

  /**
   * @brief Lock Tetromino to board
   * 
   */
  void tetroLock();

  /**
   * @brief Update Ghost tetromino
   * 
   */
  void updateGhost();

  /**
   * @brief Make Tetromino hard drop
   * 
   */
  void hardDrop();

  /**
   * @brief Update score values
   * 
   * @param lines 
   */
  void updateScore(uint lines);

  /**
   * @brief Play music set
   * 
   */
  void playMusic();

public:
  /**
   * @brief Construct a new Ingame object
   * 
   * @param windowWidth 
   * @param windowHeight 
   */
  Ingame(const int windowWidth, const int windowHeight);

  /**
   * @brief Destroy the Ingame object
   * 
   */
  ~Ingame();

  /**
   * @brief Init the Ingame object
   * 
   * @param renderer 
   * @param font 
   */
  void init(SDL_Renderer *renderer, TTF_Font *font);

  /**
   * @brief Draw Ingame's components
   * 
   * @param renderer 
   * @return PageAction 
   */
  PageAction draw(SDL_Renderer *renderer);

  /**
   * @brief Reset page's components
   * 
   */
  void start();

  /**
   * @brief Handle inputs
   * 
   * @param event 
   * @return PageAction 
   */
  PageAction handleInput(SDL_Event event);

  /**
   * @brief Get the Score value
   * 
   * @return uint 
   */
  inline uint getScore()
  {
    return score_;
  }

  /**
   * @brief Get the Time value
   * 
   * @return Duration 
   */
  inline Duration getTime()
  {
    return curTime_;
  }

  /**
   * @brief Get the Level value
   * 
   * @return uint 
   */
  inline uint getLevel()
  {
    return level_;
  }

  /**
   * @brief Get the Lines value
   * 
   * @return uint 
   */
  inline uint getLines()
  {
    return lineClear_;
  }
};

#endif // INGAME_HPP
