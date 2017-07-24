#include "GameTest.hpp"
#include "Game.hpp"

bool GameTest::test()
{
  bool allPassed = true;

  allPassed &= isEmptyTest();
  allPassed &= isPufferFishTest();
  allPassed &= isJellyFishTest();
  allPassed &= isCrabTest();
  allPassed &= isMoveableTest();
  allPassed &= performSwapTest();

  return allPassed;
}

bool GameTest::isEmptyTest()
{
  bool allPassed = true;

  allPassed &= isEmpty(EMPTY);
  allPassed &= !isEmpty(CRAB);
  allPassed &= !isEmpty(JELLYFISH);
  allPassed &= !isEmpty(PUFFERFISH);
  allPassed &= !isEmpty('A');
  allPassed &= !isEmpty('1');

  return allPassed;
}

bool GameTest::isPufferFishTest()
{
  bool allPassed = true;

  allPassed &= !isPufferFish(EMPTY);
  allPassed &= !isPufferFish(CRAB);
  allPassed &= !isPufferFish(JELLYFISH);
  allPassed &= isPufferFish(PUFFERFISH);
  allPassed &= !isPufferFish('A');
  allPassed &= !isPufferFish('1');

  return allPassed;
}

bool GameTest::isJellyFishTest()
{
  bool allPassed = true;

  allPassed &= !isJellyFish(EMPTY);
  allPassed &= !isJellyFish(CRAB);
  allPassed &= isJellyFish(JELLYFISH);
  allPassed &= !isJellyFish(PUFFERFISH);
  allPassed &= !isJellyFish('A');
  allPassed &= !isJellyFish('1');

  return allPassed;
}

bool GameTest::isCrabTest()
{
  bool allPassed = true;

  allPassed &= !isCrab(EMPTY);
  allPassed &= isCrab(CRAB);
  allPassed &= !isCrab(JELLYFISH);
  allPassed &= !isCrab(PUFFERFISH);
  allPassed &= !isCrab('A');
  allPassed &= !isCrab('1');

  return allPassed;
}

bool GameTest::isMoveableTest()
{
  bool allPassed = true;

  allPassed &= !isMoveable(EMPTY);
  allPassed &= !isMoveable(CRAB);
  allPassed &= !isMoveable(JELLYFISH);
  allPassed &= !isMoveable(PUFFERFISH);
  allPassed &= isMoveable('A');
  allPassed &= isMoveable('1');

  return allPassed;
}

bool GameTest::performSwapTest()
{
  bool allPassed = true;

  board_t board;
  for (int i = 0; i < 72; i++)
    board.push_back(i);

  performSwap(board, 0, 0);

  for (int i = 2; i < 72; i++)
    allPassed &= board[i] == i;

  allPassed &= board[1] == 0;
  allPassed &= board[0] == 1;

  return allPassed;
}
