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
        //bool for if a certain ship_ was hit
        bool if_location_hit_or_not_;

        //bool for if the user had played
        bool if_played_ = false;

        // Constructor
        Player(std::string name, int lives, int width, int height);

        // Returns name_ of the player
        std::string GetName();

        // Returns number of players lives_
        int &GetLives();

        // Adds a ship_ to the vector
        void AddShip(int col, int row);

        // Player when board gets attacked
        // Returns: -1 = out of bounds, 0 = miss, 1 = hit
        int Attacked(int col, int row);

        // ship_location_ object to hold it's board position
        struct ship_location_ {
            ship_location_(int col_, int row_) : col_{col_}, row_{row_} {};
            int col_;
            int row_;
        };

        // get ships_ vector
        const std::vector<ship_location_> &GetShips() const;

    private:
        // Players name_
        std::string name_;

        // Players remaining lives_
        int lives_;

        // Players personal board
        Board* grid_;

        // Vector of all ships_ this player has
        std::vector<ship_location_> ships_;
    };
}

#endif //FINALPROJECT_PLAYER_H
