#include <iostream>
#include <vector>

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

move_t calculateMove(board_t board)
{
  move_t move;
  return move;
}

int main()

{
  board_t board = parseBoard();

  move_t bestMove = calculateMove(board);

  cout << bestMove.x << ' ' << bestMove.y << endl;

  return 1;
}