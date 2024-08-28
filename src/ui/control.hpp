#include "../core/board.hpp"
#include "display.hpp"

#ifndef CONTROL_HPP
#define CONTROL_HPP

class Control {
private:
  Display &display;
  Board &board;
  bool running;

  /* Prints the prompt asking for the move to be performed */
  void print_prompt(Board::FieldPos &s, Board::FieldPos &e) const;

public:
  /* Constructs control module from a display and a board */
  Control(Display &d, Board &b);

  /* Main game loop inside */
  void loop();
};

#endif
