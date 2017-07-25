CC			= g++
OBJDIR	= obj
CFLAGS  = -std=c++0x -Wall -Werror -pedantic
LIBDIR  = lib
CTFLAGS = $(CFLAGS) -I $(SRCDIR) -pthread -isystem $(LIBDIR)/googletest/include/ $(LIBDIR)/libgtest.a
SRCDIR	= src
TESTDIR = test
OUTDIR	= bin

OOBJ		= Game.o Parser.o

_DEPS		= Definitions.hpp Game.hpp Parser.hpp Utils.hpp
DEPS    = $(patsubst %,$(SRCDIR)/%,$(_DEPS))

_OBJ		= $(OOBJ) Main.o
OBJ			= $(patsubst %,$(OBJDIR)/%,$(_OBJ))

_TOBJ		= $(OOBJ) Test.o
TOBJ		=  $(patsubst %,$(OBJDIR)/%,$(_TOBJ))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CTFLAGS)

$(OUTDIR)/Bilger: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(OUTDIR)/Test:	$(TOBJ)
	$(CC) -o $@ $^ $(CTFLAGS)

.PHONY: clean check all

clean:
	rm -f $(OBJDIR)/*.o $(OUTDIR)/Bilger $(OUTDIR)/Test

check: $(OUTDIR)/Bilger $(OUTDIR)/Test
			./$(OUTDIR)/Test < test.input
