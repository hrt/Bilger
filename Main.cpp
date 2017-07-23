#include <iostream>
#include <vector>

using namespace std;
int main()
{
  vector<char> board;
  char c;
  cin >> c;
  while (isalpha(c))
  {
    board.push_back(c);
    cin >> c;
  }

  return 1;
}