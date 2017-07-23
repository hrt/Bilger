#include <iostream>
#include <vector>

#define BOARD_WIDTH 6
#define BOARD_HEIGHT 12

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

int clear(board_t board)
{
  // todo
  return 0;
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

  return bestMove;
}

int main()

{
  board_t board = parseBoard();

  move_t bestMove = calculateMove(board);

  cout << bestMove.x << ' ' << bestMove.y << endl;

  return 1;
}