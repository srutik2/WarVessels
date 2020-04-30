// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include "../src/board.h"

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
 width(FLAGS_width),
 height(FLAGS_height),
 playerName(FLAGS_playerName),
 amount_of_lives(FLAGS_amount_of_lives),
 menu {FLAGS_playerName, FLAGS_amount_of_lives, FLAGS_width, FLAGS_height},
 state_{GameState::kPickingShips},
 count_{0},
 someone_won{false},
 general_location_x_user{0},
 general_location_y_user{0},
 general_location_x_computer{0},
 general_location_y_computer{0},
 computer_attacked{false},
 user_attacked{false},
 state__{Shooting::kNoOneAtttacked},
 hit_or_not{'X'} { }

void MyApp::setup() {
    background = cinder::gl::Texture2d::create(loadImage(loadAsset("backg.jpg")));
    gif_example = cinder::ciAnimatedGif::create(loadAsset("something.gif"));
}

void MyApp::update() {
     //std::cout << "user player size: " <<menu.user_player_instance->getShips().size()  << std::endl;
     //std::cout << "computer player size: " <<menu.computer_player_instance->getShips().size() << std::endl;

     if (menu.DeterminingWinner() == 0) {
         state_ = GameState::kComputerWinner;
     }

    if (menu.DeterminingWinner() == 1) {
        state_ = GameState::kUserWinner;
    }

    if (state_ == GameState::kPickingShips) {
        if (menu.user_player_instance->getShips().size() == amount_of_lives) {
            menu.PlaceRandomShips(menu.computer_player_instance);
        }
        if (menu.computer_player_instance->getShips().size() == amount_of_lives && menu.user_player_instance->getShips().size() == amount_of_lives) {
            state_ = GameState::kShooting;
        }
    }

    //if (menu.user_player_instance->getShips().size() == 0|| menu.computer_player_instance->getShips().size() == 0) {
    //   state_ = GameState::kGameOver;
    //}

     if (state_ == GameState::kShooting) {
         if (count_ == 1) {
             int computer_shot_col = menu.FindRandomRowOrCol(0);
             int computer_shot_row = menu.FindRandomRowOrCol(1);
             int attacked_number = menu.user_player_instance->Attacked(computer_shot_col, computer_shot_row); // user attacked by computer player shots
             if ( attacked_number == 0) {
                 hit_or_not = 'O';
             } else if (attacked_number == 1) {
                 hit_or_not = 'X';
             }
             std::cout << "computer col shot:: " << computer_shot_col << std::endl;
             GatheringXLocationUser(computer_shot_col);
             std::cout << "computer  row shot:: " << computer_shot_row << std::endl;
             GatheringYLocationUser(computer_shot_row);
             state__ = Shooting::kUserAttacked; // user attacked
             count_--;
         }
     }
 }


void MyApp::draw() {

     if (!someone_won) {
         cinder::gl::color(Color::white());
         cinder::gl::draw(background, getWindowBounds());
         DrawBoard();
         DrawHitOrMiss(hit_or_not);
     } else if (someone_won) {
         DrawWinningScreen();
     }


    if (state_ == GameState::kPickingShips) {
        for (int ship_placement_count = 0; ship_placement_count < menu.user_player_instance->GetLives(); ship_placement_count++) {
            DrawPickingShips();
        }
    }

    if (state_ == GameState::kShooting) {
        DrawShootingInstructions();

    }

    if (state_ == GameState::kUserWinner) {
        someone_won = true;
    }
}


    void MyApp::keyDown(KeyEvent event) { }


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
    if (event.isRight() && event.isShiftDown()) {

        auto mMouseLoc = event.getPos();
        mouse_x_ = mMouseLoc.x;
        mouse_y_ = mMouseLoc.y;
        std::cout << "Mouse location: " << mMouseLoc << std::endl;

        if (state_ == GameState::kPickingShips) {
            GatheringXLocationUser(0);
            GatheringYLocationUser(0);
            std::cout << "user x shot picking : " << user_x << std::endl;
            std::cout << "user y shot picking: " << user_y << std::endl;
            menu.PlacePlayerShips(menu.user_player_instance, user_x, user_y);
        }

        if (state_ == GameState::kShooting) {
            GatheringXLocationComputer();
            GatheringYLocationComputer();
            int attacked_number = menu.computer_player_instance->Attacked(computer_x, computer_y); // computer player attacked
            if ( attacked_number == 0) {
                hit_or_not = 'O';
            } else if (attacked_number == 1) {
                hit_or_not = 'X';
            }
            std::cout << "user x shot: " << computer_x << std::endl;
            std::cout << "user y shot: " << computer_y << std::endl;
            state__ = Shooting::kComputerAttacked;
            count_++;
        }
}

}

