#include <iostream>
#include "Parser.hpp"
#include "Game.hpp"

int main()
{
  Parser parser;
  board_t board = parser.parseBoard();

  Game game(board);

  move_t bestMove = game.calculateMove();

  std::cout << "Score : " << bestMove.score << std::endl;
  std::cout << "Move : " << bestMove.x << ' ' << bestMove.y << std::endl;

  return 1;
}
