//
// Created by Sruti Kamarajugadda on 4/19/20.
//

#include "board.h"
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


    char Board::Hit(int width, int height) {
        grid[width][height] = "X";
        return 'X';
    }


    char Board::Miss(int width, int height) {
        grid[width][height] = "O";
        return 'O';
    }


    int &Board::GetWidth() {
        return width;
    }


    int &Board::GetHeight() {
        return height;
    }

}
