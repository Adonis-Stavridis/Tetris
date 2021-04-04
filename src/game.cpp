#include "game.hpp"

Game::Game()
    : windowTitle_("Tetris"),
      windowWidth_(1280),
      windowHeight_(720),
      bgColor_({0x28, 0x28, 0x28, 0xFF}),
      startgame_(Startgame()),
      ingame_(Ingame(windowWidth_, windowHeight_)),
      gamePage_(&startgame_)
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
    std::cerr << "Could not initialize renderer. SDL Error: " << SDL_GetError()
              << std::endl;
    return false;
  }

  if (TTF_Init() < 0)
  {
    std::cerr << "Could not initialize TTF. TTF Error: " << TTF_GetError()
              << std::endl;
    exit(EXIT_FAILURE);
  }

  font_ = TTF_OpenFont(FONT_PATH, FONT_SIZE);
  if (!font_)
  {
    std::cerr << "TTF_OpenFont failed: " << TTF_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }

  startgame_.init(renderer_, font_, windowWidth_, windowHeight_);
  ingame_.init(renderer_, font_);

  running_ = true;

  return true;
}

void Game::run()
{
  while (running_)
  {
    while (SDL_PollEvent(&event_))
    {
      PageAction action = gamePage_->handleInput(event_);
      checkEvent(action);

      if (event_.type == SDL_QUIT)
        running_ = false;
    }

    draw();
  }
}

void Game::draw()
{
  SDL_SetRenderDrawColor(
      renderer_, bgColor_.r, bgColor_.g, bgColor_.b, bgColor_.a);
  SDL_RenderClear(renderer_);

  gamePage_->draw(renderer_);

  SDL_RenderPresent(renderer_);
}

void Game::quit()
{
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);

  TTF_Quit();
  SDL_Quit();
}

void Game::checkEvent(PageAction action)
{
  static uint currentState = 0;
  static GamePage *gameStates[PAGE_NUMBER] =
      {&startgame_, &ingame_};

  switch (action)
  {
  case PageAction::None:
    // nothing
    break;

  case PageAction::NextPage:
    currentState = (currentState + 1) % PAGE_NUMBER;
    gamePage_ = gameStates[currentState];
    break;

  case PageAction::Quit:
    running_ = false;
    break;

  default:
    std::cerr << "Game Error: Unknown PageAction" << std::endl;
    break;
  }
}
