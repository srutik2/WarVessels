// Copyright (c) 2020 [Sruti Kamarajugadda]. All rights reserved.

#include "my_app.h"
#include <cinder/app/App.h>
#include <cinder/Text.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <cinder/Font.h>
#include <cinder/Vector.h>
#include <algorithm>
#include <chrono>
#include <string>
#include <gflags/gflags.h>
#include <cinder/gl/texture.h>

DECLARE_string(player_name);
DECLARE_int32(width);
DECLARE_int32(height);
DECLARE_int32(amount_of_lives);
DECLARE_bool(is_easy_player_strategy);

namespace myapp {
using cinder::app::KeyEvent;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::app::KeyEvent;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;
using std::string;
using cinder::TextBox;
const std::string kNormalFont = "Papyrus";

MyApp::MyApp() :
        width_(FLAGS_width),
        height_(FLAGS_height),
        user_name_(FLAGS_player_name),
        amount_of_lives_(FLAGS_amount_of_lives),
        game_engine_ {FLAGS_player_name, FLAGS_amount_of_lives, FLAGS_width, FLAGS_height,
                      FLAGS_is_easy_player_strategy},
        state_{GameState::KGameNotStarted},
        is_computer_turn_{false},
        has_someone_won_{false},
        general_location_x_user_{0},
        general_location_y_user_{0},
        general_location_x_computer_{0},
        general_location_y_computer_{0},
        is_computer_attacked_{false},
        is_user_attacked_{false},
        shooting_state_{Shooting::kNoOneAtttacked},
        hit_or_not_computer_{'A'},
        hit_or_not_user_{'B'},
        is_easy_player_strategy_{FLAGS_is_easy_player_strategy} { }

void MyApp::setup() {
    background_ = cinder::gl::Texture2d::create(loadImage(
            loadAsset("dark_ocean_background_.jpg")));
    opening_screen_ = cinder::gl::Texture2d::create(loadImage(loadAsset(
            "opening_screen_.png")));
    gif_winning_screen_ = cinder::ciAnimatedGif::create(loadAsset("winning_.gif"));
    ship_ = cinder::gl::Texture2d::create(loadImage(loadAsset("ship_.png")));
    missile_ = cinder::gl::Texture2d::create(loadImage(loadAsset("missle_.png")));
    winning_screen_ = cinder::gl::Texture2d::create(loadImage(loadAsset(
            "winning_screen_.jpg")));
    anchor_ = cinder::gl::Texture2d::create(loadImage(loadAsset("anchor_.png")));
    losing_screen_ = cinder::gl::Texture2d::create(loadImage(loadAsset(
            "losing_screen_.png")));
    gif_losing_screen_ = cinder::ciAnimatedGif::create(loadAsset("losing_.gif"));
    logo_ = cinder::gl::Texture2d::create(loadImage(loadAsset("logo_.png")));
}


void MyApp::update() {
     if (game_engine_.DeterminingWinner() == 0) {
         state_ = GameState::kComputerWinner;
     }

    if (game_engine_.DeterminingWinner() == 1) {
        state_ = GameState::kUserWinner;
    }

    if (state_ == GameState::kPickingShips) {
        if (game_engine_.user_player_->GetShips().size() == amount_of_lives_) {
            game_engine_.PlaceRandomShips(game_engine_.computer_player_);
        }
        if (game_engine_.computer_player_->GetShips().size() == amount_of_lives_ &&
                game_engine_.user_player_->GetShips().size() == amount_of_lives_) {
            state_ = GameState::kShooting;
        }
    }

     if (state_ == GameState::kShooting) {
         if (is_computer_turn_) {
             draw();
             int computer_shot_col = game_engine_.FindRandomRowOrCol(0);
             int computer_shot_row = game_engine_.FindRandomRowOrCol(1);

             hit_or_not_computer_ = false;
             game_engine_.user_player_->Attacked(computer_shot_col, computer_shot_row);
             shooting_state_ = Shooting::kUserAttacked;

             if (game_engine_.user_player_->if_location_hit_or_not_) {
                 hit_or_not_computer_ = x;
             }

             if (!game_engine_.user_player_->if_location_hit_or_not_) {
                 hit_or_not_computer_ = o;
             }

             std::cout << "computer x_ shot: " << computer_shot_col << std::endl;
             GatheringXLocationUser(computer_shot_col);
             std::cout << "computer  y_ shot: " << computer_shot_row << std::endl;
             GatheringYLocationUser(computer_shot_row);
             is_computer_turn_ = false;
         }
     }
}


void MyApp::draw() {
    const cinder::ivec2 size = {500, 50};
     cinder::gl::color(Color::white());
     cinder::gl::draw(background_, getWindowBounds());
     DrawBoard();
     PrintImage(logo_, size, {cinder::app::getWindowWidth() / 2 + 305,
                              cinder::app::getWindowHeight() / 2 - 310});

     if (state_ == GameState::KGameNotStarted) {
         cinder::gl::draw(opening_screen_, getWindowBounds());
     }

     if (state_ == GameState::kPickingShips) {
        for (int ship_placement_count = 0; ship_placement_count < game_engine_.user_player_->GetLives();
        ship_placement_count++) {
            DrawPickingShips();
            DrawChosenShips();
        }
    }

    if (state_ == GameState::kShooting) {
        DrawShootingInstructions();
        if (shooting_state_ == Shooting::kComputerAttacked) {
            DrawHitOrMissComputer(hit_or_not_user_);
        }

        if (shooting_state_ == Shooting::kUserAttacked) {
            DrawHitOrMissUser(hit_or_not_computer_);
        }

    }

    if (state_ == GameState::kUserWinner) {
        has_someone_won_ = true;
        update();
        DrawWinningScreen();
    }

    if (state_ == GameState::kComputerWinner) {
        has_someone_won_ = true;
        update();
        DrawLosingScreen();
    }
}


void MyApp::mouseDown( cinder::app::MouseEvent event ) {
    if (event.isRight()) {
        auto mMouseLoc = event.getPos();
        mouse_x_ = mMouseLoc.x;
        mouse_y_ = mMouseLoc.y;

        if (state_ == GameState::kPickingShips) {
            GatheringXLocationUser(0);
            GatheringYLocationUser(0);
            std::cout << "user x_ shot picking : " << user_x_ << std::endl;
            std::cout << "user y_ shot picking: " << user_y_ << std::endl;
            game_engine_.PlacePlayerShips(game_engine_.user_player_, user_x_, user_y_);
        }

        if (state_ == GameState::kShooting) {
            GatheringXLocationComputer();
            GatheringYLocationComputer();
            std::cout << "computer x_:  " << computer_x_ << std::endl;
            std::cout << "computer y_:  " << computer_y_ << std::endl;
            hit_or_not_user_ = false;
            game_engine_.computer_player_->Attacked(computer_x_, computer_y_);

            if (game_engine_.computer_player_->if_location_hit_or_not_) {
                hit_or_not_user_ = x;
            } else if (!game_engine_.computer_player_->if_location_hit_or_not_) {
                hit_or_not_user_ = o;
            }

            shooting_state_ = Shooting::kComputerAttacked;
            std::cout << "user x_ shot: " << computer_x_ << std::endl;
            std::cout << "user y_ shot: " << computer_y_ << std::endl;
            is_computer_turn_ = true;
        }
    }
}


void MyApp::keyDown(KeyEvent event) {
    if (event.KEY_1) {
        state_ = GameState::kPickingShips;
    }
}


void MyApp::PrintImage(const cinder::gl::Texture2dRef &texture, const cinder::ivec2 &size, const cinder::vec2 &loc) {
    auto box = TextBox()
            .alignment(TextBox::CENTER)
            .size(size)
            .backgroundColor(ColorA(0, 0, 0, 0));
    const auto box_size = box.getSize();
    const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
    const auto surface = box.render();
    cinder::gl::draw(texture, locp);
}


template <typename C>
void PrintText(const string& text, const C& color, const cinder::ivec2& size,
                   const cinder::vec2& loc) {
    auto box = TextBox()
            .alignment(TextBox::CENTER)
            .font(cinder::Font(kNormalFont, 30))
            .size(size)
            .color(color)
            .backgroundColor(ColorA(0, 0, 0, 0))
            .text(text);
    cinder::gl::color(color);
    const auto box_size = box.getSize();
    const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
    const auto surface = box.render();
    const auto texture = cinder::gl::Texture::create(surface);
    cinder::gl::draw(texture, locp);
}


void MyApp::GatheringYLocationComputer() {
    general_location_y_computer_ = 0;
    for (int i = 130; i <= 365; i++) {
        for (int j = 130; j < 145; j++) {
            if (j == mouse_y_) {
                computer_y_ = 0;
                general_location_y_computer_ = 137;
            }
        }
        for (int j = 160; j <= 175; j++) {
            if (j == mouse_y_) {
                computer_y_ = 1;
                general_location_y_computer_ = 167;
            }
        }
        for (int j = 190; j <= 205; j++) {
            if (j == mouse_y_) {
                computer_y_ = 2;
                general_location_y_computer_ = 197;
            }
        }
        for (int j = 220; j <= 235; j++) {
            if (j == mouse_y_) {
                computer_y_ = 3;
                general_location_y_computer_ =  227;
            }
        }
        for (int j = 250; j <= 265; j++) {
            if (j == mouse_y_) {
                computer_y_ = 4;
                general_location_y_computer_ = 257;
            }
        }
        for (int j = 280; j <= 295; j++) {
            if (j == mouse_y_) {
                computer_y_ = 5;
                general_location_y_computer_ = 287;
            }
        }
        for (int j = 310; j <= 325; j++) {
            if (j == mouse_y_) {
                computer_y_ = 6;
                general_location_y_computer_ = 317;
            }
        }
        for (int j = 340; j <= 365; j++) {
            if (j == mouse_y_) {
                computer_y_ = 7;
                general_location_y_computer_ = 347;
            }
        }
    }
}


void MyApp::GatheringYLocationUser(int row) {
    general_location_y_user_ = 0;
    for (int i = 520; i <= 740; i++) {
        for (int j = 520; j < 535; j++) {
            if (row == 0) {
                general_location_y_user_ = 527;
            }
            if (j == mouse_y_) {
                user_y_ = 0;
                general_location_y_user_ = 527;
            }
        }
        for (int j = 550; j <= 565; j++) {
            if (row == 1) {
                general_location_y_user_ = 557;
            }
            if (j == mouse_y_) {
                user_y_ = 1;
                general_location_y_user_ = 557;
            }
        }
        for (int j = 580; j <= 595; j++) {
            if (row == 2) {
                general_location_y_user_ = 587;
            }
            if (j == mouse_y_) {
                user_y_ = 2;
                general_location_y_user_ = 587;
            }
        }
        for (int j = 610; j <= 625; j++) {
            if (row == 3) {
                general_location_y_user_ = 617;
            }
            if (j == mouse_y_) {
                user_y_ = 3;
                general_location_y_user_ = 617;
            }
        }
        for (int j = 640; j <= 655; j++) {
            if (row == 4) {
                general_location_y_user_ = 647;
            }
            if (j == mouse_y_) {
                user_y_ = 4;
                general_location_y_user_ = 647;
            }
        }
        for (int j = 670; j <= 685; j++) {
            if (row == 5) {
                general_location_y_user_ = 676;
            }
            if (j == mouse_y_) {
                user_y_ = 5;
                general_location_y_user_ = 676;
            }
        }
        for (int j = 700; j <= 715; j++) {
            if (row == 6) {
                general_location_y_user_ = 707;
            }
            if (j == mouse_y_) {
                user_y_ = 6;
                general_location_y_user_ = 707;
            }
        }
        for (int j = 730; j <= 745; j++) {
            if (row == 7) {
                general_location_y_user_ = 737;
            }
            if (j == mouse_y_) {
                user_y_ = 7;
                general_location_y_user_ = 737;
            }
        }
    }
 }


void MyApp::GatheringXLocationUser(int col) {
    general_location_x_user_ = 0;
    for (int i = 485; i <= 725; i++) {
        for (int j = 485; j <=515; j++) {
            if (col == 0) {
                general_location_x_user_ = 500;
            }
            if (j == mouse_x_) {
                user_x_ = 0;
                general_location_x_user_ = 500;
            }
        }
        for (int j = 516; j <= 545; j++) {
            if (col == 1) {
                general_location_x_user_ = 530;
            }
            if (j == mouse_x_) {
                user_x_ = 1;
                general_location_x_user_ = 530;
            }
        }
        for (int j = 546; j <= 575; j++) {
            if (col == 2) {
                general_location_x_user_ = 560;
            }
            if (j == mouse_x_) {
                user_x_ = 2;
                general_location_x_user_ = 560;
            }
        }
        for (int j = 576; j <= 605; j++) {
            if (col == 3) {
                general_location_x_user_ = 590;
            }
            if (j == mouse_x_) {
                user_x_ = 3;
                general_location_x_user_ = 590;
            }
        }
        for (int j = 606; j <= 635; j++) {
            if (col == 4) {
                general_location_x_user_ = 620;
            }
            if (j == mouse_x_) {
                user_x_ = 4;
                general_location_x_user_ = 620;
            }
        }
        for (int j = 636; j <= 655; j++) {
            if (col == 5) {
                    general_location_x_user_ = 650;
            }
            if (j == mouse_x_) {
                user_x_ = 5;
                general_location_x_user_ = 650;
            }
        }
        for (int j = 666; j <= 695; j++) {
            if (col == 6) {
                general_location_x_user_ = 680;
            }
            if (j == mouse_x_) {
                user_x_ = 6;
                general_location_x_user_ = 675;
            }
        }
        for (int j = 696; j <= 725; j++) {
            if (col == 7) {
                general_location_x_user_ = 710;
            }
            if (j == mouse_x_) {
                user_x_ = 7;
                general_location_x_user_ = 710;
            }
        }
    }
}


void MyApp::GatheringXLocationComputer() {
    general_location_x_computer_ = 0;
    for (int i = 115; i <= 310; i++) {
        for (int j = 115; j <=135; j++) {
            if (j == mouse_x_) {
                computer_x_ = 0;
                general_location_x_computer_ = 125;
            }
        }
        for (int j = 146; j <= 165; j++) {
            if (j == mouse_x_) {
                computer_x_ = 1;
                general_location_x_computer_ = 155;
            }
        }
        for (int j = 176; j <= 195; j++) {
            if (j == mouse_x_) {
                computer_x_ = 2;
                general_location_x_computer_ = 185;
            }
        }
        for (int j = 206; j <= 225; j++) {
            if (j == mouse_x_) {
                computer_x_ = 3;
                general_location_x_computer_ = 215;
            }
        }
        for (int j = 232; j <= 255; j++) {
            if (j == mouse_x_) {
                computer_x_ = 4;
                general_location_x_computer_ = 245;
            }
        }
        for (int j = 266; j <= 285; j++) {
            if (j == mouse_x_) {
                computer_x_ = 5;
                general_location_x_computer_ = 275;
            }
        }
        for (int j = 296; j <= 315; j++) {
            if (j == mouse_x_) {
                computer_x_ = 6;
                general_location_x_computer_ = 305;
            }
        }
        for (int j = 326; j <= 345; j++) {
            if (j == mouse_x_) {
                computer_x_ = 7;
                general_location_x_computer_ = 335;
            }
        }
    }
}


template <typename C>
void PrintBackground(const C& color, const cinder::ivec2& size) {
    cinder::gl::color(color);
    cinder::gl::drawStrokedRect( Rectf( cinder::app::getWindowWidth()/2-350.0f,
                                      cinder::app::getWindowHeight()/2-350.0f,
                                      cinder::app::getWindowWidth()/2-30.0f,
                                      cinder::app::getWindowHeight()/2-30.0f ) );
    size_t row = 0;
    PrintText(FLAGS_player_name, Color::white(), size, {cinder::app::getWindowCenter().x + (++row) * 200,
                                        cinder::app::getWindowCenter().y + (++row) * 30});
    PrintText("Computer", color, size, {cinder::app::getWindowWidth() /2 - 180.0f,
                                    cinder::app::getWindowHeight() / 2-320.0f});
    PrintText("Instructions:", color, size, {cinder::app::getWindowWidth() /2 - 180.0f,
                                             cinder::app::getWindowCenter().y + (++row) * 19});
    cinder::gl::drawStrokedRect( Rectf( cinder::app::getWindowWidth()/2+30.0f,
                                        cinder::app::getWindowHeight()/2+30.0f,
                                        cinder::app::getWindowWidth()/2+350.0f,
                                        cinder::app::getWindowHeight()/2+350.0f ) );
    cinder::gl::drawStrokedRect( Rectf( cinder::app::getWindowWidth()/2-350.0f,
                                        cinder::app::getWindowHeight()/2+30.0f,
                                        cinder::app::getWindowWidth()/2-30.0f,
                                        cinder::app::getWindowHeight()/2+350.0f ) );
}


void MyApp::DrawBoard() {
     const cinder::vec2 center = getWindowCenter();
     const cinder::ivec2 size = {500, 50};
     const Color color = Color::white();

     PrintText("~War Vessels~", color, size, center);
     PrintImage(missile_, size, {cinder::app::getWindowWidth() / 2 - 80.0f,
                                 cinder::app::getWindowHeight() / 1.95}); // instruction
     PrintImage(missile_, size, {cinder::app::getWindowWidth() / 2 - 80.0f,
                                 cinder::app::getWindowHeight() / 2 - 369.0f}); // computer
     PrintImage(missile_, size, {cinder::app::getWindowWidth() / 2 + 300.0f,
                                 cinder::app::getWindowHeight() / 1.95});
     PrintBackground(color, size);
     DrawComputerBoard();
     DrawUserBoard();
}


void MyApp::DrawHitOrMissUser(char character) {
    const Color color = Color::white();
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 50};
    std::string print(1, character);

