### Bilge puzzle solver for https://yppedia.puzzlepirates.com/Bilging
A program which will calculate the best move (it thinks) using a DFS approach with depth of 1 (for now...).

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

### Testing
Testing is currently in progress.. But will be available by ```make test```
