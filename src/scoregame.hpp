#ifndef SCOREGAME_HPP
#define SCOREGAME_HPP

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "gamepage.hpp"
#include "endgame.hpp"
#include "pseudogame.hpp"
#include "colors.hpp"

#define NEW_THEME_MUSIC "assets/music/new_theme.mp3"

class Scoregame : public GamePage
{
private:

    const char *text_;
    SDL_Color textColor_;

    SDL_Rect textRect_;
    SDL_Texture *textTexture_;

    SDL_Renderer *renderer_;
    TTF_Font *font_;
    Endgame *endgame_;
    Pseudogame *pseudogame_;

    uint score;
    std::string pseudo_;

    Mix_Music *music_;

  public:
    Scoregame();
    ~Scoregame();

    void init(SDL_Renderer *renderer, TTF_Font *font, const int windowWidth, const int windowHeight, Endgame *endgame, Pseudogame *Pseudogame);
    PageAction draw(SDL_Renderer *renderer);
    void start();
    PageAction handleInput(SDL_Event event);
};

#endif // SCOREGAME_HPP
