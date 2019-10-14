#include "parser.h"

#include <ncurses.h>
#include <regex.h>
#include <stddef.h>
#include <stdlib.h>

namespace shogi {
  extern const char* const expr;
  regex_t regex;
}

static bool originchk (shogi::Piece& p, char y, char x)
{
  return ((p.y() == y) &&
	  (p.x() == x));
}

int shogi::parse(char* inp, Piece* ctx)
{
  Piece* match;
  regmatch_t cmdmatch[4] = {0};
  char err = ERR_UNDEFINED;
  
  if (!regexec(&regex, inp, 4, cmdmatch, 0)) {
    bool has_origin = false;
    bool has_promot = false;
    char type;
    char move;
    char y, x;
    int  cnt = 0;

    type = *inp++;
    
    if (cmdmatch[2].rm_so != cmdmatch[2].rm_eo) {
      has_origin = true;
      y = *inp++ - 'a';
      x = *inp++ - '0';
    }

    move = *inp++;
    
    for (int i = 0; i < 40; i++)
      if (ctx[i].print() == type) {
	if (!has_origin ||
	     has_origin &&
	    originchk(ctx[i], y, x)) {
	  match = &ctx[i];
	  cnt++;
	}
      }
    
    if (cnt < 1)
      return ERR_NOPIECE;
    else if (cnt > 1)
      return ERR_AMBIGUOUS;
    
    y = *inp++ - 'a';
    x = *inp++ - '0';
    
    match->move(ctx, y, x);
  }
  
  return err;
}

const char* const shogi::expr =
  "^([:alpha:])([a-i][0-8]){,1}([-x*][a-i][0-8])([+]){,1}$";

int shogi::init_parser()
{
  return regcomp(&regex, expr, REG_ICASE | REG_EXTENDED);
}
