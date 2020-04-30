//
// Created by Sruti Kamarajugadda on 4/19/20.
//

#include "menu.h"
namespace mylibrary {
Menu::Menu(std::string user_name, int lives, int width, int height) :  user_name(user_name), amountOfLives(lives),
width(width), height(height) {
    user_player_ = new Player(user_name, amountOfLives, width, height);
    computer_player_ = new Player("Computer", amountOfLives, width, height);
}


int Menu::DeterminingWinner() {
    if (user_player_->getShips().size() == 0 && user_player_->if_played) {
        return 0;
    }

    if (computer_player_->getShips().size() == 0 && user_player_->if_played) {
        return 1;
    }
}


int Menu::FindRandomRowOrCol(int num) {
    if (num == 0) {
        num = (rand() % width);
    } else if (num == 1) {
        num = (rand() % height);
    }
    return num;
}


void Menu::PlaceRandomShips(Player *player) {
    for (int i{0}; i < player->GetLives(); i++) {
        int col = rand() % width;
        int row = rand() % height;
        std::cout << "computer chosen col " << col << std::endl;
        std::cout << "computer chosen row " << row << std::endl;
        player->AddShip(col, row);
    }
}


void Menu::PlacePlayerShips(Player *player, int col, int row) {
    player->AddShip(col, row);
}
}

