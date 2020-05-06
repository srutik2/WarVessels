//
// Created by Sruti Kamarajugadda on 4/19/20.
//

#ifndef FINALPROJECT_MENU_H
#define FINALPROJECT_MENU_H

#include "player.h"
#include "menu.h"
#include <iostream>
#include "board.h"
#include <algorithm>
#include <chrono>
#include <string>

namespace mylibrary {
    class Menu {

    public:
        // Constructor
        Menu(std::string, int lives, int width, int height, bool is_easy_player_strategy);

        // Players for the game
        Player *user_player_;
        Player *computer_player_;

        //determines if user or computer won
        int DeterminingWinner();

        // puts ships_ on the computers board
        void PlaceRandomShips(Player *player);

        //user inputs where the ships_ reside
        void PlacePlayerShips(Player *player, int col, int row);

        //where the random computer ships_ are
        int FindRandomRowOrCol(int num);

    private:
        //struct of character_and_location_points_ a ship_ can be located
        struct location_ {
            location_(int x_, int y_) : x_{x_}, y_{y_} {};

            int x_;
            int y_;
        };

        //variables identified with each player object
        std::string user_name_;
        int width_;
        int height_;
        int amount_of_lives_;
        bool is_easy_player_strategy_;

        //vector needed for the easy player strategy to prevent ship_ stacking for the user
        std::vector<location_> temp_points_;
    };
}

#endif //FINALPROJECT_MENU_H
