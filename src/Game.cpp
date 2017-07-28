#include "Game.hpp"
#include "Utils.hpp"

Game::Game(board_t board, int waterLevel, int searchDepth)
{
  this->board = board;
  this->waterLevel = waterLevel;
  this->searchDepth = searchDepth;
}

bool Game::shift(board_t& board)
{
  // shifts all EMPTY cells to the bottom of the board

  bool hasShifted = false;
  for (int j = 0; j < BOARD_WIDTH; j++)
  {
    // find the nearest (vertically) empty cell
    int nearestEmpty = 0;
    while (nearestEmpty < BOARD_HEIGHT && !isEmpty(board[nearestEmpty * BOARD_WIDTH + j]))
      nearestEmpty += 1;

    // find the nearest (vertically) non empty cell after the empty cell
    int nearestNonEmpty = nearestEmpty + 1;
    while (nearestNonEmpty < BOARD_HEIGHT && isEmpty(board[nearestNonEmpty * BOARD_WIDTH + j]))
      nearestNonEmpty += 1;

    // swap all empty cells with nearest cells
    while (nearestNonEmpty < BOARD_HEIGHT)
    {
      hasShifted |= true;
      swap(board[nearestEmpty * BOARD_WIDTH + j], board[nearestNonEmpty * BOARD_WIDTH + j])

      // incrementing both nearestEmpty and nearestNonEmpty, note that nearestEmpty will always be empty by default
      nearestEmpty += 1;
      nearestNonEmpty += 1;

      // refind nearest non empty cell
      while (nearestNonEmpty < BOARD_HEIGHT && isEmpty(board[nearestNonEmpty * BOARD_WIDTH + j]))
        nearestNonEmpty += 1;
    }
  }

  return hasShifted;
}

int Game::clearCrabs(board_t& board, int waterLevel)
{
  // note: this shift happens twice initially
  int crabReleased = 0;
  for (int i = 0; i < BOARD_HEIGHT - waterLevel; i++)
  {
    for (int j = 0; j < BOARD_WIDTH; j++)
      if (isCrab(board[i * BOARD_WIDTH + j]))
      {
        crabReleased += 1;
        board[i * BOARD_WIDTH + j] = EMPTY;
      }
  }

  if (shift(board))
    crabReleased += clearCrabs(board, waterLevel); // recursive call, if crab is released then shift -> check for crabs again (do not clear all for crab combo)

  return crabReleased;
}

int Game::clearAll(board_t& board, int waterLevel, int previousClears)
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
    int crabScore = clearCrabs(nextGeneration, waterLevel) * 2;
    crabScore *= crabScore;
    clears += crabScore;

    int totalClears = countClears(nextGeneration);
    int currentClears = totalClears - previousClears;

    clears += currentClears * currentClears;

    // recursive case, if board was shifted -> check for combos again
    // note : ignoring crab combos
    clearAll(nextGeneration, waterLevel, totalClears);
  }

  board = nextGeneration;

  return clears;
}

int Game::countClears(board_t& board)
{
  int clears = 0;

  // Assume all empty cells should be at bottom, so exploit this to reduce complexity
  for (int i = 0; i < BOARD_WIDTH; i++)
  {
    int j = BOARD_HEIGHT - 1;             // starting from bottom
    while (j >= 0 && isEmpty(board[j * BOARD_WIDTH + i]))
    {
      clears += 1;
      j -= 1;                             // move up
    }
  }

  return clears;
}

void Game::performPuffer(board_t& board, int y, int x)
{
  for (int i = max(y - 1, 0); i <= min(y + 1, BOARD_HEIGHT - 1); i++)
    for (int j = max(x - 1, 0); j <= min(x + 1, BOARD_WIDTH - 1); j++)
      board[i * BOARD_WIDTH + j] = EMPTY;

  shift(board);
}

void Game::performJellyFish(board_t& board, int y, int x, int p)
{
  board[y * BOARD_WIDTH + x] = EMPTY;
  char piece = board[y * BOARD_WIDTH + p];

  for (int i = 0; i < BOARD_HEIGHT; i++)
    for (int j = 0; j < BOARD_WIDTH; j++)
      if (board[i * BOARD_WIDTH + j] == piece)
        board[i * BOARD_WIDTH + j] = EMPTY;

  shift(board);
}

// iterates through the board and returns a list of swaps
std::vector<move_t> Game::generateMoves(board_t& board)
{
  std::vector<move_t> moves;
  for (int i = 0 ; i < BOARD_HEIGHT; i++)
  {
    for (int j = 0; j < BOARD_WIDTH - 1; j++) // only BOARD_WIDTH - 1 swaps possible per BOARD_WIDTH
    {
      move_t move;
      move.score = 0;
      move.x = j;
      move.y = i;
      moves.push_back(move);

      // skipping duplicate puffer fish move
      if (isPufferFish(board[i * BOARD_WIDTH + j + 1]))
        j += 1;
    }
  }
  return moves;
}

// applies the move to a new board and return this board
// also updated the move.score value according to the number of crab clear (combos)
board_t Game::applyMove(board_t& board, int waterLevel, move_t& move, int previousClears)
{
  board_t newBoard(board);

  int y = move.y;
  int x = move.x;

  if (isMoveable(newBoard[y * BOARD_WIDTH + x]) && isMoveable(newBoard[y * BOARD_WIDTH + x + 1]))
  {
    performSwap(newBoard, y, x);
  }
  else if (isPufferFish(newBoard[y * BOARD_WIDTH + x]))
  {
    performPuffer(newBoard, y, x);
  }
  else if (isPufferFish(newBoard[y * BOARD_WIDTH + x + 1]))
  {
    performPuffer(newBoard, y, x + 1);
  }
  else if (isJellyFish(newBoard[y * BOARD_WIDTH + x]) && isMoveable(newBoard[y * BOARD_WIDTH + x + 1]))
  {
    performJellyFish(newBoard, y, x, x + 1);
  }
  else if (isJellyFish(newBoard[y * BOARD_WIDTH + x + 1]) && isMoveable(newBoard[y * BOARD_WIDTH + x]))
  {
    performJellyFish(newBoard, y, x + 1, x);
  }

  move.score += clearAll(newBoard, waterLevel, previousClears);

  return newBoard;
}

// Depth First Search for best clearing move
move_t Game::search(board_t& board, int waterLevel, int searchDepth, int previousClears)
{
  move_t bestMove;
  bestMove.score = -1;

  std::vector<move_t> moves = generateMoves(board);
  for (int i = 0; i < (int) moves.size(); i++)
  {
    // applies and adds clears to moves[i].score
    board_t newBoard = applyMove(board, waterLevel, moves[i], previousClears);

    // recursive case
    if (searchDepth > 1)
      moves[i].score += search(newBoard, waterLevel, searchDepth - 1, countClears(newBoard)).score;

    // update bestMove
    if (moves[i].score > bestMove.score)
      bestMove = moves[i];
  }

  return bestMove;
}

move_t Game::calculateMove()
{
  return search(this->board, this->waterLevel, this->searchDepth, 0);
}
