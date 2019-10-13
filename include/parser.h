#ifndef PARSER_H
#define PARSER_H

#include "pieces.h"

namespace shogi {
  enum {
    ERR_UNDEFINED = -1,
    ERR_AMBIGUOUS = -2
  };
  
  int parse(char* input, Piece* context);
}

#endif /* PARSER_H */
