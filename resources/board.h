//
// Created by Sruti Kamarajugadda on 4/19/20.
//

#ifndef FINALPROJECT_BOARD_H
#define FINALPROJECT_BOARD_H

#include <string>

namespace mylibrary {
    class Board {

    public:
        // Constructor
        Board(int width, int height);

        // Destructor
        ~Board();

        // Replaces spot on grid_ with an 'X'
        char Hit(int width, int height);

        // Replaces spot on grid_ with an 'O'
        char Miss(int width, int height);

        // Returns width_ of board
        int &GetWidth();

        // Returns height_ of board
        int &GetHeight();

    private:
        // Coordinates system info
        int width_;
        int height_;

        // Max grid_ info
        const static int kMaxHeight = 7;
        const static int kMaxWidth = 7;

        // grid_ itself
        std::string grid[kMaxWidth][kMaxHeight];
    };
}
#endif //FINALPROJECT_BOARD_H
