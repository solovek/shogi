#include "parser.h"

#include <stddef.h>
#include <ncurses.h>

namespace shogi {

  static int opdrop (char*, Piece*);
  static int opmove (char*, Piece*);
  
  const struct {
    const char* verb;
    const char  req;
    int (*op)(char*, Piece*);
  } syntax[] = {
    {"drop", 2, opdrop},
    {"move", 1, opmove},
    {  NULL, 0,   NULL}
  };
  
  int parse(char* inp, Piece* ctx)
  {
    int  mchno = -1; /* number of matched characters */
    int  match = -1; /* most probable match */
    int  err   = ERR_UNDEFINED;
    int  i, j;
    char c;

    if (!inp || !ctx) {
      return 0;
    }
    
    /* remove trailing spaces */
    while (*inp == ' ')
      inp++;

    /* look through the syntax definitions for the
     * most probable match
     */
    for (i = 0; syntax[i].verb; i++) {
      if (syntax[i].verb) { 
	for (j = 0;; inp++, j++) {
	  c = *inp;

	  if (c != syntax[i].verb[j]) {
	    if (j == mchno) {
	      match = -1;
	      err   = ERR_AMBIGUOUS;
	    } else if (j > mchno) {
	      match = i;
	      mchno = j;
	      err   = 0;
	    }
	    
	    break;
	  }
	}
	
	inp -= j;
      }
    }

    if (match >= 0)
      err = syntax[match].op(inp + mchno, ctx);

    return err;
  }

  static int opmove (char* inp, Piece* ctx)
  {
    mvprintw(21, 0, "move");
    
    return 0;
  }

  static int opdrop (char* inp, Piece* ctx)
  {
    mvprintw(21, 0, "drop");
    
    return 0;
  }
}
