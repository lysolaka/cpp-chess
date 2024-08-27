#include "../core/board.hpp"
#include "../core/piece.hpp"

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

class Display {
private:
  static const char *h_line;

  const Board &board;

  /* Prints piece unicode symbol as a wide character */
  static void print_piece(Piece const &target);
  /* Prints color escape sequence for the side */
  inline static void print_color(Piece::Side side);
  /* Prints color ending escape sequence */
  inline static void end_color();

public:
  /* Constructs display from Board */
  Display(Board const &b);

  /* Prints the state of the board at the current moment */
  void print() const;
};

#endif
