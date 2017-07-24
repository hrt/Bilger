#include <iostream>
#include "GameTest.hpp"
#include "ParserTest.hpp"

int main()
{
  GameTest gameTest;
  ParserTest parserTest;

  bool allPassed = true;

  allPassed &= parserTest.test();
  allPassed &= gameTest.test();

  if (!allPassed)
  {
    std::cout << "Tests failed.." << std::endl;
    return 1;
  }
  else
  {
    std::cout << "Tests passed.." << std::endl;
    return 0;
  }
}
