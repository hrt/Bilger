CC			= g++
CFLAGS  = -std=c++0x -Wall -Werror -pedantic
SRC			= src/
OBJDIR	= obj
SRCDIR	= src
OUTDIR	= bin

OOBJ		= Game.o Parser.o

_DEPS		= Definitions.hpp Game.hpp Parser.hpp Utils.hpp
DEPS    = $(patsubst %,$(SRCDIR)/%,$(_DEPS))

_OBJ		= $(OOBJ) Main.o
OBJ			= $(patsubst %,$(OBJDIR)/%,$(_OBJ))

_TOBJ		= $(OOBJ) Test.o ParserTest.o GameTest.o
TOBJ		=  $(patsubst %,$(OBJDIR)/%,$(_TOBJ))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


$(OUTDIR)/Bilger: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(OUTDIR)/Test:	$(TOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean check all

clean:
	rm -f $(OBJDIR)/*.o $(OUTDIR)/Bilger $(OUTDIR)/Test

check: $(OUTDIR)/Bilger $(OUTDIR)/Test
	./$(OUTDIR)/Test < test.input
