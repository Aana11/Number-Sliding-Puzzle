#pragma once

#include <vector>
#include <string>

class PuzzleBoard {
public:
    PuzzleBoard(int size);
    PuzzleBoard(int size, const std::vector<int>& board);

    int getSize() const { return size_; }
    const std::vector<int>& getState() const { return state_; }
    int getBlankPos() const { return blankPos_; }

    bool moveUp();
    bool moveDown();
    bool moveLeft();
    bool moveRight();

    bool isSolved() const;
    std::string toString() const;

    bool operator==(const PuzzleBoard& other) const;
    bool operator!=(const PuzzleBoard& other) const;

private:
    int size_;
    std::vector<int> state_;
    int blankPos_;

    bool isValidPos(int row, int col) const;
    int getPos(int row, int col) const;
    void swapBlank(int pos);
};

std::ostream& operator<<(std::ostream& os, const PuzzleBoard& board);