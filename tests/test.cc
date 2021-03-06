// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../resources/menu.h"
#include "../resources/player.h"


TEST_CASE("Testing Player Class Get Name Function") {
    mylibrary::Player player1("Player 1", 5, 5, 5);
    REQUIRE(player1.GetName() == "Player 1");

    mylibrary::Player player2("Lila", 0, 0, 0);
    REQUIRE(player2.GetName() == "Lila");
}


TEST_CASE("Testing Player Class Get Lives Function") {
    mylibrary::Player player1("Player 1", 5, 5, 5);
    REQUIRE(player1.GetLives() == 5);

    player1.GetLives()--;
    REQUIRE(player1.GetLives() == 4);
    REQUIRE(player1.GetLives() != 5);
}


TEST_CASE("Testing Player Class Attacked Function") {
    mylibrary::Player player1("Player 1", 5, 5, 5);
    for (int i{0}; i < player1.GetLives(); i++) {
        player1.AddShip(i, i);
    }

    REQUIRE(player1.Attacked(0, 0) == 1);
    REQUIRE(player1.Attacked(1, 1) == 1);
    REQUIRE(player1.Attacked(0, -1) == -1);
    REQUIRE(player1.Attacked(10, 0) == -1);
    REQUIRE(player1.Attacked(0, 10) == -1);
    REQUIRE(player1.Attacked(0, 2) == 0);
    REQUIRE(player1.Attacked(2, 0) == 0);

    REQUIRE_NOTHROW(player1.Attacked(10, 10));
}


TEST_CASE("Testing Player Class Get Ships Function") {
    mylibrary::Player player1("Player 1", 5, 5, 5);
    for (int i{0}; i < player1.GetLives(); i++) {
        player1.AddShip(i, i);
    }

    REQUIRE(player1.GetShips().size() == 5);
}


TEST_CASE("Testing Board Get Width and Height Functions") {
    int width_board_one = 3;
    int height_board_one = 4;
    auto* board1 = new mylibrary::Board(width_board_one, height_board_one);
    REQUIRE(board1->GetWidth() == width_board_one);
    REQUIRE(board1->GetHeight() == height_board_one);

    int width_board_two = 5;
    int height_board_two = 6;
    auto* board2 = new mylibrary::Board(width_board_two, height_board_two);
    REQUIRE(board2->GetWidth() == width_board_two);
    REQUIRE(board2->GetHeight() == height_board_two);
}


TEST_CASE("Testing Board Miss Function") {
    int width_board_one = 3;
    int height_board_one = 4;
    int col = 5;
    int row = 5;
    auto* board1 = new mylibrary::Board(width_board_one, height_board_one);
    REQUIRE(board1->Miss(width_board_one,height_board_one) == 'O');
    REQUIRE_NOTHROW(board1->Miss(col, row));
}


TEST_CASE("Testing Board Hit Function") {
    int width_board_one = 3;
    int height_board_one = 4;
    int col = 5;
    int row = 5;
    auto* board1 = new mylibrary::Board(width_board_one, height_board_one);
    REQUIRE(board1->Hit(width_board_one,height_board_one) == 'X');
    REQUIRE_NOTHROW(board1->Hit(col, row));
}


TEST_CASE("Testing Menu Determining Winner Function") {
    int width_ = 4;
    int height_ = 4;
    int lives_ = 3;
    std::string name = "lila";
    bool is_easy_player_strategy = false;
    auto* menu = new mylibrary::Menu(name, lives_, width_, height_, is_easy_player_strategy);
    REQUIRE(menu->DeterminingWinner() == 2);
}


TEST_CASE("Testing Menu Find Random Row or Col Function") {
    int width_ = 4;
    int height_ = 6;
    int lives_ = 3;
    bool is_easy_player_strategy = false;
    std::string name = "lila";
    auto *menu = new mylibrary::Menu(name, lives_, width_, height_, is_easy_player_strategy);

    SECTION("Testing Col") {
        int num = menu->FindRandomRowOrCol(0);
        bool if_num_present = false;
        for (int i = 0; i <= width_; i++) {
            if (i == num) {
                if_num_present = true;
            }
        }
        REQUIRE(if_num_present);
    }

    SECTION("Testing Row") {
        int num = menu->FindRandomRowOrCol(1);
        bool if_num_present = false;
        for (int i = 0; i <= height_; i++) {
            if (i == num) {
                if_num_present = true;
            }
        }
        REQUIRE(if_num_present);
    }
}


TEST_CASE("Testing Menu Placing Random Player Ships Function") {
    int width_ = 4;
    int height_ = 6;
    int lives_ = 3;
    bool is_easy_player_strategy = false;
    std::string name = "lila";
    auto *player1 = new mylibrary::Player(name, lives_, width_, height_);
    auto *menu = new mylibrary::Menu(name, lives_, width_, height_, is_easy_player_strategy);
    menu->PlaceRandomShips(player1);
    REQUIRE(player1->GetShips().size() == 3);
}


TEST_CASE("Testing Menu Placing Player Ships Function") {
    int width_ = 4;
    int height_ = 6;
    int lives_ = 3;
    bool is_easy_player_strategy = false;
    std::string name = "lila";
    auto *player1 = new mylibrary::Player(name, lives_, width_, height_);
    auto *menu = new mylibrary::Menu(name, lives_, width_, height_, is_easy_player_strategy);
    menu->PlacePlayerShips(player1, 3, 3);
    REQUIRE(player1->GetShips().size() == 1);

    REQUIRE_NOTHROW(menu->PlacePlayerShips(player1, 10, 10));

}