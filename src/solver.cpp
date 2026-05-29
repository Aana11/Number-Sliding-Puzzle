#include "solver.hpp"
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <map>

struct Node {
    PuzzleBoard board;
    int g;
    int h;
    char move;
    Node* parent;
};

struct NodeCompare {
    bool operator()(Node* a, Node* b) const {
        return (a->g + a->h) > (b->g + b->h);
    }
};

Solver::Solver(int size) : size_(size), goal_(size) {
}

int Solver::manhattanDistance(const PuzzleBoard& board) const {
    int distance = 0;
    const auto& state = board.getState();
    for (int pos = 0; pos < size_ * size_; ++pos) {
        int val = state[pos];
        if (val == 0) continue;
        int targetPos = val - 1;
        int row = pos / size_;
        int col = pos % size_;
        int targetRow = targetPos / size_;
        int targetCol = targetPos % size_;
        distance += std::abs(row - targetRow) + std::abs(col - targetCol);
    }
    return distance;
}

bool Solver::isSolvable(const PuzzleBoard& board) const {
    const auto& state = board.getState();
    int inversions = 0;
    for (int i = 0; i < state.size(); ++i) {
        for (int j = i + 1; j < state.size(); ++j) {
            if (state[i] == 0 || state[j] == 0) continue;
            if (state[i] > state[j]) ++inversions;
        }
    }

    if (size_ % 2 == 1) {
        return inversions % 2 == 0;
    } else {
        int blankRow = size_ - 1 - (board.getBlankPos() / size_);
        return (inversions + blankRow) % 2 == 1;
    }
}

std::vector<char> Solver::solve(const PuzzleBoard& start) {
    if (!isSolvable(start)) {
        return {};
    }

    if (start.isSolved()) {
        return {};
    }

    std::priority_queue<Node*, std::vector<Node*>, NodeCompare> open;
    std::unordered_map<std::string, Node*> allNodes;
    std::unordered_set<std::string> closed;

    Node* root = new Node{start, 0, manhattanDistance(start), 0, nullptr};
    open.push(root);
    allNodes[start.toString()] = root;

    std::vector<char> moves = {'U', 'D', 'L', 'R'};
    std::vector<char> opposite = {'D', 'U', 'R', 'L'};

    Node* resultNode = nullptr;

    while (!open.empty()) {
        Node* current = open.top();
        open.pop();

        std::string key = current->board.toString();
        if (closed.count(key)) continue;
        closed.insert(key);

        if (current->board.isSolved()) {
            resultNode = current;
            break;
        }

        for (int i = 0; i < 4; ++i) {
            if (current->parent != nullptr && moves[i] == opposite[i]) continue;

            PuzzleBoard nextBoard = current->board;
            bool moved = false;
            switch (moves[i]) {
                case 'U': moved = nextBoard.moveUp(); break;
                case 'D': moved = nextBoard.moveDown(); break;
                case 'L': moved = nextBoard.moveLeft(); break;
                case 'R': moved = nextBoard.moveRight(); break;
            }

            if (!moved) continue;

            std::string nextKey = nextBoard.toString();
            if (closed.count(nextKey)) continue;

            auto it = allNodes.find(nextKey);
            if (it != allNodes.end()) {
                if (it->second->g > current->g + 1) {
                    it->second->g = current->g + 1;
                    it->second->parent = current;
                    it->second->move = moves[i];
                    open.push(it->second);
                }
                continue;
            }

            int g = current->g + 1;
            int h = manhattanDistance(nextBoard);
            Node* next = new Node{nextBoard, g, h, moves[i], current};
            open.push(next);
            allNodes[nextKey] = next;
        }
    }

    std::vector<char> path;
    if (resultNode != nullptr) {
        Node* node = resultNode;
        while (node->parent != nullptr) {
            path.push_back(node->move);
            node = node->parent;
        }
        std::reverse(path.begin(), path.end());
    }

    for (auto& p : allNodes) {
        delete p.second;
    }

    return path;
}