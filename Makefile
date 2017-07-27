CC			= g++
OBJDIR	= obj
CFLAGS  = -std=gnu++0x -Wall -Werror -pedantic -pthread -isystem $(LIBDIR)/googletest/googletest/include/
LIBDIR  = lib
CTFLAGS = $(CFLAGS) -I $(SRCDIR)
SRCDIR	= src
TESTDIR = test
OUTDIR	= bin

OOBJ		= Game.o Parser.o

_DEPS		= Definitions.hpp Game.hpp Parser.hpp Utils.hpp
DEPS    = $(patsubst %,$(SRCDIR)/%,$(_DEPS))

_OBJ		= $(OOBJ) Main.o
OBJ			= $(patsubst %,$(OBJDIR)/%,$(_OBJ))

_TOBJ		= $(OOBJ) ParserTest.o GameTest.o
TOBJ		=  $(patsubst %,$(OBJDIR)/%,$(_TOBJ))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJDIR)/%.o: $(TESTDIR)/%.cc $(DEPS)
	$(CC) -c -o $@ $< $(CTFLAGS)

$(OUTDIR)/Bilger: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBDIR)/googletest/googletest/libgtest.a

$(OUTDIR)/Test:	$(TOBJ)
	$(CC) -o $@ $^ $(CTFLAGS) $(LIBDIR)/googletest/googletest/src/gtest_main.cc $(LIBDIR)/googletest/googletest/libgtest.a

.PHONY: clean check all

clean:
	rm -f $(OBJDIR)/*.o $(OUTDIR)/Bilger $(OUTDIR)/Test

check: $(OUTDIR)/Bilger $(OUTDIR)/Test
