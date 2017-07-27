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

TEST(isEmpty, HoldsTrueForEmpty)
{
  EXPECT_TRUE(isEmpty(EMPTY));
}

TEST(isEmpty, holdsFalseForNonEmpty)
{
  EXPECT_FALSE(isEmpty(PUFFERFISH));
  EXPECT_FALSE(isEmpty(JELLYFISH));
  EXPECT_FALSE(isEmpty(CRAB));
  EXPECT_FALSE(isEmpty('A'));
  EXPECT_FALSE(isEmpty('7'));
}

TEST(isPufferFish, holdsTrueForPufferFish)
{
  EXPECT_TRUE(isPufferFish(PUFFERFISH));
}

TEST(isPufferFish, holdsFalseForNonPufferFish)
{
  EXPECT_FALSE(isPufferFish(EMPTY));
  EXPECT_FALSE(isPufferFish(JELLYFISH));
  EXPECT_FALSE(isPufferFish(CRAB));
  EXPECT_FALSE(isPufferFish('A'));
  EXPECT_FALSE(isPufferFish('7'));
}

TEST(isJellyFish, holdsTrueForJellyFish)
{
  EXPECT_TRUE(isJellyFish(JELLYFISH));
}

TEST(isJellyFish, holdsFalseForNonJellyFish)
{
  EXPECT_FALSE(isJellyFish(EMPTY));
  EXPECT_FALSE(isJellyFish(PUFFERFISH));
  EXPECT_FALSE(isJellyFish(CRAB));
  EXPECT_FALSE(isJellyFish('A'));
  EXPECT_FALSE(isJellyFish('7'));
}

TEST(isCrab, holdsTrueForCrab)
{
  EXPECT_TRUE(isCrab(CRAB));
}

TEST(isCrab, holdsFalseForNonCrab)
{
  EXPECT_FALSE(isCrab(EMPTY));
  EXPECT_FALSE(isCrab(PUFFERFISH));
  EXPECT_FALSE(isCrab(JELLYFISH));
  EXPECT_FALSE(isCrab('A'));
  EXPECT_FALSE(isCrab('7'));
}

TEST(isMoveable, holdsTrueForMoveable)
{
  EXPECT_TRUE(isMoveable('A'));
  EXPECT_TRUE(isMoveable('7'));
  EXPECT_TRUE(isMoveable(' '));
}

TEST(isMoveable, holdsFalseForNonMoveable)
{
  EXPECT_FALSE(isMoveable(EMPTY));
  EXPECT_FALSE(isMoveable(PUFFERFISH));
  EXPECT_FALSE(isMoveable(JELLYFISH));
  EXPECT_FALSE(isMoveable(CRAB));
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
      EXPECT_TRUE(board[i] == i);
}


TEST(shift, returnsFalseOnNoShifts)
{
  board_t board = createFullBoardWith('A');

  Game game(board, DEFAULT_WATER_LEVEL, DEFAULT_SEARCH_DEPTH);

  EXPECT_FALSE(game.shift(board));

  // entire board is empty (no shifts)
  for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
    board[i] = EMPTY;

  EXPECT_FALSE(game.shift(board));
}

TEST(shift, returnsTrueOnAShift)
{
  board_t board = createFullBoardWith('A');

  // except this
  board[0] = EMPTY;

  Game game(board, DEFAULT_WATER_LEVEL, DEFAULT_SEARCH_DEPTH);

  EXPECT_TRUE(game.shift(board));
}

TEST(shift, returnsTrueOnMultipleShifts)
{
  board_t board = createFullBoardWith('A');

  // except these
  board[0] = EMPTY;
  board[3] = EMPTY;
  board[BOARD_WIDTH] = EMPTY;

  Game game(board, DEFAULT_WATER_LEVEL, DEFAULT_SEARCH_DEPTH);

  EXPECT_TRUE(game.shift(board));
}

TEST(shift, performsValidShift)
{
  board_t board = createFullBoardWith('A');

  // top row is initially empty
  for (int i = 0; i < BOARD_WIDTH; i++)
    board[i] = EMPTY;

  Game game(board, DEFAULT_WATER_LEVEL, DEFAULT_SEARCH_DEPTH);

  EXPECT_TRUE(game.shift(board));

  // only bottom row should be empty..
  for (int i = 0; i < BOARD_WIDTH * (BOARD_HEIGHT - 1); i++)
    EXPECT_EQ('A', board[i]);

  for (int i = BOARD_WIDTH * (BOARD_HEIGHT - 1); i < BOARD_WIDTH * BOARD_HEIGHT; i++)
    EXPECT_TRUE(isEmpty(board[i]));
}

