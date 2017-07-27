#include "Parser.hpp"
#include <iostream>

board_t Parser::parseBoard()
{
  board_t board;
  char c;
  std::cin >>  std::noskipws;     // don't skip white space
  std::cin >> c;
  while (isalpha(c))
  {
    board.push_back(c);
    std::cin >> c;
  }
  return board;
}

int Parser::parseSearchDepth()
{
  return parseInt();
}

int Parser::parseWaterLevel()
{
  return parseInt();
}

int Parser::parseInt()
{
  int i;
  std::cin >> i;
  return i;
}
