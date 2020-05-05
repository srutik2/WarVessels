// Copyright (c) 2020 [Your Name]. All rights reserved.

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

DECLARE_string(playerName);
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
//change to string
const char kNormalFont[] = "Papyrus";

MyApp::MyApp() :
        width_(FLAGS_width),
        height_(FLAGS_height),
        user_name_(FLAGS_playerName),
        amount_of_lives_(FLAGS_amount_of_lives),
        game_engine_ {FLAGS_playerName, FLAGS_amount_of_lives, FLAGS_width, FLAGS_height, FLAGS_is_easy_player_strategy},
        state_{GameState::KGameNotStarted},
        is_computer_turn_{false},
        has_someone_won{false},
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
    background = cinder::gl::Texture2d::create(loadImage(loadAsset("darkoceanbackground.jpg")));
    openingscreen = cinder::gl::Texture2d::create(loadImage(loadAsset("war vessels.png")));
    gif_winning_screen_ = cinder::ciAnimatedGif::create(loadAsset("ezgif.com-resize.gif"));
    ship = cinder::gl::Texture2d::create(loadImage(loadAsset("Webp.net-resizeimage.png")));
    missle = cinder::gl::Texture2d::create(loadImage(loadAsset("missle_.png")));
    winningscreen = cinder::gl::Texture2d::create(loadImage(loadAsset("ws.jpg")));
    anchor = cinder::gl::Texture2d::create(loadImage(loadAsset("anchor.png")));
    losingscreen = cinder::gl::Texture2d::create(loadImage(loadAsset("losing.png")));
    gif_losing_screen_ = cinder::ciAnimatedGif::create(loadAsset("ssss.gif"));
    logo = cinder::gl::Texture2d::create(loadImage(loadAsset("logo.png")));
}


void MyApp::update() {
     if (game_engine_.DeterminingWinner() == 0) {
         state_ = GameState::kComputerWinner;
     }

    if (game_engine_.DeterminingWinner() == 1) {
        state_ = GameState::kUserWinner;
    }

    if (state_ == GameState::kPickingShips) {
        if (game_engine_.user_player_->getShips().size() == amount_of_lives_) {
            game_engine_.PlaceRandomShips(game_engine_.computer_player_);
        }
        if (game_engine_.computer_player_->getShips().size() == amount_of_lives_ && game_engine_.user_player_->getShips().size() == amount_of_lives_) {
            state_ = GameState::kShooting;
        }
    }

     if (state_ == GameState::kShooting) {
         if (is_computer_turn_) {
             draw();
             int computer_shot_col = game_engine_.FindRandomRowOrCol(0);
             int computer_shot_row = game_engine_.FindRandomRowOrCol(1);

             hit_or_not_computer_ = false;
             game_engine_.user_player_->Attacked(computer_shot_col, computer_shot_row); // user attacked by computer player shots
             shooting_state_ = Shooting::kUserAttacked; // user attacked

             if (game_engine_.user_player_->hit_or_not) {
                 hit_or_not_computer_ = 'X';
             }

             if (!game_engine_.user_player_->hit_or_not) {
                 hit_or_not_computer_ = 'O';
             }

             std::cout << "computer col shot:: " << computer_shot_col << std::endl;
             GatheringXLocationUser(computer_shot_col);
             std::cout << "computer  row shot:: " << computer_shot_row << std::endl;
             GatheringYLocationUser(computer_shot_row);
             is_computer_turn_ = false;
         }
     }
}