void MyApp::GatheringYLocationComputer() { // in the computer square gets y coordinate
    general_location_y_computer = 0;
    for (int i = 130; i <= 365; i++) {
        for (int j = 130; j < 145; j++) {
            if (j == mouse_y_) {
                computer_y = 0;
                general_location_y_computer = 137;
            }
        }
        for (int j = 160; j <= 175; j++) {
            if (j == mouse_y_) {
                computer_y = 1;
                general_location_y_computer = 167;
            }
        }
        for (int j = 190; j <= 205; j++) {
            if (j == mouse_y_) {
                computer_y = 2;
                general_location_y_computer = 197;
            }
        }
        for (int j = 220; j <= 235; j++) {
            if (j == mouse_y_) {
                computer_y = 3;
                general_location_y_computer =  227;
            }
        }
        for (int j = 250; j <= 265; j++) {
            if (j == mouse_y_) {
                computer_y = 4;
                general_location_y_computer = 257;
            }
        }
        for (int j = 280; j <= 295; j++) {
            if (j == mouse_y_) {
                computer_y = 5;
                general_location_y_computer = 287;
            }
        }
        for (int j = 310; j <= 325; j++) {
            if (j == mouse_y_) {
                computer_y = 6;
                general_location_y_computer = 317;
            }
        }
        for (int j = 340; j <= 365; j++) {
            if (j == mouse_y_) {
                computer_y = 7;
                general_location_y_computer = 347;
            }
        }
    }
}
void MyApp::GatheringYLocationUser(int row) { // in the user square gets the y location
        general_location_y_user = 0;
        for (int i = 520; i <= 740; i++) {
            for (int j = 520; j < 535; j++) {
                if (row == 0) {
                    general_location_y_user = 527;
                }
                if (j == mouse_y_) {
                    user_y = 0;
                    general_location_y_user = 527;
                }
            }
            for (int j = 550; j <= 565; j++) {
                if (row == 1) {
                    general_location_y_user = 557;
                }
                if (j == mouse_y_) {
                    user_y = 1;
                    general_location_y_user = 557;
                }
            }
            for (int j = 580; j <= 595; j++) {
                if (row == 2) {
                    general_location_y_user = 587;
                }
                if (j == mouse_y_) {
                    user_y = 2;
                    general_location_y_user = 587;
                }
            }
            for (int j = 610; j <= 625; j++) {
                if (row == 3) {
                    general_location_y_user = 617;
                }
                if (j == mouse_y_) {
                    user_y = 3;
                    general_location_y_user = 617;
                }
            }
            for (int j = 640; j <= 655; j++) {
                if (row == 4) {
                    general_location_y_user = 647;
                }
                if (j == mouse_y_) {
                    user_y = 4;
                    general_location_y_user = 647;
                }
            }
            for (int j = 670; j <= 685; j++) {
                if (row == 5) {
                    general_location_y_user = 667;
                }
                if (j == mouse_y_) {
                    user_y = 5;
                    general_location_y_user = 667;
                }
            }
            for (int j = 700; j <= 715; j++) {
                if (row == 6) {
                    general_location_y_user = 707;
                }
                if (j == mouse_y_) {
                    user_y = 6;
                    general_location_y_user = 707;
                }
            }
            for (int j = 730; j <= 745; j++) {
                if (row == 7) {
                    general_location_y_user = 737;
                }
                if (j == mouse_y_) {
                    user_y = 7;
                    general_location_y_user = 737;
                }
            }
        }
 }

