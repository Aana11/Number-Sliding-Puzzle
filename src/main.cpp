#include "puzzle_board.hpp"
#include "solver.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>

void printBoard(const PuzzleBoard& board) {
    int size = board.getSize();
    const auto& state = board.getState();

    for (int i = 0; i < size; ++i) {
        std::cout << "+";
        for (int j = 0; j < size; ++j) {
            std::cout << "---+";
        }
        std::cout << "\n|";
        for (int j = 0; j < size; ++j) {
            int val = state[i * size + j];
            if (val == 0) {
                std::cout << "   |";
            } else if (val < 10) {
                std::cout << " " << val << " |";
            } else {
                std::cout << val << " |";
            }
        }
        std::cout << "\n";
    }
    std::cout << "+";
    for (int j = 0; j < size; ++j) {
        std::cout << "---+";
    }
    std::cout << "\n";
}

void animateSolution(const PuzzleBoard& start, const std::vector<char>& moves) {
    PuzzleBoard current = start;

    std::cout << "\n=== Initial Board ===\n";
    printBoard(current);

    for (size_t i = 0; i < moves.size(); ++i) {
        std::cout << "\n=== Step " << (i + 1) << ": Move ";
        switch (moves[i]) {
            case 'U': std::cout << "UP"; break;
            case 'D': std::cout << "DOWN"; break;
            case 'L': std::cout << "LEFT"; break;
            case 'R': std::cout << "RIGHT"; break;
        }
        std::cout << " ===\n";

        switch (moves[i]) {
            case 'U': current.moveUp(); break;
            case 'D': current.moveDown(); break;
            case 'L': current.moveLeft(); break;
            case 'R': current.moveRight(); break;
        }

        printBoard(current);
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    std::cout << "\n=== Solved in " << moves.size() << " moves! ===\n";
}

int main() {
    std::cout << "===========================================\n";
    std::cout << "          Sliding Puzzle Solver\n";
    std::cout << "===========================================\n\n";

    int size = 0;
    std::cout << "Enter board size (3 for 3x3, 4 for 4x4): ";
    while (!(std::cin >> size)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Please enter a valid number: ";
    }

    if (size < 3 || size > 5) {
        std::cout << "Size must be between 3 and 5\n";
        return 1;
    }

    std::cout << "\nEnter the puzzle row by row (0 for blank):\n";

    std::vector<int> input;
    int num;
    while ((int)input.size() < size * size && std::cin >> num) {
        input.push_back(num);
    }

    if ((int)input.size() < size * size) {
        std::cout << "Not enough numbers entered.\n";
        return 1;
    }

    PuzzleBoard start(size, input);

    std::cout << "\nYour initial board:\n";
    printBoard(start);

    Solver solver(size);
    std::vector<char> moves = solver.solve(start);

    if (moves.empty()) {
        if (start.isSolved()) {
            std::cout << "\nPuzzle is already solved!\n";
        } else {
            std::cout << "\nSorry, this puzzle is unsolvable.\n";
            std::cout << "Hint: For odd sizes, inversions must be even.\n";
            std::cout << "      For even sizes, (inversions + blank row from bottom) must be odd.\n";
        }
        return 0;
    }

    std::cout << "\nSolving... Optimal solution has " << moves.size() << " moves.\n";
    std::cout << "Press Enter to start animation...";
    std::cin.ignore();
    std::cin.get();

    animateSolution(start, moves);

    std::cout << "\nDone! Press any key to exit...";
    std::cin.get();
    return 0;
}