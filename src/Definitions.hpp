#include <vector>

#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#define BOARD_WIDTH 6
#define BOARD_HEIGHT 12

#define EMPTY '-'
#define CRAB 'X'
#define JELLYFISH 'Y'
#define PUFFERFISH 'Z'
#define DEFAULT_WATER_LEVEL 3

#define DEFAULT_SEARCH_DEPTH 3

typedef std::vector<char> board_t;

struct move_t
{
  int x; // 0 is left, 5 is right
  int y; // 0 is top, 11 is bottom
  int score;
};

#endif
