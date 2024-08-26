#ifndef PIECE_HPP
#define PIECE_HPP

class Piece {
public:
  enum Type : char {
    KING = 'K',
    QUEEN = 'Q',
    ROOK = 'R',
    BISHOP = 'B',
    KNIGHT = 'k',
    PAWN = 'p',
    EMPTY = ' ' // Field is empty
  };
  enum Side { BLACK, WHITE, NONE };

private:
  Type type;
  Side side;
  bool moved;

public:
  /* Constructs empty piece with no side assigned */
  Piece();
  /* Constructs piece with type `t` and side `s` */
  Piece(Type t, Side s);

  /* Returns the type of the piece */
  Type get_type() const;
  /* Changes the type of the piece to queen */
  void change_type();

  /* Returns the side of the piece */
  Side get_side() const;

  /* Returns whether the piece was moved */
  bool has_moved() const;
  /* Marks the piece as moved */
  void mark_moved();

};

#endif
