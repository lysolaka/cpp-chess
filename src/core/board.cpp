#include "board.hpp"
#include "piece.hpp"
#include <initializer_list>
#include <stdexcept>

/* Type to pass a position as a single argument
 * col - any char from 'a' to 'h' (inclusive)
 * row - any int from 1 to 8 (inclusive) */
Board::FieldPos::FieldPos(char c, int r) : col(c), row(r) {}

bool operator==(Board::FieldPos const &l, Board::FieldPos const &r) {
  return (l.row == r.row && l.col == r.col);
}

/* Returns a reference to a piece at `row` and `col`
 * for private use inside the class */
inline Piece &Board::field_at(char col, int row) {
  return field[col - 'a' + (row - 1) * 8];
}
/* Returns a const reference to a piece at `row` and `col`
 * for private use inside the class */
inline const Piece &Board::field_at(char col, int row) const {
  return field[col - 'a' + (row - 1) * 8];
}

/* Checks if `pos` is inside the board */
bool Board::is_inside(FieldPos const &pos) {
  if ((pos.col < 'a' || pos.col > 'h') || (pos.row < 1 || pos.row > 8))
    return false;
  else
    return true;
}

/* Checks if `pos` is occupied by a piece */
inline bool Board::is_occupied(FieldPos const &pos) const {
  if (field_at(pos.col, pos.row).get_type() != Piece::EMPTY)
    return true;
  else
    return false;
}

/* Returns a vector of possible positions a piece can move to,
 * empty - if `pos` points to an empty field */
