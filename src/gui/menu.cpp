#include "gui/menu.h"
#include "gui/color.h"
#include "utils/constants.h"
#include "utils/vector2D.h"
#include <SDL_events.h>
#include <SDL_timer.h>
#include <iostream>

Menu::Menu(std::shared_ptr<SDL2Window> & window_ptr)
    : ButtonInterface(window_ptr), levels_(false){}

/**
 * The index of the list allow to know which button has been clicked
 * so the correct action will be executed.
 */
void Menu::buttonAction(int idx)
{
    switch (idx)
    {
    case 1:
        play_game_ = true;
        break;
    case 2:
        levels_ = true;
        break;
    case 3:
        is_window_closed_ = true;
        break;
    default: // 0, impossible
        break;
    }
}

void Menu::init()
{
    Button breakout_text{Vector2D{WINDOW_WIDTH/2, WINDOW_HEIGHT/6}, WINDOW_WIDTH/2, WINDOW_HEIGHT*3/12,  "BREAKOUT", false};

    Button play_button{Vector2D{WINDOW_WIDTH/2, WINDOW_HEIGHT*6/12},
        WINDOW_WIDTH*2/12, WINDOW_HEIGHT*1.5/12,  "Play"};

    Button levels_button{Vector2D{WINDOW_WIDTH/2, WINDOW_HEIGHT*8/12},
        WINDOW_WIDTH*2/12, WINDOW_HEIGHT*1.5/12, "Levels"};

    Button quit_button{Vector2D{WINDOW_WIDTH/2, WINDOW_HEIGHT*10/12},
        WINDOW_WIDTH*2/12, WINDOW_HEIGHT*1.5/12, "Quit"};


    buttons_.push_back(breakout_text);
    buttons_.push_back(play_button);
    buttons_.push_back(levels_button);
    buttons_.push_back(quit_button);
}

int Menu::mainLoop() {
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

        if (levels_)
            return 2;
    }
    // The window will be closed
    return 1;
}