void MyApp::GatheringXLocationUser(int col) { // in the user square gets the x location
        general_location_x_user = 0;
        for (int i = 485; i <= 725; i++) {
            for (int j = 485; j <=515; j++) {
                if (col == 0) {
                    general_location_x_user = 495;
                }
                if (j == mouse_x_) {
                    user_x = 0;
                    general_location_x_user = 495;
                }
            }
            for (int j = 516; j <= 545; j++) {
                if (col == 1) {
                    general_location_x_user = 525;
                }
                if (j == mouse_x_) {
                    user_x = 1;
                    general_location_x_user = 525;
                }
            }
            for (int j = 546; j <= 575; j++) {
                if (col == 2) {
                    general_location_x_user = 555;
                }
                if (j == mouse_x_) {
                    user_x = 2;
                    general_location_x_user = 555;
                }
            }
            for (int j = 576; j <= 605; j++) {
                if (col == 3) {
                    general_location_x_user = 575;
                }
                if (j == mouse_x_) {
                    user_x = 3;
                    general_location_x_user = 575;
                }
            }
            for (int j = 606; j <= 635; j++) {
                if (col == 4) {
                    general_location_x_user = 615;
                }
                if (j == mouse_x_) {
                    user_x = 4;
                    general_location_x_user = 615;
                }
            }
            for (int j = 636; j <= 655; j++) {
                if (col == 5) {
                    general_location_x_user = 645;
                }
                if (j == mouse_x_) {
                    user_x = 5;
                    general_location_x_user = 645;
                }
            }
            for (int j = 666; j <= 695; j++) {
                if (col == 6) {
                    general_location_x_user = 675;
                }
                if (j == mouse_x_) {
                    user_x = 6;
                    general_location_x_user = 675;
                }
            }
            for (int j = 696; j <= 725; j++) {
                if (col == 7) {
                    general_location_x_user = 705;
                }
                if (j == mouse_x_) {
                    user_x = 7;
                    general_location_x_user = 705;
                }
            }
        }
}

