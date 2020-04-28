//
// Created by Sruti Kamarajugadda on 4/19/20.
//

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H


#include <string>
#include <vector>
#include "board.h"
namespace mylibrary {
    class Player {
    public:
        // Constructor
        Player(std::string name, int lives, int width, int height);

        // Destructor
        ~Player();

        // Returns name of the player
        std::string GetName();

        // Returns number of players lives
        int &GetLives();

        // Adds a ship to the vector
        void AddShip(int col, int row);

        // Player gets "board attacked"
        // Returns: -1 = out of bounds, 0 = miss, 1 = hit
        int Attacked(int col, int row);

        // Prints board for current player
        void PrintBoard();

        std::string printing_string_;

    private:
        // Players name
        std::string name;

        // Players remaining lives
        int lives;

        // Players personal board
        Board *grid;

    public:
        // Ship object to hold it's board position
        struct Ship {
            Ship(int col, int row) : col{col}, row{row} {};
            int col;
            int row;
        };

        // Vector of all ships this player has
        std::vector<Ship> ships;

        const std::vector<Ship> &getShips() const;

    };
}

#endif //FINALPROJECT_PLAYER_H
