#include "parser.h"

#include <ncurses.h>
#include <regex.h>
#include <stddef.h>
#include <stdlib.h>

namespace shogi {
  regex_t regex;
}

/* remove trailing spaces */
static char* rmtrails (char* str)
{
  if (str)
    while (*str == ' ')
      str++;
  return str;
}

int shogi::parse(char* inp, Piece* ctx)
{
  Piece* match;
  int    matchcnt;
  regmatch_t cmdmatch[3] = {0};
  char err = ERR_UNDEFINED;
  
  if (!regexec(&regex, inp, 3, cmdmatch, 0)) {
    char y, x;
    matchcnt = 0;
    
    if (cmdmatch[1].rm_so != cmdmatch[1].rm_eo) {
      char type = *inp++;

      for (int i = 0; i < 40; i++)
	if (ctx[i].print() == type) {
	  match = &ctx[i];
	  matchcnt++;
	}
    } else if (cmdmatch[2].rm_so != cmdmatch[2].rm_eo) {
      y = *inp++ - 'a';
      x = *inp++ - '0';

      for (int i = 0; i < 40; i++)
	if ((ctx[i].y() == y) &&
	    (ctx[i].x() == x)) {
	  match = &ctx[i];
	  matchcnt++;
	}
    }
    
    if (matchcnt < 1)
      return ERR_NOPIECE;
    else if (matchcnt > 1)
      return ERR_AMBIGUOUS;

    y = *inp++ - 'a';
    x = *inp++ - '0';
    
    match->move(ctx, y, x);
  }
  
  return err;
}

int shogi::init_parser()
{
  return regcomp(&regex, "^([:alpha:][a-i][0-8])|([a-i][0-8][a-i][0-8])",
		 REG_ICASE | REG_EXTENDED);
}
