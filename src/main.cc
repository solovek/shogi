#include <forward_list>
#include <memory>
#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "parser.h"
#include "pieces.h"

using namespace std;

WINDOW* boardwnd;
WINDOW* dropwnd[2];

int shogi_loop ();

int main (int argc, char** argv)
{
  int width, height;
  int i;

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

  mvprintw(20, 0, ">");
  
  shogi_loop();
  
  endwin();

  return 0;
}

static void prngrid   ();
static void prnpieces (shogi::Piece*);
static void update    ();

int shogi_loop ()
{
  shogi::Piece pieces[40] = {0};
  shogi::Piece p = {0};
  char* inp;
  int i;
  
  inp = (char*)calloc(64, sizeof(char));
  pieces[0] = {1, 1, 1};
  
  for(;;) {
    prngrid();
    prnpieces(pieces);
    
    update();

    mvgetnstr(20, 1, inp, 64);

    shogi::parse(inp, pieces);
  }
}

static void prngrid ()
{
  static const wchar_t* grid[] = {
    L" ",      L"\u2502",
    L"\u2500", L"\u253C"
  };
  
  for (int i = 1; i < 18; i++) {
    for (int j = 1; j < 18; j++) {      
      mvwaddwstr(boardwnd, i, j, grid[i % 2? (j % 2? 0 : 1) :
				             (j % 2? 2 : 3)]);
    }
  }
}

static void prnpieces (shogi::Piece* pieces)
{
  shogi::Piece p;
  
  for (int i = 0; i < 40; i++)
    if ((p = pieces[i]).type)
	mvwaddch(boardwnd, (p.y * 2) + 1, (p.x * 2) + 1,
		 shogi::piece_types[p.type].tile);
}

static void update ()
{
  wrefresh(dropwnd[0]);
  wrefresh(dropwnd[1]);
  wrefresh(boardwnd);    
  refresh();
}

namespace shogi {  
  const PieceType piece_types[] = {
    {'?', NULL}, {'p', pawn_valid_move}, {'l', NULL},
    {'n', NULL}, {'s', NULL}, {'g', NULL},
    {'b', NULL}, {'r', NULL}, {'k', NULL}
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
