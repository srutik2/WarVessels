//
// Created by Sruti Kamarajugadda on 4/19/20.
//

#include "../resources/board.h"
#include <iostream>

namespace mylibrary {
Board::Board(int width_, int height_) : width_{width_}, height_{height_} {
    for (int col{0}; col < width_; col++) {
        for (int row{0}; row < height_; row++) {
            grid[col][row] = "~";
        }
    }
}


Board::~Board() {}


char Board::Hit(int col, int row) {
    try {
        if (col > width_ || col < 0 || row > height_ || row < 0) {
            throw std::out_of_range("Out of range");
        }
    }
    catch (const std::out_of_range& oor) {
        std::cerr << "Out of Range error: " << oor.what() << '\n';
    }

    grid[col][row] = "X";
    return 'X';
}


char Board::Miss(int col, int row) {
    try {
        if (col > width_ || col < 0 || row > height_ || row < 0) {
            throw std::out_of_range("Out of range");
        }
    }
    catch (const std::out_of_range& oor) {
        std::cerr << "Out of Range error: " << oor.what() << '\n';
    }

    grid[col][row] = "O";
    return 'O';
}


int &Board::GetWidth() {
    return width_;
}


int &Board::GetHeight() {
    return height_;
}
}
