#include "circle.h"
#include "component.h"
#include "color.h"

Circle::Circle() {
    this->position = Component();
    this->velocity = Component();
    this->acceleration = Component();
    this->jerk = Component();
    this->color = Color(255,255,255);
}

Circle::Circle(Component pos, Color c = Color(255,255,255)) {
    this->position = pos;
    this->velocity = Component();
    this->acceleration = Component();
    this->jerk = Component();
    this->color = c;
}

Circle::Circle(Component pos, Component initalVelocity, Color c = Color(255,255,255)) {
    this->position = pos;
    this->velocity = initalVelocity;
    this->acceleration = Component();
    this->jerk = Component();
    this->color = c;
}