#ifndef PIECE_H
#define PIECE_H

namespace shogi {
  enum {
    error  = 0,
    pawn   = 1,
    lance  = 2,
    knight = 3,
    silver = 4,
    gold   = 5,
    bishop = 6,
    rook   = 7,
    king   = 8
  };
  
  class Piece {
  public:
    Piece (char type = error, char y = -1, char x = -1);

    bool move   (Piece* context, char y, char x);
    char print  (void);
    bool exists (void);

    char type (void);
    char y    (void);
    char x    (void);
    
  private:
    char mtype;
    char my, mx;
  };

  inline char Piece::type (void) {return mtype;}
  inline char Piece::y    (void) {return my;}
  inline char Piece::x    (void) {return mx;}

  enum {
    SEARCH_POS,
    SEARCH_TYPE
  };
}

#endif /* PIECES_H */
