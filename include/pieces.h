#ifndef PIECES_H
#define PIECES_H

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

#endif /* PIECES_H */
