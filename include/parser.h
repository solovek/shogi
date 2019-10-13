#ifndef PARSER_H
#define PARSER_H

#include "Piece.h"

namespace shogi {
  enum {
    ERR_UNDEFINED = -1,
    ERR_AMBIGUOUS = -2,
    ERR_INVALIDMV = -3,
    ERR_NOPIECE   = -4
  };
  
  char parse(char* input, Piece* context);
}

#endif /* PARSER_H */
