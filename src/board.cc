//
// Created by Sruti Kamarajugadda on 4/19/20.
//

#include "/Users/srutikamarajugadda/Desktop/cinder/myproj/final-project-srutik2/src/board.h"
#include <iostream>

namespace mylibrary {
Board::Board(int width, int height) : width{width}, height{height} {
    for (int col{0}; col < width; col++) {
        for (int row{0}; row < height; row++) {
            grid[col][row] = "~";
        }
    }
}


Board::~Board() {}


void Board::Print() {
    std::cout << " ";
    for (int numbering{0}; numbering < width; numbering++) {
        std::cout << numbering << " ";
    }
    std::cout << std::endl;
    for (int row{0}; row < height; row++) {
        std::cout << row << " ";
        for (int col{0}; col < width; col++) {
            std::cout << grid[col][row] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


char Board::Hit(int col, int row) {
    try {
        if (col > width || col < 0 || row > height || row < 0) {
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
        if (col > width || col < 0 || row > height || row < 0) {
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
    return width;
}


int &Board::GetHeight() {
    return height;
}
}
