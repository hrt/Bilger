### Bilge puzzle solver for https://yppedia.puzzlepirates.com/Bilging
Bilging is a puzzle made for humans in the game Puzzle Pirates.
This program will calculate the best move (it thinks) using a DFS approach with depth of 3 (approx 2 seconds).

Here is a demo of the program combined with screen detection and mouse movement to play the puzzle for me!
[![Alt text](https://img.youtube.com/vi/cG1DBXWJxLw/0.jpg)](https://www.youtube.com/watch?v=cG1DBXWJxLw)

~~https://www.youtube.com/watch?v=TD-OIjR4WTw~~ (taken down by copyright claims of game owner)
https://www.youtube.com/watch?v=cG1DBXWJxLw

Discussion thread : https://bot-supply.com/forum/development/13888-bilge-bot-logic-%5Bc-source%5D.html

### Building to work for your C++ Bot
You will need to copy ```Game.cpp```, ```Game.hpp``` and ```Definitions.hpp``` and compile your bot with the parameter ```-I {LOCATION OF FILES COPIED}```.

Then you will need to create a ```board_t (vector<char>)``` and figure out the water level and your search depth
by using pixel detection or what not.

Create an instance of the game with code ```Game(board, waterLevel, searchDepth)```
To calculate the best move, make use of the function ```move_t calculateMove()``` within the Game class.
e.g.
```
board_t board = readBoard();
int waterLevel = readWaterLevel();
int searchDepth = 3;
Game game(board, waterLevel, searchDepth);
move_t bestMove = game.calculateMove();
std::cout << bestMove.x << ' ' << bestMove.y << std::endl;
```


### Building (Windows / Linux) to use Bilge Logic
If you're on windows you will need to install tools such as ```g++``` and ```make``` beforehand using applications such as Cygwin or Mingw.
To build this you will need to first install google tests which can be found below.

Run ```make``` within the root directory to create ```bin/Bilger``` executable file.

### How to use
Input to the program a series of 72 alphabetical characters followed by the water level and search depth.

For example if you choose to let A, B, C, D and E be different coloured pieces in this given board

![banner](http://i.imgur.com/x3R2xWa.png)

then you would input the series of characters to the program :
```
ABCDBC
ACBABE
DABCEA
ADEDAE
EBBEED
DABCDA
CEDBAD
CACBEA
DDBDCD
BADCCB
BDDCDE
CCEBAD
```
followed by the water level and then search depth

for example for water level 4 and search depth of 3..
```
ABCDBCACBABEDABCEAADEDAEEBBEEDDABCDACEDBADCACBEADDBDCDBADCCBBDDCDECCEBAD 4 3
```

A crab is represented by 'X', JellyFish by 'Y' and PufferFish by 'Z'.

The program will respond with your best move, example outputs :
```
ABCDBCACBABEDABCEAADEDAEEBBEEDDABCDACEDBADCACBEADDBDCDBADCCBBDDCDECCEBAD 4 1
Depth : 1
Water Level : 4
Score : 64
Move : 2 8
```

```
ABCDBCACBABEDABCEAADEDAEEBBEEDDABCDACEDBADCACBEADDBDCDBADCCBBDDCDECCEBAD 3 2
Depth : 2
Water Level : 3
Score : 80
Move : 2 8
```

```
ABCDBCACBABEDABCEAADEDAEEBBEEDDABCDACEDBADCACBEADDBDCDBADCCBBDDCDECCEBAD 3 3
Depth : 3
Water Level : 3
Score : 116
Move : 2 8
```

```
ABCDBCACBABEDABCEAADEDAEEBBEEDDABCDACEDBADCACBEADDBDCDBADCCBBDDCDECCEBAD 3 4
Depth : 4
Water Level : 3
Score : 125
Move : 4 2
```
which would correspond to the highlighted move in the diagram above.. (```{0, 0}``` is the top left and ```{5, 11}``` is the bottom right)

### Testing (Windows / Linux)
To build this you will need to first install google tests which can be found below.

Afterso, run ```make check``` within the root directory to build the tests and run the executable file ```bin/Test```

### Google Tests (Windows / Linux)
You will need to compile google tests https://github.com/google/googletest in ```lib/googletest/googletest/``` (explained below).

To pull the google test sub module run the command ```git submodule update --init --recursive```


To later remove the sub modules run ```git submodule deinit -f {PATH TO lib/googletest folder}```


To compile google tests on Linux or Windows (with Cygwin g++ and make installed), navigate to lib/googletest/googletest/ and run  ```g++ -isystem include -I . -pthread -c src/gtest-all.cc```


and then run  ```ar -rv libgtest.a gtest-all.o```
