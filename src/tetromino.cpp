#include "tetromino.hpp"

Tetromino::Tetromino()
{
}

Tetromino::~Tetromino()
{
}

std::queue<int> Tetromino::randomTetromino()
{
  int random;
  srand(time(NULL));
  // Fill the queue to always see the next tetromino + actual tetromino
  while(randomTetromino_.size() < 5)
  {
    std::cout << "IM IN" << std::endl;
    random = rand() % 7;
    std::cout << random << std::endl;
    randomTetromino_.push(random);
  }  
  return randomTetromino_;
}

Tetromino::tetromino Tetromino::rotate(tetromino t)
{
  tetromino tmp = t;
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; j++)
      {
        t.matrix[j][i] = tmp.matrix[i][j];
      }
  }
  return t;  
}

void Tetromino::move(tetromino t, int x, int y)
{
  t.pos.first += x;
  t.pos.second += y;
}

