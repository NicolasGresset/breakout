#ifndef MENU_H
#define MENU_H

#include "button.h"
#include <gui/button_interface.h>
#include "utils/clock.h"
#include "gui/SDL2Window.h"
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_timer.h>
#include <memory>
#include <vector>

class Menu : public ButtonInterface {

public:
    Menu();
    Menu(std::shared_ptr<SDL2Window> & window_ptr);
    //Menu(int screen_width, int screen_height);
    int mainLoop(void);
    void init(void);


private:
    void buttonAction(int idx);
};
#endif
