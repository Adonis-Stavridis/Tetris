#include "game.hpp"

Game::Game()
{
  windowTitle_ = "Tetris";
  windowWidth_ = 800;
  windowHeight_ = 850;
  boardPositionX_ = 50;
  boardPositionY_ = 50;
}

Game::Game(std::string windowTitle, int windowWidth, int windowHeight)
{
  windowTitle_ = windowTitle;
  windowWidth_ = windowWidth;
  windowHeight_ = windowHeight;
  boardPositionX_ = 50;
  boardPositionY_ = 50;
}

Game::~Game()
{
}

bool Game::init()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    printf("Could not initialize SDL. SDL Error: %s\n", SDL_GetError());
    return false;
  }

  window_ = SDL_CreateWindow(
      windowTitle_.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      windowWidth_, windowHeight_, SDL_WINDOW_SHOWN);
  if (window_ == NULL)
  {
    printf("Could not create window. SDL Error: %s\n", SDL_GetError());
    return false;
  }

  renderer_ = SDL_CreateRenderer(
      window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer_ == NULL)
  {
    printf("Could not initialize renderer. SDL_Error: %s", SDL_GetError());
    return false;
  }

  windowSurface_ = SDL_GetWindowSurface(window_);
  if (SDL_FillRect(windowSurface_, NULL,
                   SDL_MapRGB(windowSurface_->format, 0xFF, 0xFF, 0xFF)) == -1)
  {
    printf("Could not fill rectangle. SDL_Error: %s", SDL_GetError());
    return false;
  }

  running_ = true;

  return true;
}

void Game::loadMedia()
{
  // _blockTexture.loadFromFile("res/block.png", renderer_, 0.35f);
  // _board.setTexture(_blockTexture);
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
  SDL_SetRenderDrawColor(renderer_, 0x28, 0x28, 0x28, 0xFF);
  SDL_RenderClear(renderer_);

  // board_.draw(renderer_);

  SDL_RenderPresent(renderer_);
}
