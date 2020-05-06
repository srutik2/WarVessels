//
// Created by Sruti Kamarajugadda on 4/19/20.
//

#include "../resources/menu.h"

namespace mylibrary {
Menu::Menu(std::string user_name, int lives, int width, int height, bool is_easy_player_strategy) :
user_name_(user_name), amount_of_lives_(lives),
width_(width), height_(height), is_easy_player_strategy_(is_easy_player_strategy) {

    user_player_ = new Player(user_name, amount_of_lives_, width, height);
    computer_player_ = new Player("Computer", amount_of_lives_, width, height);
}


int Menu::DeterminingWinner() {
    if (user_player_->GetShips().size() == 0 && user_player_->if_played_) {
        return 0;
    }

    if (computer_player_->GetShips().size() == 0 && user_player_->if_played_) {
        return 1;
    }
    return 2;
}


int Menu::FindRandomRowOrCol(int num) {
    if (num == 0) {
        num = (rand() % width_);
    } else if (num == 1) {
        num = (rand() % height_);
    }
    return num;
}


void Menu::PlaceRandomShips(Player *player) {
    int col = rand() % width_;
    int row = rand() % height_;
    temp_points_.emplace_back(col, row); // character_and_location_points_ vector of x_ and y_
    player->AddShip(col, row);
    std::cout << "computer chosen col_ :" << col << std::endl;
    std::cout << "computer chosen row_ :" << row << std::endl;

    if (is_easy_player_strategy_) {
        for (int i = 1; i < amount_of_lives_; i++) {
            int col1 = rand() % width_;
            int row1 = rand() % height_;
            for (int j = 0; j < temp_points_.size();) {
                if  (temp_points_.at(j).x_ == col1) {
                    if (temp_points_.at(j).y_ == row1) {
                        int col2 = rand() % width_;
                        int row2 = rand() % height_;

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
            std::cout << "computer chosen col_ :" << col1 << std::endl;
            std::cout << "computer chosen row_ :" << row1 << std::endl;
        }
    } else if (!is_easy_player_strategy_) {
        for (int i{1}; i < player->GetLives(); i++) {
            int col = rand() % width_;
            int row = rand() % height_;

            std::cout << "computer chosen col_ :" << col << std::endl;
            std::cout << "computer chosen row_ :" << row << std::endl;
            player->AddShip(col, row);
        }
    }
}


void Menu::PlacePlayerShips(Player *player, int col, int row) {
    try {
        if (col > width_ || col < 0 || row > height_ || row < 0) {
            throw std::out_of_range("Out of range");
        }
    }
    catch (const std::out_of_range& oor) {
        std::cerr << "Out of Range error: " << oor.what() << '\n';
    }

    player->AddShip(col, row);
}
}

