#include "color.h"

Color::Color(float r, float g, float b) {
    this->red = r;
    this->green = g;
    this->blue = b;
}

Color::Color() {
    this->red = 0;
    this->green = 0;
    this->blue = 0;
}