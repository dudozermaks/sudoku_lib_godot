#pragma once

#include "../sudoku_lib/sudoku_lib.hpp"
#include "godot_cpp/variant/dictionary.hpp"
#include <godot_cpp/classes/node.hpp>

namespace godot {
class Sudoku : public Node {
  GDCLASS(Sudoku, Node)
private:
  ::Sudoku::Puzzle puzzle;
  ::Sudoku::Puzzle solved_copy;
	::Sudoku::Generator generator;

protected:
  static void _bind_methods();

public:
  Sudoku();
  void load_puzzle(String puzzle);
  bool is_solved();
	bool is_valid();
  void make_solved_copy();
  bool is_right_clue_to_place(godot::Vector2i pos, int clue);
	godot::Dictionary rate();
	godot::String generate();
  ~Sudoku();
};
} // namespace godot
