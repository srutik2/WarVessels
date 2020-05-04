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

        // Prints board to console
        void Print();

        // Replaces spot on grid with an 'X'
        char Hit(int width, int height);

        // Replaces spot on grid with an 'O'
        char Miss(int width, int height);

        // Returns width_ of board
        int &GetWidth();

        // Returns height_ of board
        int &GetHeight();

    private:
        // Coordinates system info
        int width;
        int height;

        // Max grid info
        const static int MAX_WIDTH = 7;
        const static int MAX_HEIGHT = 7;

        // grid itself
        std::string grid[MAX_WIDTH][MAX_HEIGHT];
    };
}
#endif //FINALPROJECT_BOARD_H
