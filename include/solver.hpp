#pragma once

#include "puzzle_board.hpp"
#include <vector>
#include <unordered_map>
#include <set>

struct PuzzleState {
    PuzzleBoard board;
    int g;  // cost from start
    int h;  // heuristic to goal
    PuzzleBoard parent;
    char move;  // 'U', 'D', 'L', 'R'

    int f() const { return g + h; }

    bool operator<(const PuzzleState& other) const {
        return f() > other.f();  // for min-heap
    }
};

class Solver {
public:
    Solver(int size);

    std::vector<char> solve(const PuzzleBoard& start);

private:
    int size_;
    PuzzleBoard goal_;

    int manhattanDistance(const PuzzleBoard& board) const;
    bool isSolvable(const PuzzleBoard& board) const;
};