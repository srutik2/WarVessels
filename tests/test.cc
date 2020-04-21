// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "../src/player.h"

TEST_CASE("Testing Player Class") {
    Player p("Player 1", 5, 5, 5);
    REQUIRE(p.GetName() == "Player 1");
    REQUIRE(p.GetLives() == 5);
    p.GetLives()--;
    REQUIRE(p.GetLives() == 4);
    REQUIRE(p.GetLives() != 5);

    for (int i{0}; i < p.GetLives(); i++) {
        p.AddShip(i, i);
    }

    REQUIRE(p.Attacked(0, 0) == 1);
    REQUIRE(p.Attacked(1, 1) == 1);
    REQUIRE(p.Attacked(-1, 0) == -1);
    REQUIRE(p.Attacked(0, -1) == -1);
    REQUIRE(p.Attacked(10, 0) == -1);
    REQUIRE(p.Attacked(0, 10) == -1);
    REQUIRE(p.Attacked(0, 2) == 0);
    REQUIRE(p.Attacked(2, 0) == 0);

    REQUIRE_NOTHROW(p.PrintBoard());
}

TEST_CASE("Testing Board Class") {
    int width = 3;
    int height = 4;

    Board* board = new Board(width, height);
    REQUIRE(board->GetWidth() == width);
    REQUIRE(board->GetHeight() == height);
    REQUIRE(board->Hit(width,height) == 'X');
    REQUIRE(board->Miss(width,height) == 'O');
}