    character_and_location_ newPoint = character_and_location_(general_location_x_user_, general_location_y_user_,
            print);
    character_and_location_points_.push_back(newPoint);

    for (auto & character_and_location_point : character_and_location_points_) {
        PrintText(character_and_location_point.s_, color, size, {character_and_location_point.x_,
                                                                         character_and_location_point.y_});
    }
}


void MyApp::DrawHitOrMissComputer(char character) {
     const Color color = Color::white();
     const cinder::vec2 center = getWindowCenter();
     const cinder::ivec2 size = {500, 50};
     std::string print(1, character);

     character_and_location_ newPoint = character_and_location_(general_location_x_computer_,
             general_location_y_computer_, print);
     character_and_location_points_.push_back(newPoint);

     for (auto & character_and_location_point : character_and_location_points_) {
         PrintText(character_and_location_point.s_, color, size, {character_and_location_point.x_,
                                                                          character_and_location_point.y_});
     }
}


void MyApp::DrawPickingShips() {
     std::string text = "U can place up to  " + std::to_string(amount_of_lives_) + " ships";
     const cinder::vec2 center = getWindowCenter();
     const cinder::ivec2 size = {300, 0};
     const Color color = Color::white();
     size_t row = 0;
     PrintText(text, color, size, {cinder::app::getWindowWidth() /2 - 180.0f,
                                      cinder::app::getWindowCenter().y + (++row) * 100});
}


