#ifndef BUTTON_H
#define BUTTON_H

#include "vector2D.h"
#include "object.h"
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <string>
#include "assets.h"

class Button : public Object {

private:
    SDL_Color color_;
    double width_;
    double height_;
    std::string text_;
public:

    //Button();
    Button(Vector2D position = Vector2D{0, 0},
           SDL_Color color = { 0xFF, 0xFF, 0xFF, 0xFF },
           double width = 150,
           double height = 50,
           std::string text = "BREAKOUT");
    /*
      Returns the 2DVector corresopnding to the coordinates of the upper left corner
      of the rectangle
    */
    inline Vector2D toUpperLeftCoords() const {
        return Vector2D(position_.x_ - width_ / 2,
                        position_.y_ - height_ / 2);
    }

    void draw(SDL_Renderer *renderer) const override;
};

#endif