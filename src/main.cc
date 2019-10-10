#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

namespace shogi {
  struct Piece {
    char type;
    char y, x;
  };

  struct PieceType {
    char tile;
    bool (*valid_move) (Piece, int, int);
  };

  bool pawn_valid_move (Piece, int, int);

  extern const PieceType piece_types[];
}

using namespace std;

WINDOW* boardwnd;
WINDOW* dropwnd[2];

int shogi_loop ();

const char* player[] = {
  "Black",
  "White"
};

int main (int argc, char** argv)
{
  int width, height;
  int i, j;

  setlocale(LC_ALL, "");

  //gui = load_gui("data/gui.txt");
  
  /* read argv for multiplayer opt */

  initscr();
  getmaxyx(stdscr, width, height);

  /* interface init code */
  boardwnd   = newwin(19, 19,  1,  7);
  dropwnd[0] = newwin( 6,  6,  1,  0);
  dropwnd[1] = newwin( 6,  6, 14, 27);
  refresh();
  box(boardwnd,   0, 0);
  box(dropwnd[0], 0, 0);
  box(dropwnd[1], 0, 0);
  /*
  mvprintw(21, 20, "%s", player[0]);
  mvprintw( 0,  7, "%s", player[1]);
  */
  mvprintw(0, 8, "9 8 7 6 5 4 3 2 1");
  for (i = 0; i < 18; i += 2)
    mvaddch(i+2, 26, "abcdefghi"[i/2]);

  for (i = 1; i < 18; i++) {
    for (j = 1; j < 18; j++) {
      const wchar_t* ws[] = {
	L" ",      L"\u2502",
	L"\u2500", L"\u253C"
      };
      
      mvwaddwstr(boardwnd, i, j, ws[i % 2? (j % 2? 0 : 1) :
				           (j % 2? 2 : 3)]);
    }
  }
  
  mvprintw(20, 0, ">");
  
  shogi_loop();
  
  endwin();

  return 0;
}

int shogi_loop ()
{
  for(;;) {
    getch();

    wrefresh(dropwnd[0]);
    wrefresh(dropwnd[1]);
    wrefresh(boardwnd);    
    refresh();
  }
}

namespace shogi {  
  const PieceType piece_types[] = {
    {'p', pawn_valid_move}, {'?', NULL}
  };

  static bool within (int n, int lwr, int upr)
  {
    return ((lwr <= n) &&
	    (upr >  n));
  }

  bool pawn_valid_move (Piece p, int y, int x)
  {
    /* bounds checking, maybe up */
    if (within(y, 0, 9) &&
	within(x, 0, 9)) {
      if (x ==  p.x &&
	  y == (p.y + 1)) {
	/* check for a collision also */
	p.y = y;
	p.x = x;
	return true;
      }
    }

    return false;
  }
}
