//
// Created by Sruti Kamarajugadda on 4/19/20.
//

#include "../resources/player.h"
#include <utility>
#include <iostream>

namespace mylibrary {
Player::Player(std::string name, int lives, int width, int height) : name_{std::move(name)}, lives_{lives} {
    grid_ = new Board(width, height);
}


std::string Player::GetName() {
    return name_;
}


int &Player::GetLives() {
    return lives_;
}


void Player::AddShip(int col, int row) {
    ships_.emplace_back(ship_location_(col, row));
}


int Player::Attacked(int col, int row) {
    if_played_ = true;
    if_location_hit_or_not_ = false;

    try {
        if (col > grid_->GetWidth() || col < 0 || row > grid_->GetHeight() || row < 0) {
            throw std::out_of_range("Out of range");
        }
    }
    catch (const std::out_of_range& oor) {
        std::cerr << "Out of Range error: " << oor.what() << '\n';
        return -1;
    }

    for (int i{0}; i < ships_.size(); i++) {
        if (col == ships_[i].col_ && row == ships_[i].row_) {
            grid_->Hit(col, row);
            ships_[i] = ships_[ships_.size() - 1];
            ships_.pop_back();
            lives_--;
            if_location_hit_or_not_ = true;
            return 1;
        }
    }

    grid_->Miss(col, row);
    if_location_hit_or_not_ = false;
    return 0;
}


const std::vector<Player::ship_location_> &Player::GetShips() const {
    return ships_;
}
}