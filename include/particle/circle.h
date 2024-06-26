#ifndef CIRCLE_H
#define CIRCLE_H

#include "component.h"
#include "color.h"

class Circle {
public:
    Component position_cur;
    Component position_old;
    Component velocity;
    Component acceleration;
    Component jerk;
    Color color;
    bool enabled;

    // Idk if we want a changeable radius or if we want them to all be the same size
    // Currently use a radius in physics but can rework that if needed
    float radius;

    Circle();
    Circle(Component pos);
    Circle(Component pos, Color c);
    Circle(Component pos, Component initialVelocity, Color c);

    void update(float dt);
    
    void accelerate(Component acc);

    void shiftX(float shift);
    void shiftY(float shift);

    float getDistance(Component pos);
    float getDistanceOld(Component pos);
};

#endif