#ifndef ENDGAME_HPP
#define ENDGAME_HPP

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "gamepage.hpp"
#include "ingame.hpp"
#include "colors.hpp"

class Endgame : public GamePage
{
private:

    const char *text_;
    SDL_Color textColor_, scoreColor_, timeColor_;

    SDL_Rect textRect_, scoreRect_, timeRect_;
    SDL_Texture *textTexture_, *scoreTexture_, *timeTexture_;

    //To get score + time and print them
    int score_;
    std::chrono::duration<double> time_;
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
    void updateTime(SDL_Renderer *renderer, std::chrono::duration<double> time);
};

#endif // ENDGAME_HPP
