CC  = gcc
EXE = shogi 
OBJ = $(shell find . -name "*.cc")

DEP = ncurses

CFLAG = `pkg-config $(DEP) --cflags`
LFLAG = `pkg-config $(DEP) --libs`
INCL  = -Iinclude

all:
	$(CC) -o $(EXE) $(OBJ) $(CFLAG) $(INCL) $(LFLAG)
