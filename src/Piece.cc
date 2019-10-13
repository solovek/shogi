#include "Piece.h"

#include <stddef.h>

namespace shogi {
  struct PieceType {
    char tile;
    bool (*valid_move) (Piece*, int, int);
  };

  bool pawn_valid_move (Piece*, int, int);
  
  extern const PieceType piece_types[];
}

shogi::Piece::Piece (char t, char y, char x)
{
  type = t;
  my   = y;
  mx   = x;
}

static bool within (int n, int lwr, int upr);

bool shogi::Piece::move (Piece* ctx, char y, char x)
{
  if (within(y, 0, 9) &&
      within(x, 0, 9) &&
      piece_types[this->type].valid_move(this, y, x)) {
    my = y;
    mx = x;
    return true;
  }

  return false;
}

static bool within (int n, int lwr, int upr)
{
  return ((lwr <= n) &&
	  (upr >  n));
}

char shogi::Piece::print (void)
{
  return piece_types[this->type].tile;
}

bool shogi::Piece::exists (void)
{
  return this->type;
}

namespace shogi {
  const PieceType piece_types[] = {
    {'?', NULL}, {'p', pawn_valid_move},
    {'l', NULL}, {'n', NULL},
    {'s', NULL}, {'g', NULL},
    {'b', NULL}, {'r', NULL},
    {'k', NULL}
  };
  
  bool pawn_valid_move (Piece* p, int y, int x)
  {
    return (x ==  p->x() &&
	    y == (p->y() + 1));
  }
}
