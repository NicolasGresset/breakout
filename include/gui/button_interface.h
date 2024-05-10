#ifndef BUTTON_INTERFACE_H
#define BUTTON_INTERFACE_H

#include "button.h"
#include "utils/utils.h"
#include "gui/SDL2Window.h"
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_timer.h>
#include <memory>
#include <vector>


class ButtonInterface {
protected:
    std::shared_ptr<SDL2Window> window_ptr_;

    bool is_window_closed_;
    bool play_game_;
    bool go_to_menu_;

    void manageKeys(void);
    void pollEvent(void);

    std::vector<Button> buttons_;

    std::shared_ptr<Assets> assets_;

public:
    ButtonInterface();
    ButtonInterface(std::shared_ptr<SDL2Window> & window_ptr);

    virtual int mainLoop(void) = 0;
    virtual void init(void) = 0;
protected:
    void checkButtonClicked(bool click);
    virtual void buttonAction(int idx) = 0;
    void drawObjects();
};
#endif
