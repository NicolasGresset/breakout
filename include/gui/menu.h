#ifndef MENU_H
#define MENU_H

#include <gui/button_interface.h>

class Menu : public ButtonInterface {

private:
    bool levels_;
public:
    Menu();
    Menu(std::shared_ptr<SDL2Window> & window_ptr);
    //Menu(int screen_width, int screen_height);

    /**
     * returns 0 when the button play is clicked,
     *         1 when it is the quit button
     *         2 when it is the level button
     */
    int mainLoop(void);
    void init(void);


private:
    void buttonAction(int idx);
};
#endif