void MyApp::DrawChosenShips() {
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {300, 0};
    location_ new_location = location_(general_location_x_user_ + 115.0f, general_location_y_user_ - 20.0f);
    graphics_anchor_locations_.push_back(new_location);
    for (int i = 0; i < graphics_anchor_locations_.size(); i++) {
        PrintImage(anchor_, size, {graphics_anchor_locations_.at(i).x_, graphics_anchor_locations_.at(i).y_});
    }

}


void MyApp::DrawShootingInstructions() {
     const cinder::ivec2 size_location_points = {500, 50};
     std::string text = "Click where U would like to shoot";
     const cinder::vec2 center = getWindowCenter();
     const cinder::ivec2 size_words = {300, 0};
     const Color color = Color::white();
     size_t row = 0;

     PrintText(text, color, size_words, {cinder::app::getWindowWidth() /2 - 180.0f,
                                      cinder::app::getWindowCenter().y + (++row) * 100});
     PrintText("Ur ships are placed at: ", color, size_location_points, {
         cinder::app::getWindowWidth() /2 + -194,cinder::app::getWindowCenter().y + 250});

     int col = 310.0;
     for (int i = 0; i < game_engine_.user_player_->GetShips().size(); i++) {
         std::string x = std::to_string(game_engine_.user_player_->GetShips().at(i).col_);
         std::string y = std::to_string(game_engine_.user_player_->GetShips().at(i).row_);
         std::string print = "(" + x + " , " + y +")";
         PrintText(print, color, size_location_points, {cinder::app::getWindowWidth() /2 - col,
                                        cinder::app::getWindowCenter().y + 300});
         col = col - 80;
     }

}


