#ifndef MENU_H
#define MENU_H

#include "button.h"
#include "utils/clock.h"
#include "gui/SDL2Window.h"
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_timer.h>
#include <memory>
#include <vector>

class Menu {
private:
    std::shared_ptr<SDL2Window> window_ptr_;

    bool is_window_closed_;
    bool play_game_;

    void manageKeys(void);
    void pollEvent(void);

    std::vector<Button> buttons_;

    Clock clock_;
    std::shared_ptr<Assets> assets_;

public:
    Menu();
    Menu(std::shared_ptr<SDL2Window> & window_ptr);
    //Menu(int screen_width, int screen_height);
    int mainLoop(void);
    void init(void);
private:
    void checkButtonClicked();
    void buttonAction(int idx);
};
#endif
