#include "Definitions.hpp"
#include "gtest/gtest_prod.h"

#ifndef GAME_HPP
#define GAME_HPP

#define isEmpty(boardCell) (boardCell == EMPTY)

#define isPufferFish(boardCell) (boardCell == PUFFERFISH)

#define isJellyFish(boardCell) (boardCell == JELLYFISH)

#define isCrab(boardCell) (boardCell == CRAB)

#define isMoveable(boardCell) (!isEmpty(boardCell) && !isPufferFish(boardCell) && !isCrab(boardCell) && !isJellyFish(boardCell))

#define performSwap(board, y, x) {\
                                   board[y*BOARD_WIDTH + x] ^= board[y*BOARD_WIDTH + x + 1]; \
                                   board[y*BOARD_WIDTH + x + 1] ^= board[y*BOARD_WIDTH + x]; \
                                   board[y*BOARD_WIDTH + x] ^= board[y*BOARD_WIDTH + x + 1]; \
                                 }

class Game
{
public:
  Game(board_t board);
  move_t calculateMove();
private:
  board_t board;
  bool shift(board_t& board);
  int clearCrabs(board_t& board, int waterLevel);
  int clearMoveable(board_t& board);
  void performPuffer(board_t& board, int y, int x);
  void performJellyFish(board_t& board, int y, int x, int p);

  // Functions used for google tests
  FRIEND_TEST(shift, returnsFalseOnNoShifts);
  FRIEND_TEST(shift, returnsTrueOnAShift);
  FRIEND_TEST(shift, returnsTrueOnMultipleShifts);
  FRIEND_TEST(shift, performsValidShift);

  FRIEND_TEST(clearCrabs, doesNotClearCrabsUnderwater);
  FRIEND_TEST(clearCrabs, doesClearCrabsOverwater);
  FRIEND_TEST(clearCrabs, doesChainClearCrabsOverwater);

  FRIEND_TEST(clearMoveable, doesClear3InARow);
  FRIEND_TEST(clearMoveable, doesClear3InACol);
  FRIEND_TEST(clearMoveable, doesClear3x3);
  FRIEND_TEST(clearMoveable, doesClear4x4);

  FRIEND_TEST(performPuffer, doesPerformValidPuffer);

  FRIEND_TEST(performJellyFish, doesPerformValidJellyFish);
  // TODO : performJellyFish
};

#endif
