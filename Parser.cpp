#include "Parser.hpp"
#include <iostream>

board_t Parser::parseBoard()
{
  board_t board;
  char c;
  std::cin >> c;
  while (isalpha(c))
  {
    board.push_back(c);
    std::cin >> c;
  }
  return board;
}
