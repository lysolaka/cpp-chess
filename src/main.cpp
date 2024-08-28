#include <clocale>

#include "core/board.hpp"
#include "ui/display.hpp"
#include "ui/control.hpp"

int main() {
  std::setlocale(LC_ALL, "C.UTF-8");
  Board b;
  Display d(b);
  Control c(d, b);
  
  c.loop();

  return 0;
}
