// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include "../resources/menu.h"
#include "cinder/app/App.h"
#include <cinder/gl/texture.h>

#include <utility>
#include "ciAnimatedGif.h"
#include "../resources/player.h"
#include "../resources/board.h"

namespace myapp {
class MyApp : public cinder::app::App {
public:
    //constructor
    MyApp();

private:
    //game state enum
    enum class GameState {
        kShooting,
        kPickingShips,
        kUserWinner,
        kComputerWinner,
        KGameNotStarted,
    };

    // shooting enum signifying whose turn it is when shooting
    enum class Shooting {
        kUserAttacked,
        kComputerAttacked,
        kNoOneAtttacked
    };

    //current shooting state
    Shooting shooting_state_ = Shooting::kNoOneAtttacked;

    //current game state
    GameState state_ = GameState::kPickingShips;

    // textures of images used throughout the game at specific character_and_location_points_
    cinder::gl::Texture2dRef background_;
    cinder::gl::Texture2dRef opening_screen_;
    cinder::gl::Texture2dRef winning_screen_;
    cinder::gl::Texture2dRef losing_screen_;
    cinder::gl::Texture2dRef logo_;
    cinder::gl::Texture2dRef ship_;
    cinder::gl::Texture2dRef missile_;
    cinder::gl::Texture2dRef anchor_;
    cinder::ciAnimatedGifRef gif_winning_screen_;
    cinder::ciAnimatedGifRef gif_losing_screen_;

    //gathering graphics anchor_ locations hits of user and computer with pixel graphics anchor_ locations
    void GatheringYLocationComputer();
    void GatheringXLocationUser(int col);
    void GatheringYLocationUser(int row);
    void GatheringXLocationComputer();

    // draws based on which game state or shooting state the game is in
    void DrawPickingShips();
    void DrawShootingInstructions();
    void DrawWinningScreen();
    void DrawHitOrMissComputer(char c);
    void DrawBoard();
    void DrawComputerBoard();
    void DrawUserBoard();
    void DrawHitOrMissUser(char c);
    void DrawChosenShips();
    void DrawLosingScreen();
    //Prints image at a specific location_
    void PrintImage(const cinder::gl::Texture2dRef &texture, const cinder::ivec2& size, const cinder::vec2& loc);

    // cinder already implemented methods
    void setup() override;
    void update() override;
    void draw() override;
    void keyDown(cinder::app::KeyEvent) override;
    // mouse down event
    void mouseDown( cinder::app::MouseEvent event) override;

    // general const variables identified through gflags in run
    const std::string user_name_;
    const int amount_of_lives_;
    const int width_;
    const int height_;
    bool is_easy_player_strategy_;


    // location_ of computer/ user x_, y_ location_ needed in shooting and ship_ placement game state
    int user_x_;
    int user_y_;
    int computer_x_;
    int computer_y_;
    int mouse_x_;
    int mouse_y_;

    // the location_ for each x_, y_ in the background_ grid_ we laid out
    int general_location_x_computer_;
    int general_location_x_user_;
    int general_location_y_user_;
    int general_location_y_computer_;

    // booleans to ensure that the program is waiting on user and the order of events is correct
    bool is_computer_turn_;
    bool is_computer_attacked_;
    bool is_user_attacked_;
    bool has_someone_won_;

    // X for hit or O for miss for computer/user
    char hit_or_not_computer_;
    char hit_or_not_user_;
    const char x = 'X';
    const char o = 'O';

    //struct with only x_ and y_ location_
    struct location_ {
        location_(int x_, int y_) : x_{x_}, y_{y_} {};

        int x_;
        int y_;
    };

    // character and location_ strut with x_ y_ location_ and a character
    struct character_and_location_ {
        character_and_location_(int x_, int y_, std::string s_) : x_{x_}, y_{y_}, s_{std::move(s_)} {};

        int x_;
        int y_;
        std::string s_;
    };

    //vector of where all the graphics anchors are
    std::vector<location_> graphics_anchor_locations_;

    //vector of where all the shots were on the graphics screen
    std::vector<character_and_location_> character_and_location_points_;

    // calling game_engine in My:App constructor
    mylibrary::Menu game_engine_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
