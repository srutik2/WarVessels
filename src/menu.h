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
using std::string;
//change to string
const char kNormalFont[] = "Papyrus";

namespace mylibrary {
    class Menu {
    public:
        // Constructor
        Menu(std::string, int lives, int width, int height, bool is_easy_player_strategy);

        // Destructor
        //~Menu();

        std::string user_name;

        // Players for the game
        Player *user_player_;
        Player *computer_player_;

        //determines if user or computer won
        int DeterminingWinner();

        // Puts ships on the computers board for each live they have
        void PlaceRandomShips(Player *player);

        //user inputs where the ships reside
        void PlacePlayerShips(Player *player, int col, int row);

        //where the random computer ships are
        int FindRandomRowOrCol(int num);

    private:
        int width;
        int height;
        int amountOfLives;
        bool is_easy_player_strategy;


        //struct of points
        struct Points {
            Points(int x, int y) : x{x}, y{y} {};

            int x;
            int y;
        };

    };
}

#endif //FINALPROJECT_MENU_H
