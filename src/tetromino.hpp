#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include <SDL2/SDL.h>
#include <utility>
#include <queue>
#include <iostream>

class Tetromino
{
private:
    struct tetromino
    {
        int matrix[4][4];
        SDL_Color tetrominoColor;
        std::pair<int,int> pos;
    };

    tetromino tab[7] =
    {
        {
            {{1,1,1,1}
            ,{0,0,0,0}
            ,{0,0,0,0}
            ,{0,0,0,0}},
            {0x00,0xFF,0xFF,0xFF},
            {0,0},
        },
        {
            {{1,1,0,0}
            ,{1,1,0,0}
            ,{0,0,0,0}
            ,{0,0,0,0}},
            {0xFF,0xFF,0x0,0xFF},
            {0,0},
        },
        {
            {{1,1,1,0}
            ,{0,1,0,0}
            ,{0,0,0,0}
            ,{0,0,0,0}},
            {0x8B,0x00,0x8B,0xFF},
            {0,0},
        },
        {
            {{1,1,1,0}
            ,{1,0,0,0}
            ,{0,0,0,0}
            ,{0,0,0,0}},
            {0xFF,0x8C,0x00,0xFF},
            {0,0},
        },
        {
            {{1,1,1,0}
            ,{0,0,1,0}
            ,{0,0,0,0}
            ,{0,0,0,0}},
            {0x00,0x00,0xFF,0xFF},
            {0,0},
        },
        {
            {{1,1,0,0}
            ,{0,1,1,0}
            ,{0,0,0,0}
            ,{0,0,0,0}},
            {0xFF,0x00,0x00,0xFF},
            {0,0},
        },
        {
            {{0,1,1,0}
            ,{1,1,0,0}
            ,{0,0,0,0}
            ,{0,0,0,0}},
            {0x00,0xFF,0x00,0xFF},
            {0,0}
        }
    };

public:

    std::queue<int> randomTetromino_;

    std::queue<int> randomTretromino();
    void randomPosition();

};

#endif // TETROMINO_HPP
