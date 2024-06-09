#ifndef CIRCLE_H
#define CIRCLE_H

#include "component.h"
#include "color.h"

class Circle {
public:
    Component position;
    Component velocity;
    Component acceleration;
    Component jerk;
    Color color;

    Circle();
    Circle(Component pos, Color c);
    Circle(Component pos, Component initialVelocity, Color c);
};

#endif