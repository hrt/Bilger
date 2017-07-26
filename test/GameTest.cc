#include "gtest/gtest.h"
#include "Game.hpp"
#include "Definitions.hpp"

board_t createFullBoardWith(char piece)
{
  board_t board;
  // fill up entire board
  for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
    board.push_back(piece);

  return board;
}

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


TEST(shift, returnsFalseOnNoShifts)
{
  board_t board = createFullBoardWith('A');

  Game game(board);

  EXPECT_EQ(false, game.shift(board));

  // entire board is empty (no shifts)
  for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
    board[i] = EMPTY;

  EXPECT_EQ(false, game.shift(board));
}

TEST(shift, returnsTrueOnAShift)
{
  board_t board = createFullBoardWith('A');

  // except this
  board[0] = EMPTY;

  Game game(board);

  EXPECT_EQ(true, game.shift(board));
}

TEST(shift, returnsTrueOnMultipleShifts)
{
  board_t board = createFullBoardWith('A');

  // except these
  board[0] = EMPTY;
  board[3] = EMPTY;
  board[BOARD_WIDTH] = EMPTY;

  Game game(board);

  EXPECT_EQ(true, game.shift(board));
}

TEST(shift, performsValidShift)
{
  board_t board = createFullBoardWith('A');

  // top row is initially empty
  for (int i = 0; i < BOARD_WIDTH; i++)
    board[i] = EMPTY;

  Game game(board);

  EXPECT_EQ(true, game.shift(board));

  // only bottom row should be empty..
  for (int i = 0; i < BOARD_WIDTH * (BOARD_HEIGHT - 1); i++)
    EXPECT_EQ('A', board[i]);

  for (int i = BOARD_WIDTH * (BOARD_HEIGHT - 1); i < BOARD_WIDTH * BOARD_HEIGHT; i++)
    EXPECT_EQ(true, isEmpty(board[i]));
}

TEST(clearCrabs, doesNotClearCrabsUnderwater)
{
  board_t board = createFullBoardWith('A');

  // fill up crabs upto water level
  for (int i = BOARD_WIDTH * (BOARD_HEIGHT - DEFAULT_WATER_LEVEL); i < BOARD_HEIGHT; i++)
    board[i] = CRAB;

  Game game(board);

  EXPECT_EQ(0, game.clearCrabs(board, DEFAULT_WATER_LEVEL));
}

TEST(clearCrabs, doesClearCrabsOverwater)
{
  board_t board = createFullBoardWith('A');

  // fill up crabs over water level
  for (int i = 0; i < BOARD_WIDTH * (BOARD_HEIGHT - DEFAULT_WATER_LEVEL); i++)
    board[i] = CRAB;

  Game game(board);

  EXPECT_EQ(54, game.clearCrabs(board, DEFAULT_WATER_LEVEL));

  // top rows should be shifted
  for (int i = 0; i < BOARD_WIDTH * DEFAULT_WATER_LEVEL; i++)
    EXPECT_EQ('A', board[i]);
}

TEST(clearCrabs, doesChainClearCrabsOverwater)
{
  board_t board = createFullBoardWith('A');

  // fill up crabs over water level
  for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
    board[i] = CRAB;

  Game game(board);

  EXPECT_EQ(72, game.clearCrabs(board, DEFAULT_WATER_LEVEL));

  // board should now be empty
  for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
    EXPECT_EQ(EMPTY, board[i]);
}

TEST(clearMoveable, doesClear3InARow)
{
  board_t board = createFullBoardWith(PUFFERFISH);

  for (int i = 0; i < 3; i++)
    board[i] = 'A';

  Game game(board);

  EXPECT_EQ(3, game.clearMoveable(board));

  // checking that board has been shifted
  for (int i = 0; i < 3; i++)
    EXPECT_EQ(PUFFERFISH, board[i]);
}

TEST(clearMoveable, doesClear3InACol)
{
  board_t board = createFullBoardWith(PUFFERFISH);

  for (int i = 0; i < 3; i++)
    board[i * BOARD_WIDTH] = 'A';

  Game game(board);

  // checking score
  EXPECT_EQ(3, game.clearMoveable(board));

  // checking that board has been shifted
  for (int i = 0; i < 3; i++)
    EXPECT_EQ(PUFFERFISH, board[i * BOARD_WIDTH]);
}

TEST(clearMoveable, doesClear3x3)
{
  board_t board = createFullBoardWith(PUFFERFISH);

  for (int i = 0; i < 3; i++)
  {
    board[i] = 'A';
    board[i * BOARD_WIDTH] = 'A';
  }

  Game game(board);

  // checking score
  EXPECT_EQ(5, game.clearMoveable(board));

  // checking that board has been shifted
  for (int i = 0; i < 3; i++)
  {
    EXPECT_EQ(PUFFERFISH, board[i * BOARD_WIDTH]);
    EXPECT_EQ(PUFFERFISH, board[i]);
  }
}

TEST(clearMoveable, doesClear4x4)
{
  board_t board = createFullBoardWith(PUFFERFISH);

  for (int i = 0; i < 4; i++)
  {
    board[i] = 'A';
    board[i * BOARD_WIDTH] = 'A';
  }

  Game game(board);

  // checking score
  EXPECT_EQ(7, game.clearMoveable(board));

  // checking that board has been shifted
  for (int i = 0; i < 4; i++)
  {
    EXPECT_EQ(PUFFERFISH, board[i * BOARD_WIDTH]);
    EXPECT_EQ(PUFFERFISH, board[i]);
  }
}

TEST(performPuffer, doesPerformValidPuffer)
{
  board_t board = createFullBoardWith(PUFFERFISH);

  Game game(board);

  game.performPuffer(board, 1, 1);

  for (int i = 1; i <= 3; i++)
  {
    EXPECT_EQ(true, isEmpty(board[(BOARD_HEIGHT - i) * BOARD_WIDTH]));
    EXPECT_EQ(true, isEmpty(board[(BOARD_HEIGHT - i) * BOARD_WIDTH + 1]));
    EXPECT_EQ(true, isEmpty(board[(BOARD_HEIGHT - i) * BOARD_WIDTH + 2]));
  }
}


