#ifndef ENDGAME_HPP
#define ENDGAME_HPP

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "gamepage.hpp"
#include "ingame.hpp"

class Endgame : public GamePage
{
private:

    const char *text_;
    SDL_Color textColor_;

    SDL_Rect textRect_, scoreRect_;
    SDL_Texture *textTexture_, *scoreTexture_;

    //To get score + time and print them
    int score_;
    SDL_Renderer *renderer_;
    TTF_Font *font_;
    Ingame *ingame_;

public:
    Endgame();
    ~Endgame();

    void init(SDL_Renderer *renderer, TTF_Font *font, const int windowWidth, const int windowHeight, Ingame *ingame);
    PageAction draw(SDL_Renderer *renderer);
    void start();
    PageAction handleInput(SDL_Event event);
};

#endif // ENDGAME_HPP
