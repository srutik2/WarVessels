//
// Created by Sruti Kamarajugadda on 4/19/20.
//

#include "menu.h"

namespace mylibrary {
Menu::Menu(std::string user_name, int lives, int width, int height, bool is_easy_player_strategy) :  user_name(user_name), amountOfLives(lives),
width(width), height(height), is_easy_player_strategy(is_easy_player_strategy) {
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
    return 2;
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
        int col1 = rand() % width;
        int row1 = rand() % height;
        if (is_easy_player_strategy) {
            mylibrary::Player::Ship *ship = new Player::Ship(col1, row1);
            for (int i = 0; i < player->getShips().size(); i++) {
                if (ship->col == player->getShips().at(i).col) {
                    if (ship->row == player->getShips().at(i).row) {
                        int col2 = rand() % width;
                        int row2 = rand() % height;
                        mylibrary::Player::Ship *ship2 = new Player::Ship(col2, row2);
                        if (ship2->col == player->getShips().at(i).col) {
                            if (ship2->row == player->getShips().at(i).row) {
                                int col3 = rand() % width;
                                int row3 = rand() % height;
                                player->AddShip(col3, row3);
                                std::cout << "computer chosen col " << col3 << std::endl;
                                std::cout << "computer chosen row " << row3 << std::endl;
                                return;
                            }
                        }
                        player->AddShip(col2, row2);
                        std::cout << "computer chosen col " << col2 << std::endl;
                        std::cout << "computer chosen row " << row2 << std::endl;
                        return;
                    }
                }
            }
        }
        std::cout << "computer chosen col " << col1 << std::endl;
        std::cout << "computer chosen row " << row1 << std::endl;
        player->AddShip(col1, row1);
        return;
    }
}


void Menu::PlacePlayerShips(Player *player, int col, int row) {
    try {
        if (col > width || col < 0 || row > height || row < 0) {
            throw std::out_of_range("Out of range");
        }
    }
    catch (const std::out_of_range& oor) {
        std::cerr << "Out of Range error: " << oor.what() << '\n';
    }
    player->AddShip(col, row);
}
}

