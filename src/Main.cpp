#include <iostream>
#include "Parser.hpp"
#include "Game.hpp"

int main()
{
  Parser parser;
  board_t board = parser.parseBoard();
  int waterLevel = parser.parseWaterLevel();
  int searchDepth = parser.parseSearchDepth();

  Game game(board, waterLevel, searchDepth);

  move_t bestMove = game.calculateMove();

  std::cout << "Depth : " << searchDepth << std::endl;
  std::cout << "Water Level : " << waterLevel << std::endl;
  std::cout << "Score : " << bestMove.score << std::endl;
  std::cout << "Move : " << bestMove.x << ' ' << bestMove.y << std::endl;

  return 1;
}