TEST(clearCrabs, doesNotClearCrabsUnderwater)
{
  board_t board = createFullBoardWith('A');

  // fill up crabs upto water level
  for (int i = BOARD_WIDTH * (BOARD_HEIGHT - DEFAULT_WATER_LEVEL); i < BOARD_HEIGHT; i++)
    board[i] = CRAB;

  Game game(board, DEFAULT_WATER_LEVEL, DEFAULT_SEARCH_DEPTH);

  EXPECT_EQ(0, game.clearCrabs(board, DEFAULT_WATER_LEVEL));
}

TEST(clearCrabs, doesClearCrabsOverwater)
{
  board_t board = createFullBoardWith('A');

  // fill up crabs over water level
  for (int i = 0; i < BOARD_WIDTH * (BOARD_HEIGHT - DEFAULT_WATER_LEVEL); i++)
    board[i] = CRAB;

  Game game(board, DEFAULT_WATER_LEVEL, DEFAULT_SEARCH_DEPTH);

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

  Game game(board, DEFAULT_WATER_LEVEL, DEFAULT_SEARCH_DEPTH);

  EXPECT_EQ(72, game.clearCrabs(board, DEFAULT_WATER_LEVEL));

  // board should now be empty
  for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
    EXPECT_TRUE(isEmpty(board[i]));
}

TEST(clearAll, doesClear3InARow)
{
  board_t board = createFullBoardWith(PUFFERFISH);

  for (int i = 0; i < 3; i++)
    board[i] = 'A';

  Game game(board, DEFAULT_WATER_LEVEL, DEFAULT_SEARCH_DEPTH);

  EXPECT_EQ(3, game.clearAll(board, DEFAULT_WATER_LEVEL));

  // checking that board has been shifted
  for (int i = 0; i < 3; i++)
    EXPECT_EQ(PUFFERFISH, board[i]);
}

TEST(clearAll, doesClear3InACol)
{
  board_t board = createFullBoardWith(PUFFERFISH);

  for (int i = 0; i < 3; i++)
    board[i * BOARD_WIDTH] = 'A';

  Game game(board, DEFAULT_WATER_LEVEL, DEFAULT_SEARCH_DEPTH);

  // checking score
  EXPECT_EQ(3, game.clearAll(board, DEFAULT_WATER_LEVEL));

  // checking that board has been shifted
  for (int i = 0; i < 3; i++)
    EXPECT_EQ(PUFFERFISH, board[i * BOARD_WIDTH]);
}

TEST(clearAll, doesClear3x3)
{
  board_t board = createFullBoardWith(PUFFERFISH);

  for (int i = 0; i < 3; i++)
  {
    board[i] = 'A';
    board[i * BOARD_WIDTH] = 'A';
  }

  Game game(board, DEFAULT_WATER_LEVEL, DEFAULT_SEARCH_DEPTH);

  // checking score
  EXPECT_EQ(5, game.clearAll(board, DEFAULT_WATER_LEVEL));

  // checking that board has been shifted
  for (int i = 0; i < 3; i++)
  {
    EXPECT_EQ(PUFFERFISH, board[i * BOARD_WIDTH]);
    EXPECT_EQ(PUFFERFISH, board[i]);
  }
}

TEST(clearAll, doesClear4x4)
{
  board_t board = createFullBoardWith(PUFFERFISH);

  for (int i = 0; i < 4; i++)
  {
    board[i] = 'A';
    board[i * BOARD_WIDTH] = 'A';
  }

  Game game(board, DEFAULT_WATER_LEVEL, DEFAULT_SEARCH_DEPTH);

  // checking score
  EXPECT_EQ(7, game.clearAll(board, DEFAULT_WATER_LEVEL));

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

  Game game(board, DEFAULT_WATER_LEVEL, DEFAULT_SEARCH_DEPTH);

  game.performPuffer(board, 1, 1);

  for (int i = 1; i <= 3; i++)
  {
    EXPECT_TRUE(isEmpty(board[(BOARD_HEIGHT - i) * BOARD_WIDTH]));
    EXPECT_TRUE(isEmpty(board[(BOARD_HEIGHT - i) * BOARD_WIDTH + 1]));
    EXPECT_TRUE(isEmpty(board[(BOARD_HEIGHT - i) * BOARD_WIDTH + 2]));
  }
}

TEST(performJellyFish, doesPerformValidJellyFish)
{
  board_t board = createFullBoardWith('A');
  board[0] = JELLYFISH;

  Game game(board, DEFAULT_WATER_LEVEL, DEFAULT_SEARCH_DEPTH);

  game.performJellyFish(board, 0, 0, 'A');

  for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
    EXPECT_TRUE(isEmpty(board[i]));
}