void MyApp::DrawWinningScreen() {
    cinder::gl::draw(winning_screen_, getWindowBounds());
     gif_winning_screen_->draw();
}

void MyApp::DrawLosingScreen() {
    cinder::gl::draw(losing_screen_, getWindowBounds());
    gif_losing_screen_->draw();
}


void MyApp::DrawComputerBoard() {
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {50, 50};
    const Color color = Color::white();
    int horizontal_location_numbering = 270.0f;

    for (int i{0}; i < width_; i++) {
        string str = std::to_string(i);
        PrintText(str, color, size, {cinder::app::getWindowWidth() /2 - horizontal_location_numbering,
                                     cinder::app::getWindowHeight() / 2 - 290.0f});
        horizontal_location_numbering = horizontal_location_numbering - 30;
    }

    int horizontal_location_in_grid = 270.0f;
    int vertical_location_in_grid = 250.0f;
    for (int row{0}; row < height_; row++) {
        string str= std::to_string(row);
        PrintText(str, color, size, {cinder::app::getWindowWidth() /2 - horizontal_location_in_grid - 40,
                                     cinder::app::getWindowHeight() / 2 - vertical_location_in_grid});
        for (int col{0}; col < width_; col++) {
            PrintImage(ship_, size, {cinder::app::getWindowWidth() / 2 - horizontal_location_in_grid,
                                     cinder::app::getWindowHeight() / 2 - vertical_location_in_grid});
            horizontal_location_in_grid = horizontal_location_in_grid - 30;
        }
        vertical_location_in_grid = vertical_location_in_grid - 30;
        horizontal_location_in_grid = 270.0f;
    }
}


