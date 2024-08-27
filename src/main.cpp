#include "core/board.hpp"
#include <iostream>
#include <stdexcept>

int main() {
  Board b;
  b.debug_print();
  try {
  b.move_piece(Board::FieldPos('d', 2), Board::FieldPos('d', 4));
  } catch(std::invalid_argument a) {
    std::cout << '1' << '\n';
  }
  try {
  b.move_piece(Board::FieldPos('d', 7), Board::FieldPos('d', 5));
  } catch(std::invalid_argument a) {
    std::cout << '2' << '\n';
  }
  try {
  b.move_piece(Board::FieldPos('c', 1), Board::FieldPos('f', 4));
  } catch(std::invalid_argument a) {
    std::cout << '3' << '\n';
  }
  b.debug_print();

  return 0;
}
