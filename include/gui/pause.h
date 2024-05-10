#ifndef PAUSE_H
#define PAUSE_H

#include <gui/button_interface.h>

class Pause : public ButtonInterface {

private:
    const unsigned int score_;

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
