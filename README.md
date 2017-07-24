### Bilge puzzle solver for https://yppedia.puzzlepirates.com/Bilging
A program which will calculate the best move (it thinks) using a DFS approach with depth of 1 (for now...).

Note: It looks deeper than one in the case of crabs, puffer fish and jelly fish.
Also worth noting that the evaluation is currently simply the number of "cells" you can clear excluding ones by puffer fish and jelly fish (since they don't add to your score). Crab combos are scored as well.

### Building
To build this you will need to run ```make``` within the root directory

### How to use
Input to the program a series of 72 alphabetical characters follow by a non alphabetical characters to represent the board state.

For example if you choose to let A, B, C, D and E be different coloured pieces in this given board

![banner](http://i.imgur.com/x3R2xWa.png)

then you would input the series of characters to the program :
```
ABCDBC
ADBABE
DABCEA
ADEDAE
EBBEED
DABCDA
CEDBAD
CACBDA
DDBDCD
BADCCB
BDDCDE
CCEBAD
4
```

which is..
```
ABCDBCADBABEDABCEAADEDAEEBBEEDDABCDACEDBADCACBDADDBDCDBADCCBBDDCDECCEBAD4
```

A crab is represented by 'X', JellyFish by 'Y' and PufferFish by 'Z'.

The program will respond with your best move, for example
```2 5```
which would correspond to the highlighted move in the diagram above.. ({0, 0} is the top left and {5, 11} is the bottom right)

### Testing
To test run ```make check```
