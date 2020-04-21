// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include "../src/board.h"


#include <cinder/app/App.h>
#include <cinder/Text.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <string>
#include <iostream>
#include<string>



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

    const char kNormalFont[] = "Arial Unicode MS";


MyApp::MyApp() { }

void MyApp::setup() {
    //background picture
    texture = cinder::gl::Texture2d::create( loadImage(loadAsset("backg.jpg")));
}

void MyApp::update() { }

void MyApp::draw() {
    cinder::gl::color(Color::white());
    cinder::gl::draw(texture, getWindowBounds());
    DrawBoard();
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

template <typename C>
void PrintBackground(const C& color, const cinder::ivec2& size) {
    cinder::gl::color(color);
    cinder::gl::drawStrokedRect( Rectf( cinder::app::getWindowWidth()/2-350.0f,
                                      cinder::app::getWindowHeight()/2-350.0f,
                                      cinder::app::getWindowWidth()/2-30.0f,
                                      cinder::app::getWindowHeight()/2-30.0f ) );
    size_t row = 0;
    PrintText("Computer", color, size, {cinder::app::getWindowCenter().x + (++row) * 180, cinder::app::getWindowCenter().y + (++row) * 30});
    PrintText("User", color, size, {cinder::app::getWindowWidth() /2 - 180.0f, cinder::app::getWindowHeight() / 2-325.0f});

    cinder::gl::drawStrokedRect( Rectf( cinder::app::getWindowWidth()/2+30.0f,
                                        cinder::app::getWindowHeight()/2+30.0f,
                                        cinder::app::getWindowWidth()/2+350.0f,
                                        cinder::app::getWindowHeight()/2+350.0f ) );
}

void MyApp::DrawBoard() {
        // Lazily print.

        const cinder::vec2 center = getWindowCenter();
        const cinder::ivec2 size = {500, 50};
        const Color color = Color::white();

        size_t row = 0;
        PrintText("~Battleship~", color, size, center);
        PrintBackground(color, size);
        PrintBoard();
}

void MyApp::PrintBoard() {
    int width = 8;
    int height = 8;
    Board* board = new Board(width, height);
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {50, 50};
    const Color color = Color::white();
    int horizontal_width_numbering = 270.0f;
    for (int i{0}; i < width; i++) {
        string str= std::to_string(i);
        PrintText(str, color, size, {cinder::app::getWindowWidth() /2 - horizontal_width_numbering, cinder::app::getWindowHeight() / 2 - 290.0f});
        horizontal_width_numbering = horizontal_width_numbering - 30;
    }
    int horizontal_counters = 270.0f;
    int vertical_counters = 250.0f;
    for (int row{0}; row < height; row++) {
        string str= std::to_string(row);
        PrintText(str, color, size, {cinder::app::getWindowWidth() /2 - horizontal_counters - 40, cinder::app::getWindowHeight() / 2-vertical_counters});
        for (int col{0}; col < width; col++) {
            PrintText(board->grid[col][row], color, size, {cinder::app::getWindowWidth() /2 - horizontal_counters, cinder::app::getWindowHeight() / 2 - vertical_counters});
            horizontal_counters = horizontal_counters - 30;
        }
        vertical_counters = vertical_counters - 30;
        horizontal_counters = 270.0f;
    }
}

}  // namespace myapp
