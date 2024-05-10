#include "gui/levels.h"
#include "gui/color.h"
#include "utils/constants.h"
#include "utils/vector2D.h"
#include <SDL_events.h>
#include <SDL_timer.h>
#include <iostream>

Levels::Levels(std::shared_ptr<SDL2Window> & window_ptr)
    : ButtonInterface(window_ptr), level_choosen_(0){}

/**
 * The index of the list allow to know which button has been clicked
 * so the correct action will be executed.
 */
void Levels::buttonAction(int idx)
{
    if (idx < 11)
        level_choosen_ = idx + 1;
    else
        go_to_menu_ = true;
}

void Levels::init()
{
    const int nb_buttons{12};
    const int nb_buttons_row{4};
    const int nb_buttons_column{nb_buttons / nb_buttons_row};

    const double button_width = WINDOW_WIDTH/( 2 * nb_buttons_row);
    const double button_height = WINDOW_HEIGHT/(2* nb_buttons_column + 1);

    for (int i{0}; i < nb_buttons; ++i)
    {
        std:: string text;
        if (i + 1 < 10)
            text = "0" + std::to_string(i + 1);
        else
            text = std::to_string(i + 1);

        Button button{
            Vector2D{
                button_width*((i % nb_buttons_row )*2 + 1),
                button_height*((i / nb_buttons_row )*2 + 1)},
            button_width,
            button_height,
            text};

        buttons_.push_back(button);
    }

    Button back_button{
        Vector2D{
            WINDOW_WIDTH/2,
            button_height*((12 / nb_buttons_row )*2 + 0.5)}, // dernier rang
        3 * button_width,
        button_height,
        "Back"};

    buttons_.push_back(back_button);

}

int Levels::mainLoop() {
    this->init();

    while (!this->is_window_closed_) {

        window_ptr_->clearWindow();
        this->pollEvent();

        this->manageKeys();

        this->drawObjects();

        window_ptr_->update();
        window_ptr_->temporisation(50);

        if (go_to_menu_)
        {
            return 0;
        }

        if (level_choosen_ > 0)
            return level_choosen_;
    }
    // The window will be closed
    return -1;
}
