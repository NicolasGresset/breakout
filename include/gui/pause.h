#ifndef PAUSE_H
#define PAUSE_H

#include "button.h"
#include <gui/button_interface.h>
#include "utils/clock.h"
#include "gui/SDL2Window.h"
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_timer.h>
#include <memory>
#include <vector>

class Pause : public ButtonInterface {

private:
    const unsigned int score_;
    bool go_to_menu_{false};
public:
    Pause();
    Pause(std::shared_ptr<SDL2Window> & window_ptr, const unsigned int score);
    //Pause(int screen_width, int screen_height);
    int mainLoop(void);
    void init(void);
private:
    void buttonAction(int idx);
};
#endif
