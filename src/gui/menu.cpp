#include "gui/menu.h"
#include "gui/color.h"
#include "utils/constants.h"
#include "utils/vector2D.h"
#include <SDL_events.h>
#include <SDL_timer.h>
#include <iostream>

Menu::Menu(std::shared_ptr<SDL2Window> & window_ptr)
    : window_ptr_(window_ptr), is_window_closed_(false), play_game_(false){}

void Menu::manageKeys() {
    int nbk;
    const Uint8 *keys = SDL_GetKeyboardState(&nbk);
    if (keys[SDL_SCANCODE_ESCAPE])
        is_window_closed_ = true;
}

void Menu::pollEvent() {
    SDL_Event event;
    while (!is_window_closed_ && SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            is_window_closed_ = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            checkButtonClicked(true);
            break;
        case SDL_MOUSEMOTION:
            checkButtonClicked(false);
            break;
        default:
            break;
        }
    }
    return;
}


void Menu::checkButtonClicked(bool click)
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    int n = static_cast<int>(buttons_.size());

    for (int i = 0; i < n; i++)
    {
        if (buttons_[i].isClickable() && buttons_[i].isClicked(mouseX, mouseY))
        {
            if (click)
                buttonAction(i);
            else
                buttons_[i].setColor({0x00, 0x00, 0xFF, 0x00});

        }
        else
        {
            buttons_[i].setColor({0xFF, 0xFF, 0xFF, 0xFF});
        }
    }
}

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
        play_game_ = true;
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
    Button breakout_text{Vector2D{WINDOW_WIDTH/2, WINDOW_HEIGHT/6}, WINDOW_WIDTH/2, WINDOW_HEIGHT*3/12,
                         { 0xFF, 0xFF, 0xFF, 0xFF }, "BREAKOUT", false};

    Button play_button{Vector2D{WINDOW_WIDTH/2, WINDOW_HEIGHT*6/12},
        WINDOW_WIDTH*2/12, WINDOW_HEIGHT*1.5/12, { 0xFF, 0xFF, 0xFF, 0xFF }, "Play"};

    Button levels_button{Vector2D{WINDOW_WIDTH/2, WINDOW_HEIGHT*8/12},
        WINDOW_WIDTH*2/12, WINDOW_HEIGHT*1.5/12, { 0xFF, 0xFF, 0xFF, 0xFF }, "Levels"};

    Button quit_button{Vector2D{WINDOW_WIDTH/2, WINDOW_HEIGHT*10/12},
        WINDOW_WIDTH*2/12, WINDOW_HEIGHT*1.5/12, { 0xFF, 0xFF, 0xFF, 0xFF }, "Quit"};


    buttons_.push_back(breakout_text);
    buttons_.push_back(play_button);
    buttons_.push_back(levels_button);
    buttons_.push_back(quit_button);
}

void Menu::drawObjects()
{
    for (auto button : buttons_)
    {
        button.draw(window_ptr_->getRenderer());
    }
}

int Menu::mainLoop() {
    this->init();

    while (!is_window_closed_) {
        clock_.tick(); // update the time elapsed since last frame
        window_ptr_->clearWindow();
        this->pollEvent();
        this->manageKeys();

        drawObjects();

        window_ptr_->update();
        window_ptr_->temporisation(50);

        if (play_game_)
        {
            return 0;
        }
    }
    // The window will be closed
    return 1;
}
