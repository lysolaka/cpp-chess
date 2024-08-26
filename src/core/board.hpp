#include "piece.hpp"

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

  /* Returns a reference to a piece at `row` and `col`
   * for private use inside the class */
  inline Piece &field_at(char col, int row);
  /* Returns a const reference to a piece at `row` and `col`
   * for private use inside the class */
  inline const Piece &field_at(char col, int row) const;


public:
  /* Constructs the board and places the pieces in appropriate places */
  Board();

  ~Board();

  /* Returns reference to a piece at `row` and `col` */
  Piece &operator[](char col, int row);
  /* Returns const reference to a piece at `row` and `col` */
  const Piece &operator[](char col, int row) const;

  /* Returns reference to a piece at `pos` */
  Piece &operator[](FieldPos pos);
  /* Returns const reference to a piece at `pos` */
  const Piece &operator[](FieldPos pos) const;

  /* Moves a piece from `start_pos` to `end_pos`, this method might throw:
   * std::invalid_argument - if the piece can't perform this movement under any
   * circumstance, std::out_of_range - if the `start_pos` or `end_pos` is
   * outside the board. Returns true if movement was successful, false if the
   * piece can't be moved due to the rules. */
  bool move_piece(FieldPos start_pos, FieldPos end_pos);

  void debug_print() const;
};

#endif
