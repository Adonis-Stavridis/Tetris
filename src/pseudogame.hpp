#ifndef PSEUDOGAME_HPP
#define PSEUDOGAME_HPP

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "gamepage.hpp"
#include "endgame.hpp"
#include "colors.hpp"

#define NEW_THEME_MUSIC "assets/music/new_theme.mp3"

class Pseudogame : public GamePage
{
private:

    const char *text_;
    SDL_Color textColor_, pseudoColor_, endColor_;

    SDL_Rect textRect_, pseudoRect_, endRect_;
    SDL_Texture *textTexture_, *pseudoTexture_, *endTexture_;

    int cpt_;
    std::string pseudo_;

    SDL_Renderer *renderer_;
    TTF_Font *font_;
    Endgame *endgame_;

    Mix_Music *music_;

  public:
    Pseudogame();
    ~Pseudogame();

    void init(SDL_Renderer *renderer, TTF_Font *font, const int windowWidth, const int windowHeight, Endgame *endgame);
    PageAction draw(SDL_Renderer *renderer);
    void start();
    PageAction handleInput(SDL_Event event);
};

#endif // PSEUDOGAME_HPP
