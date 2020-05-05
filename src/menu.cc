//
// Created by Sruti Kamarajugadda on 4/19/20.
//

#include "../resources/menu.h"

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
    int col = rand() % width;
    int row = rand() % height;
    temp_points_.emplace_back(col, row); // points vector of x and y
    player->AddShip(col, row);
    std::cout << "computer chosen col :" << col << std::endl;
    std::cout << "computer chosen row :" << row << std::endl;

    if (is_easy_player_strategy) {
        for (int i = 1; i < amountOfLives; i++) {
            int col1 = rand() % width;
            int row1 = rand() % height;
            for (int j = 0; j < temp_points_.size();) {
                if  (temp_points_.at(j).x == col1) {
                    if (temp_points_.at(j).y == row1) {
                        int col2 = rand() % width;
                        int row2 = rand() % height;
                        col1 = col2;
                        row1 = row2;
                        j = 0;
                        continue;
                    }
                }
                j++;
            }
            temp_points_.emplace_back(col1, row1);
            player->AddShip(col1, row1);
            std::cout << "computer chosen col :" << col << std::endl;
            std::cout << "computer chosen row :" << row << std::endl;
        }
    } else if (!is_easy_player_strategy) {
        for (int i{1}; i < player->GetLives(); i++) {
            int col = rand() % width;
            int row = rand() % height;
            std::cout << "computer chosen col :" << col << std::endl;
            std::cout << "computer chosen row :" << row << std::endl;
            player->AddShip(col, row);
        }
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

