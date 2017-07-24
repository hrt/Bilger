#include "Game.hpp"
#include "Utils.hpp"

Game::Game(board_t board)
{
  this->board = board;
}

bool Game::shift(board_t& board)
{
  // shift all EMPTY cells out of the board

  bool hasShifted = false;
  for (int j = 0; j < BOARD_WIDTH; j++)
  {
    for (int i = 0; i < BOARD_HEIGHT - 1; i++) // we don't care about the last row
    {
      if (isEmpty(board[i * BOARD_WIDTH + j]))
      {
        // first find the nearest (vertically) non empty cell
        int nearestCell = i + 1;
        while (nearestCell < BOARD_HEIGHT && isEmpty(board[nearestCell * BOARD_WIDTH + j]))
          nearestCell += 1;

        // swap all empty cells with nearest cells
        int currentY = i;
        while (nearestCell < BOARD_HEIGHT)
        {
          hasShifted |= true;
          swap(board[currentY * BOARD_WIDTH + j], board[nearestCell * BOARD_WIDTH + j])
          currentY += 1;
          nearestCell += 1;
          while (nearestCell < BOARD_HEIGHT && isEmpty(board[nearestCell * BOARD_WIDTH + j]))
            nearestCell += 1;
        }
      }
    }
  }

  return hasShifted;
}

int Game::clearCrabs(board_t& board)
{
  // note: this shift happens twice initially
  int crabReleased = 0;
  for (int i = 0; i < BOARD_HEIGHT - 3; i++)
  {
    for (int j = 0; j < BOARD_WIDTH; j++)
      if (isCrab(board[i * BOARD_WIDTH + j]))
      {
        crabReleased += 1;
        board[i * BOARD_WIDTH + j] = EMPTY;
      }
  }

  if (shift(board))
    crabReleased += clearCrabs(board); // recursive call, if crab is released then shift -> check for crabs again (do not clear all for crab combo)

  return crabReleased;
}

int Game::clearMoveable(board_t& board)
{
  board_t nextGeneration(board);
  int clears = 0;

  for (int i = 0; i < BOARD_HEIGHT; i++)
  {
    for (int j = 0; j < BOARD_WIDTH; j++)
    {
      // horizontal right clears
      if (j < BOARD_WIDTH - 2 && isMoveable(board[i * BOARD_WIDTH + j])
        && board[i * BOARD_WIDTH + j] == board[i * BOARD_WIDTH + j + 1]
        && board[i * BOARD_WIDTH + j] == board[i * BOARD_WIDTH + j + 2])
      {
        nextGeneration[i * BOARD_WIDTH + j] = EMPTY;
        nextGeneration[i * BOARD_WIDTH + j + 1] = EMPTY;
        nextGeneration[i * BOARD_WIDTH + j + 2] = EMPTY;
      }

      // horizontal left clears
      if (j > 1 && isMoveable(board[i * BOARD_WIDTH + j])
        && board[i * BOARD_WIDTH + j] == board[i * BOARD_WIDTH + j - 1]
        && board[i * BOARD_WIDTH + j] == board[i * BOARD_WIDTH + j - 2])
      {
        nextGeneration[i * BOARD_WIDTH + j] = EMPTY;
        nextGeneration[i * BOARD_WIDTH + j - 1] = EMPTY;
        nextGeneration[i * BOARD_WIDTH + j - 2] = EMPTY;
      }

      // vertical below clears
      if (i < BOARD_HEIGHT - 2 && isMoveable(board[i * BOARD_WIDTH + j])
        && board[i * BOARD_WIDTH + j] == board[(i + 1) * BOARD_WIDTH + j]
        && board[i * BOARD_WIDTH + j] == board[(i + 2) * BOARD_WIDTH + j])
      {
        nextGeneration[i * BOARD_WIDTH + j] = EMPTY;
        nextGeneration[(i + 1) * BOARD_WIDTH + j] = EMPTY;
        nextGeneration[(i + 2) * BOARD_WIDTH + j] = EMPTY;
      }

      // vertical above clears
      if (i > 1 && isMoveable(board[i * BOARD_WIDTH + j])
        && board[i * BOARD_WIDTH + j] == board[(i - 1) * BOARD_WIDTH + j]
        && board[i * BOARD_WIDTH + j] == board[(i - 2) * BOARD_WIDTH + j])
      {
        nextGeneration[i * BOARD_WIDTH + j] = EMPTY;
        nextGeneration[(i - 1) * BOARD_WIDTH + j] = EMPTY;
        nextGeneration[(i - 2) * BOARD_WIDTH + j] = EMPTY;
      }

    }
  }

  if (shift(nextGeneration))
  {
    int crabsCleared = clearCrabs(nextGeneration) * 2;
    clears += crabsCleared * crabsCleared;
    clears += clearMoveable(nextGeneration);        // recursive case, if board was shifted -> check for combos again, TODO: this score should be reduced since it is "random"
  }
  else
  {                                         // base case, todo: we don't need to go through entire board
    for (int i = 0; i < (int) nextGeneration.size(); i++)
      if (isEmpty(nextGeneration[i]))
        clears += 1;
  }

  board = nextGeneration;

  return clears;
}

void Game::performPuffer(board_t& board, int y, int x)
{
  for (int i = max(y - 1, 0); i <= min(y + 1, BOARD_HEIGHT - 1); i++)
    for (int j = max(x - 1, 0); j <= min(x + 1, BOARD_HEIGHT - 1); j++)
      board[y * BOARD_WIDTH + x] = EMPTY;

  shift(board);
}

void Game::performJellyFish(board_t& board, int y, int j, int p)
{
  board[y * BOARD_WIDTH + j] = EMPTY;
  char piece = board[y * BOARD_WIDTH + p];

  for (int i = 0; i < BOARD_HEIGHT; i++)
    for (int j = 0; j < BOARD_WIDTH; j++)
      if (board[i * BOARD_WIDTH + j] == piece)
        board[i * BOARD_WIDTH + j] = EMPTY;

  shift(board);
}

move_t Game::calculateMove()
{
  move_t bestMove;
  int bestScore = -1;

  for (int i = 0 ; i < BOARD_HEIGHT; i++)
  {
    for (int j = 0; j < BOARD_WIDTH - 1; j++) // only BOARD_WIDTH - 1 swaps possible per BOARD_WIDTH
    {
      board_t currentBoard(this->board);
      if (isMoveable(currentBoard[i * BOARD_WIDTH + j]) && isMoveable(currentBoard[i * BOARD_WIDTH + j + 1]))
      {
        performSwap(currentBoard, i, j);
      }
      else if (isPufferFish(currentBoard[i * BOARD_WIDTH + j]))
      {
        performPuffer(currentBoard, i, j);
      }
      else if (isPufferFish(currentBoard[i * BOARD_WIDTH + j + 1]))
      {
        performPuffer(currentBoard, i, j + 1);
      }
      else if (isJellyFish(currentBoard[i * BOARD_WIDTH + j]) && isMoveable(currentBoard[i * BOARD_WIDTH + j + 1]))
      {
        performJellyFish(currentBoard, i, j, j + 1);
      }
      else if (isJellyFish(currentBoard[i * BOARD_WIDTH + j + 1]) && isMoveable(currentBoard[i * BOARD_WIDTH + j]))
      {
        performJellyFish(currentBoard, i, j + 1, j);
      }
      int currentScore = clearMoveable(currentBoard);
      if (currentScore > bestScore)
      {
        bestScore = currentScore;
        bestMove.x = j;
        bestMove.y = i;
      }
    }
  }
  return bestMove;
}
