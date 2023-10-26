#include "sudoku.hpp"
#include "../sudoku_lib/sudoku_lib.hpp"
#include "godot_cpp/variant/array.hpp"
#include "godot_cpp/variant/dictionary.hpp"
#include "godot_cpp/variant/vector2.hpp"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <random>
#include <vector>

namespace godot {
void Sudoku::_bind_methods() {
  ClassDB::bind_method(D_METHOD("load_puzzle", "puzzle"), &Sudoku::load_puzzle);
  ClassDB::bind_method(D_METHOD("is_solved"), &Sudoku::is_solved);
  ClassDB::bind_method(D_METHOD("is_valid"), &Sudoku::is_valid);
  ClassDB::bind_method(D_METHOD("make_solved_copy"), &Sudoku::make_solved_copy);
  ClassDB::bind_method(D_METHOD("is_right_clue_to_place", "pos", "clue"),
                       &Sudoku::is_right_clue_to_place);
  ClassDB::bind_method(D_METHOD("rate"), &Sudoku::rate);
  ClassDB::bind_method(D_METHOD("generate"), &Sudoku::generate);
}

void Sudoku::load_puzzle(String puzzle) {
  this->puzzle.load(puzzle.utf8().get_data());
}

bool Sudoku::is_valid(){
	::Sudoku::TdokuLib tdoku{puzzle};
	return tdoku.has_unique_solution();
}

void Sudoku::make_solved_copy() {
  ::Sudoku::TdokuLib tdoku{puzzle};
  solved_copy = tdoku.solve();
}

bool Sudoku::is_right_clue_to_place(godot::Vector2i pos, int clue) {
  return solved_copy.get_clues()[::Sudoku::Pos{pos.x, pos.y}] == clue;
}

bool Sudoku::is_solved() { return puzzle.is_solved(); }

godot::Dictionary Sudoku::rate(){
	::Sudoku::HumanSolver hs{puzzle};
	::Sudoku::HumanSolver::Result hs_result = hs.solve();

	godot::Dictionary dict_result;

	dict_result["score"] = hs_result.score;
	std::cout << hs_result.is_solved << std::endl;
	dict_result["is_solved"] = hs_result.is_solved;
	::godot::Array used_methods{};
	for (std::string used_mehtod : hs_result.used_methods){
		used_methods.push_back(used_mehtod.data());
	}
	dict_result["used_methods"] = used_methods;

	return dict_result;
}

godot::String Sudoku::generate(){
	return generator.generate().clues_as_string().data();
}

Sudoku::Sudoku() {
	generator.set_seed(std::random_device{}());
}
Sudoku::~Sudoku() {}
} // namespace godot
