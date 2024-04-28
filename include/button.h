#ifndef BUTTON_H
#define BUTTON_H

#include "utils/vector2D.h"
#include "object/object.h"
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <string>
#include "gui/assets.h"

class Button : public Object {

private:
    SDL_Color color_;
    double width_;
    double height_;
    std::string text_;
public:

    //Button();
    Button(Vector2D position = Vector2D{0, 0},
           double width = 150,
           double height = 50,
           SDL_Color color = { 0xFF, 0xFF, 0xFF, 0xFF },
           std::string text = "BREAKOUT");

    bool isClicked(int mouseX, int mouseY);

/*
      Returns the 2DVector corresopnding to the coordinates of the upper left corner
      of the rectangle
    */
    inline Vector2D toUpperLeftCoords() const override{
        return Vector2D(position_.x_ - width_ / 2,
                        position_.y_ - height_ / 2);
    }

    void draw(SDL_Renderer &renderer) const override;
};

#endif
