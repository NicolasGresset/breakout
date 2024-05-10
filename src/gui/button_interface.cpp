#include "gui/button_interface.h"
#include "gui/color.h"
#include "utils/constants.h"
#include "utils/vector2D.h"
#include <SDL_events.h>
#include <SDL_timer.h>
#include <iostream>
#include <ctime>

ButtonInterface::ButtonInterface(std::shared_ptr<SDL2Window> & window_ptr)
    : window_ptr_(window_ptr), is_window_closed_(false),
      play_game_(false), go_to_menu_(false){}

void ButtonInterface::manageKeys() {
    int nbk;
    const Uint8 *keys = SDL_GetKeyboardState(&nbk);
    if (keys[SDL_SCANCODE_A])
        is_window_closed_ = true;
}

void ButtonInterface::pollEvent() {
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


void ButtonInterface::checkButtonClicked(bool click)
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

void ButtonInterface::drawObjects()
{
    // Create noise
    const int nb_points = 1000;
    SDL_Point points[nb_points];
    srand(time(0));
    // Loop to draw 100 random dots
    for (int i = 0; i < nb_points; ++i) {
        // Generate random x and y coordinates within window bounds
        points[i].x = rand() % WINDOW_WIDTH;
        points[i].y = rand() % WINDOW_HEIGHT;

    }
    CHECK_SDL_RETURN_CODE(
        SDL_SetRenderDrawColor(&window_ptr_->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF) < 0);
    CHECK_SDL_RETURN_CODE(SDL_RenderDrawPoints(&window_ptr_->getRenderer(), points, nb_points) < 0);
    CHECK_SDL_RETURN_CODE(
        SDL_SetRenderDrawColor(&window_ptr_->getRenderer(), 0x00, 0x00, 0x00, 0xFF) < 0);

    for (auto button : buttons_)
    {
        button.draw(window_ptr_->getRenderer());
    }
}
