#include "game.hpp"

Game::Game()
    : windowTitle_("Tetris"),
      windowWidth_(1280),
      windowHeight_(720),
      window_(nullptr),
      renderer_(nullptr),
      font_(nullptr),
      bgColor_(Colors::background()),
      running_(false),
      startgame_(Startgame()),
      ingame_(Ingame(windowWidth_, windowHeight_)),
      endgame_(Endgame()),
      pseudogame_(Pseudogame()),
      scoregame_(Scoregame()),
      gamePage_(&startgame_)
{
}

Game::~Game()
{
}

void Game::init()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    std::cerr << "Could not initialize SDL. SDL Error: " << SDL_GetError()
              << std::endl;
    exit(EXIT_FAILURE);
  }

  window_ = SDL_CreateWindow(
      windowTitle_.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      windowWidth_, windowHeight_, SDL_WINDOW_SHOWN);
  if (window_ == NULL)
  {
    std::cerr << "Could not create window. SDL Error: " << SDL_GetError()
              << std::endl;
    exit(EXIT_FAILURE);
  }

  renderer_ = SDL_CreateRenderer(
      window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer_ == NULL)
  {
    std::cerr << "Could not initialize renderer. SDL Error: " << SDL_GetError()
              << std::endl;
    exit(EXIT_FAILURE);
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

  Music::init();

  startgame_.init(renderer_, font_, windowWidth_, windowHeight_);
  ingame_.init(renderer_, font_);
  endgame_.init(renderer_, font_, windowWidth_, windowHeight_, &ingame_);
  pseudogame_.init(renderer_, font_, windowWidth_, windowHeight_, &endgame_);
  scoregame_.init(renderer_, font_, windowWidth_, windowHeight_, &endgame_,
                  &pseudogame_);

  running_ = true;

  gamePage_->start();
}

void Game::run()
{
  SDL_Event event;

  while (running_)
  {
    while (SDL_PollEvent(&event))
    {
      PageAction action = gamePage_->handleInput(event);
      checkEvent(action);

      if (event.type == SDL_QUIT)
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

  PageAction action = gamePage_->draw(renderer_);
  checkEvent(action);

  SDL_RenderPresent(renderer_);
}

void Game::quit()
{
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);

  TTF_Quit();

  Music::close();

  SDL_Quit();
}

void Game::checkEvent(PageAction action)
{
  static uint currentState = 0;
  static GamePage *gameStates[PAGE_NUMBER] =
      {&startgame_, &ingame_, &endgame_, &pseudogame_, &scoregame_};

  switch (action)
  {
  case PageAction::None:
    // nothing
    break;

  case PageAction::NextPage:
    currentState = (currentState + 1) % PAGE_NUMBER;
    gamePage_ = gameStates[currentState];
    gamePage_->start();
    break;

  case PageAction::Quit:
    running_ = false;
    break;

  default:
    std::cerr << "Game Error: Unknown PageAction" << std::endl;
    break;
  }
}
