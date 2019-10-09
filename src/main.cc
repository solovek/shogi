#include <stdio.h>
#include <ncurses.h>

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

WINDOW* boardwnd = NULL;

int shogi_loop ();

int main (int argc, char** argv)
{
  int width, height;

  /* read argv for multiplayer opt */

  initscr();
  getmaxyx(stdscr, width, height);

  boardwnd = newwin(11, 20, 1, 0);
  refresh();
  wborder(boardwnd, '|', '|', '-', '-', '+', '+', '+', '+');

  shogi_loop();
  
  endwin();

  return 0;
}

int shogi_loop ()
{
  for(;;) {
    
    
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
      }
    }
  }
}
