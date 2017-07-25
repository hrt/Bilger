#include "gtest/gtest.h"
#include "Game.hpp"
#include "Definitions.hpp"

TEST(hsEmpty, HoldsTrueForEmpty)
{
  EXPECT_EQ(true, isEmpty(EMPTY));
}

TEST(isEmpty, holdsFalseForNonEmpty)
{
  EXPECT_EQ(false, isEmpty(PUFFERFISH));
  EXPECT_EQ(false, isEmpty(JELLYFISH));
  EXPECT_EQ(false, isEmpty(CRAB));
  EXPECT_EQ(false, isEmpty('A'));
  EXPECT_EQ(false, isEmpty('7'));
}

TEST(isPufferFish, holdsTrueForPufferFish)
{
  EXPECT_EQ(true, isPufferFish(PUFFERFISH));
}

TEST(isPufferFish, holdsFalseForNonPufferFish)
{
  EXPECT_EQ(false, isPufferFish(EMPTY));
  EXPECT_EQ(false, isPufferFish(JELLYFISH));
  EXPECT_EQ(false, isPufferFish(CRAB));
  EXPECT_EQ(false, isPufferFish('A'));
  EXPECT_EQ(false, isPufferFish('7'));
}

TEST(isJellyFish, holdsTrueForJellyFish)
{
  EXPECT_EQ(true, isJellyFish(JELLYFISH));
}

TEST(isJellyFish, holdsFalseForNonJellyFish)
{
  EXPECT_EQ(false, isJellyFish(EMPTY));
  EXPECT_EQ(false, isJellyFish(PUFFERFISH));
  EXPECT_EQ(false, isJellyFish(CRAB));
  EXPECT_EQ(false, isJellyFish('A'));
  EXPECT_EQ(false, isJellyFish('7'));
}

TEST(isCrab, holdsTrueForCrab)
{
  EXPECT_EQ(true, isCrab(CRAB));
}

TEST(isCrab, holdsFalseForNonCrab)
{
  EXPECT_EQ(false, isCrab(EMPTY));
  EXPECT_EQ(false, isCrab(PUFFERFISH));
  EXPECT_EQ(false, isCrab(JELLYFISH));
  EXPECT_EQ(false, isCrab('A'));
  EXPECT_EQ(false, isCrab('7'));
}

TEST(isMoveable, holdsTrueForMoveable)
{
  EXPECT_EQ(true, isMoveable('A'));
  EXPECT_EQ(true, isMoveable('7'));
  EXPECT_EQ(true, isMoveable(' '));
}

TEST(isMoveable, holdsFalseForNonMoveable)
{
  EXPECT_EQ(false, isMoveable(EMPTY));
  EXPECT_EQ(false, isMoveable(PUFFERFISH));
  EXPECT_EQ(false, isMoveable(JELLYFISH));
  EXPECT_EQ(false, isMoveable(CRAB));
}

TEST(performSwap, swapsTwoElements)
{
  board_t board;
  for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
    board.push_back(i);


  int x = 3;
  int y = 4;

  board[y * BOARD_WIDTH + x] = 'A';
  board[y * BOARD_WIDTH + x + 1] = 'B';

  performSwap(board, y, x);

  EXPECT_EQ('B', board[y * BOARD_WIDTH + x]);
  EXPECT_EQ('A', board[y * BOARD_WIDTH + x + 1]);
}

TEST(performSwap, doesNotTouchOtherElements)
{
  board_t board;
  for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
    board.push_back(i);


  int x = 3;
  int y = 4;
  int indexA = y * BOARD_WIDTH + x;
  int indexB = indexA + 1;

  board[indexA] = 'A';
  board[indexB] = 'B';

  performSwap(board, y, x);

  for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
    if (i != indexA && i != indexB)
      EXPECT_EQ(true, board[i] == i);
}