void MyApp::GatheringXLocationComputer() { // in the computer square gets the x location
    general_location_x_computer = 0;
    for (int i = 115; i <= 310; i++) {
        for (int j = 115; j <=145; j++) {
            if (j == mouse_x_) {
                computer_x = 0;
                general_location_x_computer = 125;
            }
        }
        for (int j = 146; j <= 175; j++) {
            if (j == mouse_x_) {
                computer_x = 1;
                general_location_x_computer = 155;
            }
        }
        for (int j = 176; j <= 205; j++) {
            if (j == mouse_x_) {
                computer_x = 2;
                general_location_x_computer = 185;
            }
        }
        for (int j = 206; j <= 235; j++) {
            if (j == mouse_x_) {
                computer_x = 3;
                general_location_x_computer = 215;
            }
        }
        for (int j = 236; j <= 265; j++) {
            if (j == mouse_x_) {
                computer_x = 4;
                general_location_x_computer = 245;
            }
        }
        for (int j = 266; j <= 295; j++) {
            if (j == mouse_x_) {
                computer_x = 5;
                general_location_x_computer = 275;
            }
        }
        for (int j = 296; j <= 325; j++) {
            if (j == mouse_x_) {
                computer_x = 6;
                general_location_x_computer = 305;
            }
        }
        for (int j = 326; j <= 355; j++) {
            if (j == mouse_x_) {
                computer_x = 7;
                general_location_x_computer = 335;
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
    PrintText("User", Color::black(), size, {cinder::app::getWindowCenter().x + (++row) * 180,
                                        cinder::app::getWindowCenter().y + (++row) * 30});
    PrintText("Computer", color, size, {cinder::app::getWindowWidth() /2 - 180.0f,
                                    cinder::app::getWindowHeight() / 2-325.0f});
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

        PrintText("~Battleship~", color, size, center);
        PrintBackground(color, size);
         ComputerPrintBoard();
        UserPrintBoard();
}


    void MyApp::DrawHitOrMiss(char character) {
        const Color color = Color::white();
        const cinder::vec2 center = getWindowCenter();
        const cinder::ivec2 size = {500, 50};
        std::string print = std::to_string(character);

        for (int i = 0; i < points.size(); i++) {
            PrintText(points.at(i).s, color, size, {points.at(i).x,
                                                   points.at(i).y});
           // std::cout << "x point" << points.at(i).x << std::endl;
           // std::cout << "y point" << points.at(i).y << std::endl;
        }


        if (state__ == Shooting::kComputerAttacked) {
            std::cout << "general x location user: " << general_location_x_user << std::endl;
            std::cout << "general y location user: " << general_location_y_user << std::endl;
            PrintText(print, color, size, {general_location_x_user,
                                           general_location_y_user});
            Points newPoint = Points(general_location_x_user, general_location_y_user, print);
           // std::cout << "general x location user" << general_location_x_user << std::endl;
           // std::cout << "general y location user" << general_location_y_user << std::endl;
            points.push_back(newPoint);
        } else if (state__ == Shooting::kUserAttacked){
           // std::cout << "General X location"  <<  general_location_x_computer << std::endl;
           // std::cout << "General Y location"  <<  general_location_y_computer << std::endl;
            PrintText(print, color, size, {general_location_x_computer, general_location_y_computer});
            Points newPoint = Points(general_location_x_computer, general_location_y_computer, print);
            points.push_back(newPoint);
        }

    }

void MyApp::DrawPickingShips() {
     std::string text = "U can place up to  "  +std::to_string(amount_of_lives) +" ships";
        const cinder::vec2 center = getWindowCenter();
        const cinder::ivec2 size = {300, 0};
        const Color color = Color::white();
        size_t row = 0;
        PrintText(text, color, size, {cinder::app::getWindowWidth() /2 - 180.0f,
                                      cinder::app::getWindowCenter().y + (++row) * 100});
 }

void MyApp::DrawShootingInstructions() {
        std::string text = "Click where U would like to shoot";
        const cinder::vec2 center = getWindowCenter();
        const cinder::ivec2 size = {300, 0};
        const Color color = Color::white();
        size_t row = 0;
        PrintText(text, color, size, {cinder::app::getWindowWidth() /2 - 180.0f,
                                      cinder::app::getWindowCenter().y + (++row) * 100});
}

void MyApp::DrawWinningScreen() {
        cinder::gl::clear(Color(0, 0, 1));
        gif_example->draw();
}

void MyApp::ComputerPrintBoard() {
    mylibrary::Board* board = new mylibrary::Board(width, height);
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {50, 50};
    const Color color = Color::white();
    int horizontal_location_numbering = 270.0f;

    for (int i{0}; i < width; i++) {
        string str = std::to_string(i);
        PrintText(str, color, size, {cinder::app::getWindowWidth() /2 - horizontal_location_numbering, cinder::app::getWindowHeight() / 2 - 290.0f});
        horizontal_location_numbering = horizontal_location_numbering - 30;
    }

    int horizontal_location_in_grid = 270.0f;
    int vertical_location_in_grid = 250.0f;

    for (int row{0}; row < height; row++) {
        string str= std::to_string(row);
        PrintText(str, color, size, {cinder::app::getWindowWidth() /2 - horizontal_location_in_grid - 40, cinder::app::getWindowHeight() / 2 - vertical_location_in_grid});
        for (int col{0}; col < width; col++) {
            PrintText(board->grid[col][row], color, size, {cinder::app::getWindowWidth() /2 - horizontal_location_in_grid, cinder::app::getWindowHeight() / 2 - vertical_location_in_grid});
            horizontal_location_in_grid = horizontal_location_in_grid - 30;
        }
        vertical_location_in_grid = vertical_location_in_grid - 30;
        horizontal_location_in_grid = 270.0f;
    }
}

void MyApp::UserPrintBoard() {
    mylibrary::Board* board = new mylibrary::Board(width, height);
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {50, 50};
    const Color color = Color::black();
    int horizontal_location_numbering = -100;

    for (int i{0}; i < width; i++) {
        string str = std::to_string(i);
        PrintText(str, color, size, {cinder::app::getWindowWidth() /2 - horizontal_location_numbering, cinder::app::getWindowHeight() / 2 + 100.0f});
        horizontal_location_numbering = horizontal_location_numbering - 30;
    }

    int horizontal_location_in_grid = -100.0f;
    int vertical_location_in_grid = -140.0f;

    for (int row{0}; row < height; row++) {
        string str= std::to_string(row);
        PrintText(str, color, size, {cinder::app::getWindowWidth() /2 - horizontal_location_in_grid - 40, cinder::app::getWindowHeight() / 2 - vertical_location_in_grid});
        for (int col{0}; col < width; col++) {
            PrintText(board->grid[col][row], color, size, {cinder::app::getWindowWidth() /2 - horizontal_location_in_grid, cinder::app::getWindowHeight() / 2 - vertical_location_in_grid});
            horizontal_location_in_grid = horizontal_location_in_grid - 30;
        }
        vertical_location_in_grid = vertical_location_in_grid - 30;
        horizontal_location_in_grid = -100.0f;
    }
 }

}  // namespace myapp
