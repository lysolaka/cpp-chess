#include "core/board.hpp"
#include "ui/display.hpp"
#include <clocale>

int main() {
  setlocale(LC_ALL, "C.UTF-8");
  Board b;
  Display d(b);
  
  b.move_piece(Board::FieldPos('d', 2), Board::FieldPos('d', 4));
  b.move_piece(Board::FieldPos('d', 7), Board::FieldPos('d', 5));
  b.move_piece(Board::FieldPos('c', 1), Board::FieldPos('f', 4));
  d.print();

  return 0;
}
