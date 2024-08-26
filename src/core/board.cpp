#include "board.hpp"
#include "piece.hpp"
#include <initializer_list>

/* Type to pass a position as a single argument
 * col - any char from 'a' to 'h' (inclusive)
 * row - any int from 1 to 8 (inclusive) */
Board::FieldPos::FieldPos(char c, int r) : col(c), row(r) {}

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
inline bool Board::is_occupied(Board::FieldPos const &pos) const {
  if (field_at(pos.col, pos.row).get_type() != Piece::EMPTY)
    return true;
  else
    return false;
}

/* Returns a vector of possible positions a piece can move to,
 * empty - if `pos` points to an empty field */
std::vector<Board::FieldPos>
Board::possible_moves(Board::FieldPos const &pos) const {
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
  case Piece::PAWN:
    cur = FieldPos(pos.col, pos.row + 1);
    if (!is_inside(cur))
      break;
    if (!is_occupied(cur))
      moves.push_back(cur);

    cur.row++;
    if (!selected.has_moved()) {
      if (!is_occupied(cur))
        moves.push_back(cur);
    }
    cur.row--;
    {
      int temp = cur.col;
      cur.col -= 1;
      if (is_inside(cur)) {
        if (field_at(cur.col, cur.row).get_side() != current_move &&
            field_at(cur.col, cur.row).get_type() != Piece::EMPTY)
          moves.push_back(cur);
      }
      cur.col = temp + 1;
      if (is_inside(cur)) {
        if (field_at(cur.col - 1, cur.row).get_side() != current_move &&
            field_at(cur.col, cur.row).get_type() != Piece::EMPTY)
          moves.push_back(cur);
      }
    }
    break;
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

/* Returns reference to a piece at `pos` */
Piece &Board::operator[](FieldPos const &pos) {
  return field_at(pos.col, pos.row);
}
/* Returns const reference to a piece at `pos` */
const Piece &Board::operator[](FieldPos const &pos) const {
  return field_at(pos.col, pos.row);
}

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