void MyApp::DrawUserBoard() {
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {50, 50};
    const Color color = Color::white();
    int horizontal_location_numbering = -100;

    for (int i{0}; i < width_; i++) {
        string str = std::to_string(i);
        PrintText(str, color, size, {cinder::app::getWindowWidth() /2 - horizontal_location_numbering,
                                     cinder::app::getWindowHeight() / 2 + 100.0f});
        horizontal_location_numbering = horizontal_location_numbering - 30;
    }

    int horizontal_location_in_grid = -100.0f;
    int vertical_location_in_grid = -140.0f;
    for (int row{0}; row < height_; row++) {
        string str= std::to_string(row);
        PrintText(str, color, size, {cinder::app::getWindowWidth() /2 - horizontal_location_in_grid - 40,
                                     cinder::app::getWindowHeight() / 2 - vertical_location_in_grid});
        for (int col{0}; col < width_; col++) {
            PrintImage(ship_, size, {cinder::app::getWindowWidth() / 2 - horizontal_location_in_grid,
                                     cinder::app::getWindowHeight() / 2 - vertical_location_in_grid});
            horizontal_location_in_grid = horizontal_location_in_grid - 30;
        }
        vertical_location_in_grid = vertical_location_in_grid - 30;
        horizontal_location_in_grid = -100.0f;
    }
}
}  // namespace myapp
