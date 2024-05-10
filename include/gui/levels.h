#ifndef LEVELS_H
#define LEVELS_H

#include <gui/button_interface.h>

class Levels : public ButtonInterface {

private:
    int level_choosen_;

public:
    Levels();
    Levels(std::shared_ptr<SDL2Window> & window_ptr);
    //Levels(int screen_width, int screen_height);
    int mainLoop(void);
    void init(void);


private:
    void buttonAction(int idx);
};
#endif
