# Sliding Puzzle Solver

A C++ implementation of a sliding puzzle (N-puzzle) solver using the A* algorithm.


## Usage

1. Enter board size (3 for 3x3, 4 for 4x4, 5 for 5x5)
2. Enter the puzzle numbers row by row, separated by spaces
3. After entering all rows, the solver starts automatically

Example for 3x3:
```
3
1 2 3
4 5 6
7 8 0
```

## Algorithm

### A* Search

The solver uses the **A\*** algorithm with **Manhattan distance** as the heuristic function.

```
f(n) = g(n) + h(n)
```

- `g(n)`: Cost from start state to current state (number of moves)
- `h(n)`: Estimated cost from current state to goal (Manhattan distance)

### Manhattan Distance

For each tile (except the blank), calculate the distance from its current position to its goal position:

```
h = sum(|current_row - goal_row| + |current_col - goal_col|) for all tiles
```

### Solvability Check

A puzzle is solvable if:

- **Odd size board** (3x3, 5x5): Number of inversions must be even
- **Even size board** (4x4): `(inversions + blank_row_from_bottom) % 2 == 1`

**Inversion**: A pair (a, b) where a appears before b but a > b.

### State Space

- State representation: Flat vector of integers (0 = blank)
- Successor function: Swap blank with adjacent tile (up/down/left/right)
- Goal state: `{1, 2, 3, ..., n-1, 0}`

### Data Structures

- **Open list**: Priority queue ordered by f(n) = g(n) + h(n)
- **Closed set**: Hash set of visited states (using board string as key)
- **Node**: Contains board state, g cost, h cost, parent pointer, move made

## Project Structure

```
shuzi/
├── CMakeLists.txt
├── include/
│   ├── puzzle_board.hpp   # Board representation & moves
│   └── solver.hpp         # A* solver
├── src/
│   ├── main.cpp           # CLI interface
│   ├── puzzle_board.cpp
│   └── solver.cpp
└── build/
    └── shuzi.exe
```

## Key Functions

### PuzzleBoard
- `moveUp/Down/Left/Right()`: Move the blank tile
- `isSolved()`: Check if puzzle is in goal state
- `toString()`: Generate unique state key for hashing

### Solver
- `manhattanDistance()`: Calculate heuristic
- `isSolvable()`: Verify puzzle can be solved
- `solve()`: A* search implementation