CC  = g++
EXE = shogi 
OBJ = $(shell find . -name "*.cc")

DEP = ncursesw

CFLAG = `pkg-config $(DEP) --cflags`
LFLAG = `pkg-config $(DEP) --libs`
INCL  = -Iinclude

all:
	$(CC) -o $(EXE) $(OBJ) $(CFLAG) $(INCL) $(LFLAG)

test: all
	./shogi

report: 
	pdflatex report.tex
