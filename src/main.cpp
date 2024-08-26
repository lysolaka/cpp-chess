#include "core/board.hpp"
#include "core/piece.hpp"
#include <iostream>

int main() {
  Board b;
  b.debug_print();
  auto v = b.possible_moves(Board::FieldPos('a', 2));
  for (auto i : v) {
    std::cout << i.col << i.row << '\n';
  }

  b['c', 4] = Piece(Piece::QUEEN, Piece::WHITE);
  b['d', 1] = Piece();
  b.debug_print();
  v = b.possible_moves(Board::FieldPos('c', 4));
  for (auto i : v) {
    std::cout << i.col << i.row << '\n';
  }
  return 0;
}
