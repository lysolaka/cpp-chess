#include "piece.hpp"

/* Constructs empty piece with no side assigned */
Piece::Piece() : type(EMPTY), side(NONE), moved(false) {}
/* Constructs piece with type `t` and side `s` */
Piece::Piece(Type t, Side s) : type(t), side(s), moved(false) {}

/* Returns the type of the piece */
Piece::Type Piece::get_type() const { return type; }
/* Changes the type of the piece to queen */
void Piece::change_type() { type = QUEEN; }

/* Returns the side of the piece */
Piece::Side Piece::get_side() const { return side; }

/* Returns whether the piece was moved */
bool Piece::has_moved() const { return moved; }
/* Marks the piece as moved */
void Piece::mark_moved() { moved = true; }
