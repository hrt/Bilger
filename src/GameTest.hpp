#ifndef GAMETEST_HPP
#define GAMETEST_HPP

class GameTest
{
public:
  bool test();
private:
  bool isEmptyTest();
  bool isPufferFishTest();
  bool isJellyFishTest();
  bool isCrabTest();
  bool isMoveableTest();
  bool performSwapTest();
};

#endif