void MyApp::draw() {
    const cinder::ivec2 size = {500, 50};
     cinder::gl::color(Color::white());
     cinder::gl::draw(background, getWindowBounds());
     DrawBoard();
    const cinder::ivec2 size_ = {5, 5};
     PrintImage(logo, size, {cinder::app::getWindowWidth() /2 + 305, cinder::app::getWindowHeight() / 2 - 310});
     if (state_ == GameState::KGameNotStarted) {
         cinder::gl::draw(openingscreen, getWindowBounds());
     }
     if (state_ == GameState::kPickingShips) {
        for (int ship_placement_count = 0; ship_placement_count < game_engine_.user_player_->GetLives(); ship_placement_count++) {
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
        has_someone_won = true;
        update();
        DrawWinningScreen();
    }

    if (state_ == GameState::kComputerWinner) {
        has_someone_won = true;
        update();
        DrawLosingScreen();
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
        cinder::gl::color(color);
        auto box = TextBox()
                .alignment(TextBox::CENTER)
                .font(cinder::Font(kNormalFont, 30))
                .size(size)
                .color(color)
                .backgroundColor(ColorA(0, 0, 0, 0))
                .text(text);

        const auto box_size = box.getSize();
        const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
        const auto surface = box.render();
        const auto texture = cinder::gl::Texture::create(surface);
        cinder::gl::draw(texture, locp);
}

void MyApp::mouseDown( cinder::app::MouseEvent event ) {
    if (event.isRight()) {
        auto mMouseLoc = event.getPos();
        mouse_x_ = mMouseLoc.x;
        mouse_y_ = mMouseLoc.y;

        if (state_ == GameState::kPickingShips) {
            GatheringXLocationUser(0);
            GatheringYLocationUser(0);
            std::cout << "user x shot picking : " << user_x << std::endl;
            std::cout << "user y shot picking: " << user_y << std::endl;
            game_engine_.PlacePlayerShips(game_engine_.user_player_, user_x, user_y);
        }

        if (state_ == GameState::kShooting) {
            GatheringXLocationComputer();
            GatheringYLocationComputer();
            std::cout << "computer x:  " << computer_x << std::endl;
            std::cout << "computer y:  " << computer_y << std::endl;
            std::cout << "general location x computer:  " << general_location_x_computer_ << std::endl;
            std::cout << "general location y computer:  " << general_location_y_computer_ << std::endl;
            hit_or_not_user_ = false;
            game_engine_.computer_player_->Attacked(computer_x, computer_y);

            if (game_engine_.computer_player_->hit_or_not) {
                hit_or_not_user_ = 'X';
            } else if (!game_engine_.computer_player_->hit_or_not) {
                hit_or_not_user_ = 'O';
            }

            shooting_state_ = Shooting::kComputerAttacked;
            std::cout << "user x shot: " << computer_x << std::endl;
            std::cout << "user y shot: " << computer_y << std::endl;
            is_computer_turn_ = true;
        }
    }

}

void MyApp::GatheringYLocationComputer() {
    general_location_y_computer_ = 0;
    for (int i = 130; i <= 365; i++) {
        for (int j = 130; j < 145; j++) {
            if (j == mouse_y_) {
                computer_y = 0;
                general_location_y_computer_ = 137;
            }
        }
        for (int j = 160; j <= 175; j++) {
            if (j == mouse_y_) {
                computer_y = 1;
                general_location_y_computer_ = 167;
            }
        }
        for (int j = 190; j <= 205; j++) {
            if (j == mouse_y_) {
                computer_y = 2;
                general_location_y_computer_ = 197;
            }
        }
        for (int j = 220; j <= 235; j++) {
            if (j == mouse_y_) {
                computer_y = 3;
                general_location_y_computer_ =  227;
            }
        }
        for (int j = 250; j <= 265; j++) {
            if (j == mouse_y_) {
                computer_y = 4;
                general_location_y_computer_ = 257;
            }
        }
        for (int j = 280; j <= 295; j++) {
            if (j == mouse_y_) {
                computer_y = 5;
                general_location_y_computer_ = 287;
            }
        }
        for (int j = 310; j <= 325; j++) {
            if (j == mouse_y_) {
                computer_y = 6;
                general_location_y_computer_ = 317;
            }
        }
        for (int j = 340; j <= 365; j++) {
            if (j == mouse_y_) {
                computer_y = 7;
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
                    user_y = 0;
                    general_location_y_user_ = 527;
                }
            }
            for (int j = 550; j <= 565; j++) {
                if (row == 1) {
                    general_location_y_user_ = 557;
                }
                if (j == mouse_y_) {
                    user_y = 1;
                    general_location_y_user_ = 557;
                }
            }
            for (int j = 580; j <= 595; j++) {
                if (row == 2) {
                    general_location_y_user_ = 587;
                }
                if (j == mouse_y_) {
                    user_y = 2;
                    general_location_y_user_ = 587;
                }
            }
            for (int j = 610; j <= 625; j++) {
                if (row == 3) {
                    general_location_y_user_ = 617;
                }
                if (j == mouse_y_) {
                    user_y = 3;
                    general_location_y_user_ = 617;
                }
            }
            for (int j = 640; j <= 655; j++) {
                if (row == 4) {
                    general_location_y_user_ = 647;
                }
                if (j == mouse_y_) {
                    user_y = 4;
                    general_location_y_user_ = 647;
                }
            }
            for (int j = 670; j <= 685; j++) {
                if (row == 5) {
                    general_location_y_user_ = 676;
                }
                if (j == mouse_y_) {
                    user_y = 5;
                    general_location_y_user_ = 676;
                }
            }
            for (int j = 700; j <= 715; j++) {
                if (row == 6) {
                    general_location_y_user_ = 707;
                }
                if (j == mouse_y_) {
                    user_y = 6;
                    general_location_y_user_ = 707;
                }
            }
            for (int j = 730; j <= 745; j++) {
                if (row == 7) {
                    general_location_y_user_ = 737;
                }
                if (j == mouse_y_) {
                    user_y = 7;
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
                    user_x = 0;
                    general_location_x_user_ = 500;
                }
            }
            for (int j = 516; j <= 545; j++) {
                if (col == 1) {
                    general_location_x_user_ = 530;
                }
                if (j == mouse_x_) {
                    user_x = 1;
                    general_location_x_user_ = 530;
                }
            }
            for (int j = 546; j <= 575; j++) {
                if (col == 2) {
                    general_location_x_user_ = 560;
                }
                if (j == mouse_x_) {
                    user_x = 2;
                    general_location_x_user_ = 560;
                }
            }
            for (int j = 576; j <= 605; j++) {
                if (col == 3) {
                    general_location_x_user_ = 590;
                }
                if (j == mouse_x_) {
                    user_x = 3;
                    general_location_x_user_ = 590;
                }
            }
            for (int j = 606; j <= 635; j++) {
                if (col == 4) {
                    general_location_x_user_ = 620;
                }
                if (j == mouse_x_) {
                    user_x = 4;
                    general_location_x_user_ = 620;
                }
            }
            for (int j = 636; j <= 655; j++) {
                if (col == 5) {
                    general_location_x_user_ = 650;
                }
                if (j == mouse_x_) {
                    user_x = 5;
                    general_location_x_user_ = 650;
                }
            }
            for (int j = 666; j <= 695; j++) {
                if (col == 6) {
                    general_location_x_user_ = 680;
                }
                if (j == mouse_x_) {
                    user_x = 6;
                    general_location_x_user_ = 675;
                }
            }
            for (int j = 696; j <= 725; j++) {
                if (col == 7) {
                    general_location_x_user_ = 710;
                }
                if (j == mouse_x_) {
                    user_x = 7;
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
                computer_x = 0;
                general_location_x_computer_ = 125;
            }
        }
        for (int j = 146; j <= 165; j++) {
            if (j == mouse_x_) {
                computer_x = 1;
                general_location_x_computer_ = 155;
            }
        }
        for (int j = 176; j <= 195; j++) {
            if (j == mouse_x_) {
                computer_x = 2;
                general_location_x_computer_ = 185;
            }
        }
        for (int j = 206; j <= 225; j++) {
            if (j == mouse_x_) {
                computer_x = 3;
                general_location_x_computer_ = 215;
            }
        }
        for (int j = 232; j <= 255; j++) {
            if (j == mouse_x_) {
                computer_x = 4;
                general_location_x_computer_ = 245;
            }
        }
        for (int j = 266; j <= 285; j++) {
            if (j == mouse_x_) {
                computer_x = 5;
                general_location_x_computer_ = 275;
            }
        }
        for (int j = 296; j <= 315; j++) {
            if (j == mouse_x_) {
                computer_x = 6;
                general_location_x_computer_ = 305;
            }
        }
        for (int j = 326; j <= 345; j++) {
            if (j == mouse_x_) {
                computer_x = 7;
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

    PrintText(FLAGS_playerName, Color::white(), size, {cinder::app::getWindowCenter().x + (++row) * 200,
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
     PrintImage(missle, size, {cinder::app::getWindowWidth() /2-80.0f, cinder::app::getWindowHeight() / 1.95}); // instruction
     PrintImage(missle, size, {cinder::app::getWindowWidth() /2-80.0f, cinder::app::getWindowHeight() / 2-369.0f}); // computer
     PrintImage(missle, size, {cinder::app::getWindowWidth() /2+300.0f, cinder::app::getWindowHeight() / 1.95});
     PrintBackground(color, size);
     DrawComputerBoard();
     DrawUserBoard();
}


void MyApp::DrawHitOrMissUser(char character) {
    const Color color = Color::white();
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 50};
    std::string print(1, character);

    Points newPoint = Points(general_location_x_user_, general_location_y_user_, print);
    points.push_back(newPoint);

    for (int i = 0; i < points.size(); i++) {
        PrintText(points.at(i).s, color, size, {points.at(i).x,
                                                points.at(i).y});
    }
}


void MyApp::DrawHitOrMissComputer(char character) {
     const Color color = Color::white();
     const cinder::vec2 center = getWindowCenter();
     const cinder::ivec2 size = {500, 50};
     std::string print(1, character);

     Points newPoint = Points(general_location_x_computer_, general_location_y_computer_, print);
     points.push_back(newPoint);

     for (int i = 0; i < points.size(); i++) {
         PrintText(points.at(i).s, color, size, {points.at(i).x,
                                                   points.at(i).y});
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
    location new_location = location(general_location_x_user_+ 115.0f, general_location_y_user_ - 20.0f);
    locations.push_back(new_location);
    for (int i = 0; i < locations.size(); i++) {
        PrintImage(anchor, size, {locations.at(i).x, locations.at(i).y});
    }

}

void MyApp::DrawShootingInstructions() {
     const cinder::ivec2 size_ = {500, 50};


     std::string text = "Click where U would like to shoot";
     const cinder::vec2 center = getWindowCenter();
     const cinder::ivec2 size = {300, 0};
     const Color color = Color::white();
     size_t row = 0;
     PrintText(text, color, size, {cinder::app::getWindowWidth() /2 - 180.0f,
                                      cinder::app::getWindowCenter().y + (++row) * 100});

    PrintText("Ur ships are placed at: ", color, size_, {cinder::app::getWindowWidth() /2 + -194,
                                    cinder::app::getWindowCenter().y + 250});

    int col = 310.0;
     for (int i = 0; i < game_engine_.user_player_->getShips().size(); i++) {
         std::string x = std::to_string(game_engine_.user_player_->getShips().at(i).col);
         std::string y = std::to_string(game_engine_.user_player_->getShips().at(i).row);
         std::string print = "(" + x + " , " + y +")";
         PrintText(print, color, size_, {cinder::app::getWindowWidth() /2 - col,
                                        cinder::app::getWindowCenter().y + 300});
         col = col - 80;
     }

}


void MyApp::DrawWinningScreen() {
    cinder::gl::draw(winningscreen, getWindowBounds());
     gif_winning_screen_->draw();
}

void MyApp::DrawLosingScreen() {
    cinder::gl::draw(losingscreen, getWindowBounds());
    gif_losing_screen_->draw();
}


void MyApp::DrawComputerBoard() {
    mylibrary::Board* board = new mylibrary::Board(width_, height_);
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {50, 50};
    const Color color = Color::white();
    int horizontal_location_numbering = 270.0f;

    for (int i{0}; i < width_; i++) {
        string str = std::to_string(i);
        PrintText(str, color, size, {cinder::app::getWindowWidth() /2 - horizontal_location_numbering, cinder::app::getWindowHeight() / 2 - 290.0f});
        horizontal_location_numbering = horizontal_location_numbering - 30;
    }

    int horizontal_location_in_grid = 270.0f;
    int vertical_location_in_grid = 250.0f;

    for (int row{0}; row < height_; row++) {
        string str= std::to_string(row);
        PrintText(str, color, size, {cinder::app::getWindowWidth() /2 - horizontal_location_in_grid - 40, cinder::app::getWindowHeight() / 2 - vertical_location_in_grid});
        for (int col{0}; col < width_; col++) {
            PrintImage(ship, size, {cinder::app::getWindowWidth() /2 - horizontal_location_in_grid, cinder::app::getWindowHeight() / 2 - vertical_location_in_grid});
            horizontal_location_in_grid = horizontal_location_in_grid - 30;
        }
        vertical_location_in_grid = vertical_location_in_grid - 30;
        horizontal_location_in_grid = 270.0f;
    }
}


void MyApp::DrawUserBoard() {
    mylibrary::Board* board = new mylibrary::Board(width_, height_);
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {50, 50};
    const Color color = Color::white();
    int horizontal_location_numbering = -100;

    for (int i{0}; i < width_; i++) {
        string str = std::to_string(i);
        PrintText(str, color, size, {cinder::app::getWindowWidth() /2 - horizontal_location_numbering, cinder::app::getWindowHeight() / 2 + 100.0f});
        horizontal_location_numbering = horizontal_location_numbering - 30;
    }

    int horizontal_location_in_grid = -100.0f;
    int vertical_location_in_grid = -140.0f;

    for (int row{0}; row < height_; row++) {
        string str= std::to_string(row);
        PrintText(str, color, size, {cinder::app::getWindowWidth() /2 - horizontal_location_in_grid - 40, cinder::app::getWindowHeight() / 2 - vertical_location_in_grid});
        for (int col{0}; col < width_; col++) {
            PrintImage(ship, size, {cinder::app::getWindowWidth() /2 - horizontal_location_in_grid, cinder::app::getWindowHeight() / 2 - vertical_location_in_grid});
            horizontal_location_in_grid = horizontal_location_in_grid - 30;
        }
        vertical_location_in_grid = vertical_location_in_grid - 30;
        horizontal_location_in_grid = -100.0f;
    }
 }



}  // namespace myapp
