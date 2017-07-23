#include <iostream>
#include <vector>

using namespace std;

typedef vector<char> board_t;

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

int main()

{

  board_t board = parseBoard();


  return 1;
}