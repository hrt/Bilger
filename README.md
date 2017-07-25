### Bilge puzzle solver for https://yppedia.puzzlepirates.com/Bilging
A program which will calculate the best move (it thinks) using a DFS approach with depth of 1 (for now...).

Note: It looks deeper than one in the case of crabs, puffer fish and jelly fish.
Also worth noting that the evaluation is currently simply the number of "cells" you can clear excluding ones by puffer fish and jelly fish (since they don't add to your score). Crab combos are scored as well.

Discussion thread : https://bot-supply.com/forum/development/13888-bilge-bot-logic-%5Bc-source%5D.html

### Building
To build this you will need to run ```make``` within the root directory.
If you're on windows you will need to install tools such as ```g++``` and ```make``` beforehand using applications such as Cygwin or Mingw.

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

Note, the '4' at the end can be any non-alpha character used to represent termination.
A crab is represented by 'X', JellyFish by 'Y' and PufferFish by 'Z'.

The program will respond with your best move, for example
```2 8```
which would correspond to the highlighted move in the diagram above.. (```{0, 0}``` is the top left and ```{5, 11}``` is the bottom right)

### Testing
You will need to compile google tests https://github.com/google/googletest and place ```libgtest.a``` within the root of the ```lib``` folder.
You will also need to have the google test include folder (included as a submodule within this repo) and place it within the ```lib``` folder.

To pull the google test sub module run the command ```git submodule update --init --recursive --remote```


To later remove the sub modules run ```git submodule deinit -f {PATH TO lib/googletest folder}```


To compile google tests on Linux, navigate to lib/googletest/googletest/ and run  ```g++ -isystem include -I . -pthread -c src/gtest-all.cc```


and then run  ```ar -rv libgtest.a gtest-all.o```

then you should move the ```libgtest.a``` file to the root of the ```lib``` folder. e.g.  ```mv libgtest.a ../..```


Afterso, run ```make check``` within the root directory to run the tests.
