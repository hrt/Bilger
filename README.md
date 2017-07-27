### Bilge puzzle solver for https://yppedia.puzzlepirates.com/Bilging
A program which will calculate the best move (it thinks) using a DFS approach with depth of 3.

Note: It looks deeper than one in the case of crabs, puffer fish and jelly fish.
Also worth noting that the evaluation is currently simply the number of "cells" you can clear excluding ones by puffer fish and jelly fish (since they don't add to your score). Crab combos are scored as well.

Discussion thread : https://bot-supply.com/forum/development/13888-bilge-bot-logic-%5Bc-source%5D.html

### Building
If you're on windows you will need to install tools such as ```g++``` and ```make``` beforehand using applications such as Cygwin or Mingw.
To build this you will need to first install google tests which can be found below.

Run ```make``` within the root directory.

### How to use
Input to the program a series of 72 alphabetical characters followed by the water level and search depth.

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
```
followed by the water level and then search depth

for example for water level 4 and search depth of 3..
```
ABCDBCADBABEDABCEAADEDAEEBBEEDDABCDACEDBADCACBDADDBDCDBADCCBBDDCDECCEBAD 4 3
```

Note, the '4' at the end can be any non-alpha character used to represent termination.
A crab is represented by 'X', JellyFish by 'Y' and PufferFish by 'Z'.

The program will respond with your best move, for example
```
Depth : 3
Water Level : 4
Score : 54
Move : 2 8
```
which would correspond to the highlighted move in the diagram above.. (```{0, 0}``` is the top left and ```{5, 11}``` is the bottom right)

### Testing
To build this you will need to first install google tests which can be found below.

Afterso, run ```make check``` within the root directory to run the tests.

### Google Tests
You will need to compile google tests https://github.com/google/googletest and place ```libgtest.a``` within the root of the ```lib``` folder.
You will also need to have the google test include folder (included as a submodule within this repo) and place it within the ```lib``` folder.

To pull the google test sub module run the command ```git submodule update --init --recursive```


To later remove the sub modules run ```git submodule deinit -f {PATH TO lib/googletest folder}```


To compile google tests on Linux, navigate to lib/googletest/googletest/ and run  ```g++ -isystem include -I . -pthread -c src/gtest-all.cc```


and then run  ```ar -rv libgtest.a gtest-all.o```
