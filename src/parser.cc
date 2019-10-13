#include "parser.h"

#include <stddef.h>
#include <stdlib.h>

namespace shogi {

  static char opdrop (char*, Piece*);
  static char opmove (char*, Piece*);
  
  const struct {
    const char* verb;
    const char  req;
    char (*op)(char*, Piece*);
  } syntax[] = {
    {"drop", 2, opdrop},
    {"move", 1, opmove},
    {  NULL, 0,   NULL}
  };
}
/* remove trailing spaces */
static char* rmtrails (char* str)
{
  if (str)
    while (*str == ' ')
      str++;
  return str;
}

char shogi::parse(char* inp, Piece* ctx)
{
  int  mchno = -1; /* number of matched characters */
  int  match = -1; /* most probable match */
  char err = ERR_UNDEFINED;
  char c;
  int  i, j;
  
  if (!inp || !ctx) {
    return 0;
  }
  
  inp = rmtrails(inp);
  
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
    err = syntax[match].op(rmtrails(inp + mchno), ctx);
  
  return err;
}

static char shogi::opmove (char* inp, Piece* ctx)
{
  Piece p;
  char  y, x;
  char  err = ERR_NOPIECE;
  int   i;

  /* make a more flexible version later */
  y = inp[0] - 'a'; /* ebcdic a-i is contiguous, thank god */
  x = inp[1] - '0'; 

  for (i = 0; i < 40; i++) {
    if ((ctx[i].y() == y) &&
	(ctx[i].x() == x)) {
      err = 0;
      p = ctx[i];
      break;
    }
  }

  if (err)
    return err;

  inp += 2;
  y = inp[0] - 'a';
  x = inp[1] - '0';

  if (!p.move(ctx, y, x))
    return ERR_INVALIDMV;

  ctx[i] = p;
  
  return err;
}

static char shogi::opdrop (char* inp, Piece* ctx)
{

  
  return 0;
}
