#include "board.hpp"
#include "piece.hpp"
#include <initializer_list>

/* Type to pass a position as a single argument
 * col - any char from 'a' to 'h' (inclusive)
 * row - any int from 1 to 8 (inclusive) */
Board::FieldPos::FieldPos(char c, int r) : col(c), row(r) {}

/* Returns a reference to a piece at `row` and `col`
 * for private use inside the class */
Piece &Board::field_at(char col, int row) {
  return field[col - 'a' + (row - 1) * 8];
}
/* Returns a const reference to a piece at `row` and `col`
 * for private use inside the class */
const Piece &Board::field_at(char col, int row) const {
  return field[col - 'a' + (row - 1) * 8];
}

/* Constructs the board and places the pieces in appropriate places */
Board::Board() : field(nullptr) {
  field = new Piece[64];
  // Place the pawns
  for (char c = 'a'; c <= 'h'; c++) {
    field_at(c, 2) = Piece(Piece::PAWN, Piece::WHITE);
    field_at(c, 7) = Piece(Piece::PAWN, Piece::BLACK);
  }

  // Place the rest
  char c = 'a';
  for (auto p : {Piece::ROOK, Piece::KNIGHT, Piece::BISHOP}) {
    field_at(c, 1) = Piece(p, Piece::WHITE);
    field_at(c, 8) = Piece(p, Piece::BLACK);
    field_at('h' - (c - 'a'), 1) = Piece(p, Piece::WHITE);
    field_at('h' - (c - 'a'), 8) = Piece(p, Piece::BLACK);
    c++;
  }
  field_at('d', 1) = Piece(Piece::QUEEN, Piece::WHITE);
  field_at('e', 1) = Piece(Piece::KING, Piece::WHITE);
  field_at('d', 8) = Piece(Piece::QUEEN, Piece::BLACK);
  field_at('e', 8) = Piece(Piece::KING, Piece::BLACK);
}

Board::~Board() { delete[] field; }

/* Returns reference to a piece at `row` and `col` */
Piece &Board::operator[](char col, int row) { return field_at(col, row); }
/* Returns const reference to a piece at `row` and `col` */
const Piece &Board::operator[](char col, int row) const {
  return field_at(col, row);
}

/* Returns reference to a piece at `pos` */
Piece &Board::operator[](FieldPos pos) { return field_at(pos.col, pos.row); }
/* Returns const reference to a piece at `pos` */
const Piece &Board::operator[](FieldPos pos) const {
  return field_at(pos.col, pos.row);
}

/* Moves a piece from `start_pos` to `end_pos`, this method might throw:
 * std::invalid_argument - if the piece can't perform this movement under any
 * circumstance, std::out_of_range - if the `start_pos` or `end_pos` is
 * outside the board. Returns true if movement was successful, false if the
 * piece can't be moved due to the rules. */
bool Board::move_piece(Board::FieldPos start_pos, Board::FieldPos end_pos) { return true; }
