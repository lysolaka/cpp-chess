#include "piece.hpp"
#include <vector>

#ifndef BOARD_HPP
#define BOARD_HPP

class Board {
public:
  /* Type to pass a position as a single argument
   * col - any char from 'a' to 'h' (inclusive)
   * row - any int from 1 to 8 (inclusive) */
  struct FieldPos {
    char col;
    int row;

    FieldPos(char c, int r);
  };

private:
  /* Array of size 64 storing each piece like a chess board does */
  Piece *field;
  /* Stores the side which can now move its pieces */
  Piece::Side current_move;

  /* Returns a reference to a piece at `row` and `col`
   * for private use inside the class */
  inline Piece &field_at(char col, int row);
  /* Returns a const reference to a piece at `row` and `col`
   * for private use inside the class */
  inline const Piece &field_at(char col, int row) const;

  /* Checks if `pos` is inside the board */
  static bool is_inside(FieldPos const &pos);
  /* Checks if `pos` is occupied by a piece */
  inline bool is_occupied(FieldPos const &pos) const;
#ifdef CPP_CHESS_DEBUG
public:
#endif
  /* Returns a vector of possible positions a piece can move to,
   * empty - if `pos` points to an empty field */
  std::vector<FieldPos> possible_moves(FieldPos const &pos) const;

public:
  /* Constructs the board and places the pieces in appropriate places */
  Board();
  ~Board();

  /* Returns reference to a piece at `row` and `col` */
  Piece &operator[](char col, int row);
  /* Returns const reference to a piece at `row` and `col` */
  const Piece &operator[](char col, int row) const;

  /* Returns reference to a piece at `pos` */
  Piece &operator[](FieldPos const &pos);
  /* Returns const reference to a piece at `pos` */
  const Piece &operator[](FieldPos const &pos) const;

#ifdef CPP_CHESS_DEBUG
  void debug_print() const;
#endif
};

#endif
