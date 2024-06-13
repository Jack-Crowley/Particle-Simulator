#include "component.h"

Component::Component(float x1, float y1) {
    this->x = x1;
    this->y = y1;
}

void Component::set(Component comp)
{
    x = comp.x;
    y = comp.y;
}

void Component::cap(float maxValue)
{
    if (y > maxValue) {
        y = maxValue;
    }
    if (x > maxValue) {
        x = maxValue;
    }
}

Component::Component() {
    this->x = 0;
    this->y = 0;
}

