#include <iostream>
#include <vector>

#define BOARD_WIDTH 6
#define BOARD_HEIGHT 12

#define EMPTY '-'

#define isEmpty(boardCell) (boardCell == EMPTY)

#define swap(board, x, y) {\
                            board[x*BOARD_WIDTH + y] ^= board[x*BOARD_WIDTH + y + 1]; \
                            board[x*BOARD_WIDTH + y + 1] ^= board[x*BOARD_WIDTH + y]; \
                            board[x*BOARD_WIDTH + y] ^= board[x*BOARD_WIDTH + y + 1]; \
                          }

using namespace std;

typedef vector<char> board_t;

struct move_t
{
  int x; // 0 is left, 5 is right
  int y; // 0 is top, 12 is bottom
};

board_t parseBoard()
{
  board_t board;
  char c;
  cin >> c;
  while (isalpha(c))
  {
    board.push_back(c);
    cin >> c;
  }
  return board;
}

bool shift(board_t& board)
{
  // todo : check the logic
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
          board[currentY * BOARD_WIDTH + j] ^= board[nearestCell * BOARD_WIDTH + j];
          board[nearestCell * BOARD_WIDTH + j] ^= board[currentY * BOARD_WIDTH + j];
          board[currentY * BOARD_WIDTH + j] ^= board[nearestCell * BOARD_WIDTH + j];
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

int clear(board_t& board)
{
  board_t nextGeneration(board);
  int clears = 0;

  for (int i = 0; i < BOARD_HEIGHT; i++)
  {
    for (int j = 0; j < BOARD_WIDTH; j++)
    {
      // horizontal right clears
      if (j < BOARD_WIDTH - 2 && !isEmpty(board[i * BOARD_WIDTH + j])
        && board[i * BOARD_WIDTH + j] == board[i * BOARD_WIDTH + j + 1] && board[i * BOARD_WIDTH + j] == board[i * BOARD_WIDTH + j + 2])
      {
        // todo: check for greater than 3s
        nextGeneration[i * BOARD_WIDTH + j] = EMPTY;
        nextGeneration[i * BOARD_WIDTH + j + 1] = EMPTY;
        nextGeneration[i * BOARD_WIDTH + j + 2] = EMPTY;
      }

      // horizontal left clears
      if (j > 1 && !isEmpty(board[i * BOARD_WIDTH + j])
        && board[i * BOARD_WIDTH + j] == board[i * BOARD_WIDTH + j - 1] && board[i * BOARD_WIDTH + j] == board[i * BOARD_WIDTH + j - 2])
      {
        // todo: check for greater than 3s
        nextGeneration[i * BOARD_WIDTH + j] = EMPTY;
        nextGeneration[i * BOARD_WIDTH + j - 1] = EMPTY;
        nextGeneration[i * BOARD_WIDTH + j - 2] = EMPTY;
      }

      // vertical below clears
      if (i < BOARD_HEIGHT - 2 && !isEmpty(board[i * BOARD_WIDTH + j])
        && board[i * BOARD_WIDTH + j] == board[(i + 1) * BOARD_WIDTH + j] && board[i * BOARD_WIDTH + j] == board[(i + 2) * BOARD_WIDTH + j])
      {
        // todo: check for greater than 3s
        nextGeneration[i * BOARD_WIDTH + j] = EMPTY;
        nextGeneration[(i + 1) * BOARD_WIDTH + j] = EMPTY;
        nextGeneration[(i + 2) * BOARD_WIDTH + j] = EMPTY;
      }

      // vertical above clears
      if (i > 1 && !isEmpty(board[i * BOARD_WIDTH + j])
        && board[i * BOARD_WIDTH + j] == board[(i - 1) * BOARD_WIDTH + j] && board[i * BOARD_WIDTH + j] == board[(i - 2) * BOARD_WIDTH + j])
      {
        // todo: check for greater than 3s
        nextGeneration[i * BOARD_WIDTH + j] = EMPTY;
        nextGeneration[(i - 1) * BOARD_WIDTH + j] = EMPTY;
        nextGeneration[(i - 2) * BOARD_WIDTH + j] = EMPTY;
      }
    }
  }


  if (shift(nextGeneration))
    clear(nextGeneration);

  for (int i = 0; i < (int) nextGeneration.size(); i++)
    if (isEmpty(nextGeneration[i]))
      clears += 1;

  board = nextGeneration;

  return clears;
}

move_t calculateMove(board_t board)
{
  move_t bestMove;
  int bestScore = -1;

  for (int i = 0 ; i < BOARD_HEIGHT; i++)
  {
    for (int j = 0; j < BOARD_WIDTH - 1; j++) // only BOARD_WIDTH - 1 swaps possible per BOARD_WIDTH
    {
      board_t currentBoard(board);
      swap(currentBoard, i, j);
      int currentScore = clear(currentBoard);
      if (currentScore > bestScore)
      {
        bestScore = currentScore;
        bestMove.x = j;
        bestMove.y = i;
      }
    }
  }
  cout << "Score : " << bestScore << endl;
  return bestMove;
}

int main()

{
  board_t board = parseBoard();

  move_t bestMove = calculateMove(board);

  cout << bestMove.x << ' ' << bestMove.y << endl;

  return 1;
}