std::vector<Board::FieldPos> Board::possible_moves(FieldPos const &pos) const {
  std::vector<FieldPos> moves;
  moves.clear();
  Piece selected = field_at(pos.col, pos.row);
  FieldPos cur = pos;

  switch (selected.get_type()) {
  case Piece::KING:
    for (char c : {-1, 0, 1}) {
      for (int r : {-1, 0, 1}) {
        if (c != r != 0) {
          cur = FieldPos(pos.col + c, pos.row + r);
          if (is_inside(cur)) {
            if (!is_occupied(cur))
              moves.push_back(cur);
            else if (field_at(cur.col, cur.row).get_side() != current_move)
              moves.push_back(cur);
          }
        }
      }
    }
    break;
  case Piece::QUEEN:
    [[fallthrough]];
  case Piece::ROOK:
    for (int i = pos.row + 1; i <= 8; i++) {
      cur = FieldPos(pos.col, i);
      if (is_occupied(cur) &&
          field_at(cur.col, cur.row).get_side() != current_move) {
        moves.push_back(cur);
        break;
      } else if (is_occupied(cur)) {
        break;
      }
      moves.push_back(cur);
    }
    for (int i = pos.row - 1; i >= 1; i--) {
      cur = FieldPos(pos.col, i);
      if (is_occupied(cur) &&
          field_at(cur.col, cur.row).get_side() != current_move) {
        moves.push_back(cur);
        break;
      } else if (is_occupied(cur)) {
        break;
      }
      moves.push_back(cur);
    }
    for (char i = pos.col + 1; i <= 'h'; i++) {
      cur = FieldPos(i, pos.row);
      if (is_occupied(cur) &&
          field_at(cur.col, cur.row).get_side() != current_move) {
        moves.push_back(cur);
        break;
      } else if (is_occupied(cur)) {
        break;
      }
      moves.push_back(cur);
    }
    for (char i = pos.col - 1; i >= 'a'; i--) {
      cur = FieldPos(i, pos.row);
      if (is_occupied(cur) &&
          field_at(cur.col, cur.row).get_side() != current_move) {
        moves.push_back(cur);
        break;
      } else if (is_occupied(cur)) {
        break;
      }
      moves.push_back(cur);
    }
    if (selected.get_type() == Piece::ROOK)
      break;
    [[fallthrough]];
  case Piece::BISHOP:
    for (int i = 1;; i++) {
      cur = FieldPos(pos.col + i, pos.row + i);
      if (!is_inside(cur))
        break;
      if (is_occupied(cur) &&
          field_at(cur.col, cur.row).get_side() != current_move) {
        moves.push_back(cur);
        break;
      } else if (is_occupied(cur)) {
        break;
      }
      moves.push_back(cur);
    }
    for (int i = 1;; i++) {
      cur = FieldPos(pos.col - i, pos.row - i);
      if (!is_inside(cur))
        break;
      if (is_occupied(cur) &&
          field_at(cur.col, cur.row).get_side() != current_move) {
        moves.push_back(cur);
        break;
      } else if (is_occupied(cur)) {
        break;
      }
      moves.push_back(cur);
    }
    for (int i = 1;; i++) {
      cur = FieldPos(pos.col + i, pos.row - i);
      if (!is_inside(cur))
        break;
      if (is_occupied(cur) &&
          field_at(cur.col, cur.row).get_side() != current_move) {
        moves.push_back(cur);
        break;
      } else if (is_occupied(cur)) {
        break;
      }
      moves.push_back(cur);
    }
    for (int i = 1;; i++) {
      cur = FieldPos(pos.col - i, pos.row + i);
      if (!is_inside(cur))
        break;
      if (is_occupied(cur) &&
          field_at(cur.col, cur.row).get_side() != current_move) {
        moves.push_back(cur);
        break;
      } else if (is_occupied(cur)) {
        break;
      }
      moves.push_back(cur);
    }
    break;
  case Piece::KNIGHT:
    for (auto p : {FieldPos(pos.col - 2, pos.row + 1),
                   FieldPos(pos.col - 1, pos.row + 2),
                   FieldPos(pos.col + 1, pos.row + 2),
                   FieldPos(pos.col + 2, pos.row + 1),
                   FieldPos(pos.col + 2, pos.row - 1),
                   FieldPos(pos.col + 1, pos.row - 2),
                   FieldPos(pos.col - 2, pos.row - 1),
                   FieldPos(pos.col - 1, pos.row - 2)}) {
      if (is_inside(p)) {
        if (!is_occupied(p))
          moves.push_back(p);
        else if (field_at(p.col, p.row).get_side() != current_move)
          moves.push_back(p);
      }
    }
    break;
  case Piece::PAWN: {
    int pl_min_one = selected.get_side() == Piece::WHITE ? 1 : -1;
    cur.row += pl_min_one;
    if (!is_occupied(cur))
      moves.push_back(cur);

    cur.row += pl_min_one;
    if (!is_occupied(cur) && !selected.has_moved())
      moves.push_back(cur);

    cur = pos;
    cur.row += pl_min_one;
    for (int i : {-1, 1}) {
      if (is_occupied(FieldPos(cur.col + i, cur.row)) &&
          field_at(cur.col + i, cur.row).get_side() != current_move)
        moves.push_back(FieldPos(cur.col + i, cur.row));
    }
  } break;
  case Piece::EMPTY:
    break;
  }

  return moves;
}

/* Constructs the board and places the pieces in appropriate places */
Board::Board() : field(nullptr), current_move(Piece::WHITE) {
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

/* Moves a piece from position `start` to position `end`,
 * may throw std::invalid_argument if `end` is not a viable position for the
 * selected piece */
void Board::move_piece(FieldPos const &start, FieldPos const &end) {
  if (field_at(start.col, start.row).get_side() != current_move)
    throw std::invalid_argument("Invalid piece selected!");

  auto moves = possible_moves(start);
  bool found = false;
  for (FieldPos const &i : moves) {
    if (end == i)
      found = true;
    if (found)
      break;
  }
  if (!found)
    throw std::invalid_argument("Invalid position supplied!");

  field_at(start.col, start.row).mark_moved();
  field_at(end.col, end.row) = field_at(start.col, start.row);
  field_at(start.col, start.row) = Piece();

  if (current_move == Piece::WHITE)
    current_move = Piece::BLACK;
  else
    current_move = Piece::WHITE;
}

/* Returns the side which should perform next move */
Piece::Side Board::get_move() const { return current_move; }

#ifdef CPP_CHESS_DEBUG
#include <iostream>
void Board::debug_print() const {
  for (int i = 8; i > 0; i--) {
    for (char c = 'a'; c < 'h' + 1; c++) {
      std::cout << c << i << ": " << field_at(c, i).get_type() << " | ";
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}
#endif
