// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include "../resources/menu.h"
#include "cinder/app/App.h"
#include <cinder/gl/texture.h>
#include "ciAnimatedGif.h"
#include "../resources/player.h"
#include "../resources/board.h"

namespace myapp {
class MyApp : public cinder::app::App {
public:
    MyApp();
    //static bool something = true;

private:
    enum class GameState {
        kShooting,
        kPickingShips,
        kUserWinner,
        kComputerWinner,
        KGameNotStarted,
        kClosingScreen
    };

    //  shooting enum signifying whose turn it is when shooting
    enum class Shooting {
        kUserAttacked,
        kComputerAttacked,
        kNoOneAtttacked
    };

    //current shooting state
    Shooting shooting_state_ = Shooting::kNoOneAtttacked;

    //current game state
    GameState state_ = GameState::kPickingShips;

    // background
    cinder::gl::Texture2dRef background;

    cinder::gl::Texture2dRef openingscreen;

    cinder::gl::Texture2dRef winningscreen;

    cinder::gl::Texture2dRef losingscreen;

    cinder::gl::Texture2dRef logo;

    cinder::gl::Texture2dRef ship;

    cinder::gl::Texture2dRef missle;

    cinder::gl::Texture2dRef anchor;
    // winning fid
    cinder::ciAnimatedGifRef gif_winning_screen_;

    cinder::ciAnimatedGifRef gif_losing_screen_;

    // mouse down event
    void mouseDown( cinder::app::MouseEvent event );

    //gathering locations hits of user and computer with pixel locations
    void GatheringYLocationComputer();
    void GatheringXLocationUser(int col);
    void GatheringYLocationUser(int row);
    void GatheringXLocationComputer();

    void PrintImage(const cinder::gl::Texture2dRef &texture, const cinder::ivec2& size, const cinder::vec2& loc);

    // drew based in which game state or shooting state the game is in
    void DrawPickingShips();
    void DrawShootingInstructions();
    void DrawWinningScreen();
    void DrawHitOrMissComputer(char c);
    void DrawBoard();
    void DrawComputerBoard();
    void DrawUserBoard();
    void DrawHitOrMissUser(char character);
    void DrawChosenShips();
    void DrawLosingScreen();

    // cinder already implemented methods
    void setup() override;
    void update() override;
    void draw() override;
    void keyDown(cinder::app::KeyEvent) override;

    // general const variables identified through gflags in run
    const std::string user_name_;
    const int amount_of_lives_;
    const int width_;
    const int height_;


    // location of computer/ user x, y location needed in shooting and ship placement game state
    int user_x;
    int user_y;
    int computer_x;
    int computer_y;
    int x;
    int y;
    int mouse_x_;
    int mouse_y_;

    // the location for each x y in the background grid we laid out
    int general_location_x_computer_;
    int general_location_x_user_;
    int general_location_y_user_;
    int general_location_y_computer_;

    // boolean to ensure that the program is waiting on user and the order of events is correct
    bool is_computer_turn_;
    bool is_computer_attacked_;
    bool is_user_attacked_;
    bool has_someone_won;
    bool is_easy_player_strategy_;

    // x  or o for computer/ user
    char hit_or_not_computer_;
    char hit_or_not_user_;

    struct location {
        location(int x, int y) : x{x}, y{y} {};

        int x;
        int y;
    };

    // point strut with x y location and a character
    struct Points {
        Points(int x, int y, std::string s) : x{x}, y{y}, s{s} {};

        int x;
        int y;
        std::string s;
    };

    std::vector<location> locations;

    // vector of points
    std::vector<Points> points;

    // calling game_engine in My:App constructor
    mylibrary::Menu game_engine_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
