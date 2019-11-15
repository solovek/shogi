CC  = g++
EXE = shogi 
SRC = $(shell find . -name "*.cc")
OBJ = $(addsuffix .o,$(basename $(SRC)))

DEP = ncurses

CFLAG = `pkg-config $(DEP) --cflags`
LFLAG = `pkg-config $(DEP) --libs`
INCL  = -Iinclude

.SUFFIXES: .cc .o .pdf .tex
.PHONY: all test clean

.cc.o:
	$(CC) -c -o $@ $< $(CFLAG) $(INCL)

.tex.pdf:
	pdflatex $<

all: shogi report.pdf

clean:
	rm $(OBJ) $(EXE)

shogi: $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(LFLAG)

test: shogi
	./shogi
