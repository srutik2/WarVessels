//
// Created by Sruti Kamarajugadda on 4/19/20.
//

#include "board.h"
#include <iostream>
#include "board.h"

// Constructor
Board::Board(int width, int height) : width{width}, height{height} {
    for (int i{0}; i < width; i++) {
        for (int j{0}; j < height; j++) {
            grid[i][j] = "~";
        }
    }
}

// Destructor
Board::~Board() {

}

// Prints board to console
void Board::Print() {
    std::cout << " ";
    for (int i{0}; i < width; i++) {
        std::cout << i << " ";
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

// Replaces spot on grid with an 'X'
void Board::Hit(int width, int height) {
    grid[width][height] = "X";
}

// Replaces spot on grid with an 'O'
void Board::Miss(int width, int height) {
    grid[width][height] = "O";
}

// Returns width of board
int &Board::getWidth() {
    return width;
}

// Returns height of board
int &Board::getHeight() {
    return height;
}
