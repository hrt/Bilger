#include "Definitions.hpp"

#ifndef GAME_HPP
#define GAME_HPP

#define isEmpty(boardCell) (boardCell == EMPTY)

#define isPuffer(boardCell) (boardCell == PUFFERFISH)

#define isJellyFish(boardCell) (boardCell == JELLYFISH)

#define isCrab(boardCell) (boardCell == CRAB)

#define isMovable(boardCell) (!isEmpty(boardCell) && !isPuffer(boardCell) && !isCrab(boardCell) && !isJellyFish(boardCell))

#define performSwap(board, x, y) {\
                                   board[x*BOARD_WIDTH + y] ^= board[x*BOARD_WIDTH + y + 1]; \
                                   board[x*BOARD_WIDTH + y + 1] ^= board[x*BOARD_WIDTH + y]; \
                                   board[x*BOARD_WIDTH + y] ^= board[x*BOARD_WIDTH + y + 1]; \
                                 }

class Game
{
public:
  Game(board_t board);
  move_t calculateMove();
private:
  board_t board;
  bool shift(board_t& board);
  int clearCrabs(board_t& board);
  int clearMoveable(board_t& board);
  void performPuffer(board_t& board, int y, int x);
  void performJellyFish(board_t& board, int y, int j, int p);
};

#endif
