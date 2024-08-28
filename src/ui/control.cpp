#include "control.hpp"
#include <cwchar>
#include <stdexcept>

void Control::print_prompt(Board::FieldPos &s, Board::FieldPos &e) const {
  std::wprintf(L"\nCurrent move is: ");
  switch (board.get_move()) {
  case Piece::BLACK:
    std::wprintf(L"BLACK\n");
    break;
  case Piece::WHITE:
    std::wprintf(L"WHITE\n");
    break;
  }
  std::wprintf(L"Select piece (example: d2), 'qq' - quits\n: ");
  std::wscanf(L" %c%d", &s.col, &s.row);
  if (s.col == 'q') {
    return;
  }
  std::wprintf(L"Select move (example: d4), 'qq' - quits\n: ");
  std::wscanf(L" %c%d", &e.col, &e.row);
}

/* Constructs control module from a display and a board */
Control::Control(Display &d, Board &b) : display(d), board(b), running(true) {}

/* Main game loop inside */
void Control::loop() {
  Board::FieldPos start_pos('a', 1);
  Board::FieldPos end_pos('a', 1);

  while (running) {
    display.print();
    print_prompt(start_pos, end_pos);
    if (start_pos.col == 'q' || end_pos.col == 'q') {
      std::wprintf(L"Ending... thanks for playing.\n");
      running = false;
    }
    if (running) {
      try {
        board.move_piece(start_pos, end_pos);
      } catch (std::invalid_argument &a) {
        wprintf(L"%s\n", a.what());
      }
    }
    std::wprintf(L"\n");
  }
}
