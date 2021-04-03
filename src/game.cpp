#include "game.hpp"

Game::Game()
    : windowTitle_("Tetris"),
      windowWidth_(1280),
      windowHeight_(720),
      board_(Board(windowWidth_, windowHeight_)),
      score_(Score()),
      bgColor_({0x28, 0x28, 0x28, 0xFF}),
      state_(GameState::Startgame)
{
}

Game::Game(std::string windowTitle, int windowWidth, int windowHeight)
    : windowTitle_(windowTitle),
      windowWidth_(windowWidth),
      windowHeight_(windowHeight),
      board_(Board(windowWidth_, windowHeight_)),
      score_(Score()),
      bgColor_({0x28, 0x28, 0x28, 0xFF}),
      state_(GameState::Startgame)
{
}

Game::~Game()
{
}

bool Game::init()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    std::cerr << "Could not initialize SDL. SDL Error: " << SDL_GetError()
              << std::endl;
    return false;
  }

  window_ = SDL_CreateWindow(
      windowTitle_.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      windowWidth_, windowHeight_, SDL_WINDOW_SHOWN);
  if (window_ == NULL)
  {
    std::cerr << "Could not create window. SDL Error: " << SDL_GetError()
              << std::endl;
    return false;
  }

  renderer_ = SDL_CreateRenderer(
      window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer_ == NULL)
  {
    std::cerr << "Could not initialize renderer. SDL_Error: " << SDL_GetError()
              << std::endl;
    return false;
  }

  score_.init(renderer_);

  running_ = true;

  return true;
}

void Game::run()
{
  while (running_)
  {
    while (SDL_PollEvent(&event_))
    {
      if (event_.type == SDL_QUIT)
        running_ = false;
      if (event_.type == SDL_KEYDOWN)
        running_ = false;
      // board_.handleInput(event_);
    }

    // board_.update();
    draw();
  }
}

void Game::draw()
{
  SDL_SetRenderDrawColor(
      renderer_, bgColor_.r, bgColor_.g, bgColor_.b, bgColor_.a);
  SDL_RenderClear(renderer_);

  board_.draw(renderer_);
  score_.draw(renderer_);

  SDL_RenderPresent(renderer_);
}

void Game::quit()
{
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);

  SDL_Quit();
}
