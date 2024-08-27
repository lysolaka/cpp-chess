#include "display.hpp"
#include <cwchar>

const char *Display::h_line = "+---+---+---+---+---+---+---+---+";

/* Prints piece unicode symbol as a wide character */
void Display::print_piece(Piece const &target) {
  wchar_t symbol = 0x2654;
#ifdef CPP_CHESS_DEBUG
  switch (target.get_type()) {
  case Piece::KING:
    break;
  case Piece::QUEEN:
    symbol += 1;
    break;
  case Piece::ROOK:
    symbol += 2;
    break;
  case Piece::BISHOP:
    symbol += 3;
    break;
  case Piece::KNIGHT:
    symbol += 4;
    break;
  case Piece::PAWN:
    symbol += 5;
    break;
  }
#else
  if (target.get_type() == Piece::EMPTY) {
    std::wprintf(L" ");
    return;
  }

  symbol += target.get_type();

#endif
  if (target.get_side() == Piece::WHITE)
    symbol += 6;
  std::wprintf(L"%lc", symbol);
}

/* Prints color escape sequence for the side */
void Display::print_color(Piece::Side side) {
  switch (side) {
  case Piece::BLACK:
    std::wprintf(L"\e[1;31m");
    break;
  case Piece::WHITE:
    std::wprintf(L"\e[1;37m");
    break;
  case Piece::NONE:
    break;
  }
}
/* Prints color ending escape sequence */
void Display::end_color() { std::wprintf(L"\e[0m"); }

/* Constructs display from Board */
Display::Display(Board const &b) : board(b) {}

/* Prints the state of the board at the current moment */
void Display::print() const {
  std::wprintf(L"%s\n", h_line);
  for (int row = 8; row > 0; row--) {
    for (char col = 'a'; col <= 'h'; col++) {
      std::wprintf(L"| ");
#ifdef CPP_CHESS_COLOR
      print_color(board[col, row].get_side());
#endif
      print_piece(board[col, row]);
#ifdef CPP_CHESS_COLOR
      end_color();
#endif
      std::wprintf(L" ");
    }
    std::wprintf(L"| %d\n", row);
    std::wprintf(L"%s\n", h_line);
  }
  for (char col = 'a'; col <= 'h'; col++) {
    std::wprintf(L"  %c ", col);
  }
  std::wprintf(L"\n");
}
