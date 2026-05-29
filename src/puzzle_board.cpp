#include "puzzle_board.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

PuzzleBoard::PuzzleBoard(int size) : size_(size), state_(size * size), blankPos_(0) {
    for (int i = 0; i < size * size - 1; ++i) {
        state_[i] = i + 1;
    }
    state_[size * size - 1] = 0;
    blankPos_ = size * size - 1;
}

PuzzleBoard::PuzzleBoard(int size, const std::vector<int>& board)
    : size_(size), state_(board), blankPos_(0) {
    for (int i = 0; i < board.size(); ++i) {
        if (board[i] == 0) {
            blankPos_ = i;
            break;
        }
    }
}

bool PuzzleBoard::isValidPos(int row, int col) const {
    return row >= 0 && row < size_ && col >= 0 && col < size_;
}

int PuzzleBoard::getPos(int row, int col) const {
    return row * size_ + col;
}

void PuzzleBoard::swapBlank(int pos) {
    std::swap(state_[blankPos_], state_[pos]);
    blankPos_ = pos;
}

bool PuzzleBoard::moveUp() {
    int row = blankPos_ / size_;
    if (row == 0) return false;
    swapBlank(getPos(row - 1, blankPos_ % size_));
    return true;
}

bool PuzzleBoard::moveDown() {
    int row = blankPos_ / size_;
    if (row == size_ - 1) return false;
    swapBlank(getPos(row + 1, blankPos_ % size_));
    return true;
}

bool PuzzleBoard::moveLeft() {
    int col = blankPos_ % size_;
    if (col == 0) return false;
    swapBlank(getPos(blankPos_ / size_, col - 1));
    return true;
}

bool PuzzleBoard::moveRight() {
    int col = blankPos_ % size_;
    if (col == size_ - 1) return false;
    swapBlank(getPos(blankPos_ / size_, col + 1));
    return true;
}

bool PuzzleBoard::isSolved() const {
    for (int i = 0; i < size_ * size_ - 1; ++i) {
        if (state_[i] != i + 1) return false;
    }
    return state_[size_ * size_ - 1] == 0;
}

std::string PuzzleBoard::toString() const {
    std::ostringstream oss;
    for (int i = 0; i < size_; ++i) {
        for (int j = 0; j < size_; ++j) {
            int val = state_[getPos(i, j)];
            if (val == 0) {
                oss << "    ";
            } else {
                oss << "  " << val << " ";
            }
        }
        oss << "\n";
    }
    return oss.str();
}

bool PuzzleBoard::operator==(const PuzzleBoard& other) const {
    return size_ == other.size_ && state_ == other.state_;
}

bool PuzzleBoard::operator!=(const PuzzleBoard& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const PuzzleBoard& board) {
    int size = board.getSize();
    for (int i = 0; i < size; ++i) {
        os << "+";
        for (int j = 0; j < size; ++j) {
            os << "---+";
        }
        os << "\n|";
        for (int j = 0; j < size; ++j) {
            int val = board.getState()[i * size + j];
            if (val == 0) {
                os << "   |";
            } else {
                os << " " << val << " |";
            }
        }
        os << "\n";
    }
    os << "+";
    for (int j = 0; j < size; ++j) {
        os << "---+";
    }
    os << "\n";
    return os;
}