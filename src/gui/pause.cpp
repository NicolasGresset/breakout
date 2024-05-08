#include "gui/pause.h"
#include "gui/color.h"
#include "utils/constants.h"
#include "utils/vector2D.h"
#include <SDL_events.h>
#include <SDL_timer.h>
#include <iostream>
#include <string>

Pause::Pause(std::shared_ptr<SDL2Window> & window_ptr, unsigned int score)
    : ButtonInterface(window_ptr), score_(score){}

void Pause::buttonAction(int idx)
{
    switch (idx)
    {
    case 1:
        play_game_ = true;
        break;
    case 2:
        go_to_menu_ = true;
        break;
    case 3:
        is_window_closed_ = true;
        break;
    default: // 0, impossible
        break;
    }
}

void Pause::init()
{
    Button pause_text{Vector2D{WINDOW_WIDTH/2, WINDOW_HEIGHT/6}, WINDOW_WIDTH/2, WINDOW_HEIGHT*3/12,  "PAUSE", false};

    Button play_button{Vector2D{WINDOW_WIDTH*2/12, WINDOW_HEIGHT*6/12},
        WINDOW_WIDTH*2/12, WINDOW_HEIGHT*1.5/12,  "Play"};

    Button menu_button{Vector2D{WINDOW_WIDTH*2/12, WINDOW_HEIGHT*8/12},
        WINDOW_WIDTH*2/12, WINDOW_HEIGHT*1.5/12, "Menu"};

    Button quit_button{Vector2D{WINDOW_WIDTH*2/12, WINDOW_HEIGHT*10/12},
        WINDOW_WIDTH*2/12, WINDOW_HEIGHT*1.5/12, "Quit"};

    Button score_button{Vector2D{WINDOW_WIDTH*3/4, WINDOW_HEIGHT*8/12},
        WINDOW_WIDTH*2/12, WINDOW_HEIGHT*1.5/12, "Score: " + std::to_string(score_),
        false};

    buttons_.push_back(pause_text);
    buttons_.push_back(play_button);
    buttons_.push_back(menu_button);
    buttons_.push_back(quit_button);
    buttons_.push_back(score_button);
}

int Pause::mainLoop() {
    this->init();

    while (!this->is_window_closed_) {

        window_ptr_->clearWindow();
        this->pollEvent();

        this->manageKeys();

        this->drawObjects();

        window_ptr_->update();
        window_ptr_->temporisation(50);

        if (play_game_)
            return 0;

        if (go_to_menu_)
            return 2;
    }
    // The window will be closed
    return 1;
}
