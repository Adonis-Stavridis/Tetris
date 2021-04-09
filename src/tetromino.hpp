#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include <SDL2/SDL.h>
#include <utility>
#include <queue>
#include <iostream>

class Tetromino
{
private:
<<<<<<< HEAD
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

=======
>>>>>>> 5b690163d2adcc844380c1b4735414f6311b1f15
public:
  void randomTretromino();
  void randomPosition();
};

<<<<<<< HEAD
    std::queue<int> randomTetromino_;

    std::queue<int> randomTretromino();
    void randomPosition();

};

#endif // TETROMINO_HPP
=======
#endif // TETROMINO_HPP
>>>>>>> 5b690163d2adcc844380c1b4735414f6311b1f15
