#include "ParserTest.hpp"
#include "Parser.hpp"
#include <string>

bool ParserTest::test()
{
  bool allPassed = true;

  allPassed &= parseBoardTest();

  return allPassed;
}

bool ParserTest::parseBoardTest()
{
  bool hasPassed = true;

  Parser parser;
  std::string expectedBoard = "ABCDBCADBABEDABCEAADEDAEEBBEEDDABCDACEDBADCACBDADDBDCDBADCCBBDDCDECCEBAD";
  board_t actualBoard = parser.parseBoard();

  for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
    hasPassed &= expectedBoard[i] == actualBoard[i];

  return hasPassed;
}
