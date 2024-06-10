#include "circle.h"
#include "component.h"
#include "color.h"

Circle::Circle() {
    this->position = Component();
    this->velocity = Component();
    this->acceleration = Component();
    this->jerk = Component();
    this->color = Color(255,255,255);
    this->radius = 0.5;
}


Circle::Circle(Component pos) {
    this->position = pos;
    this->velocity = Component();
    this->acceleration = Component();
    this->jerk = Component();
    this->color = Color(255,255,255);
    this->radius = 0.5;
}


Circle::Circle(Component pos, Color c = Color(255,255,255)) {
    this->position = pos;
    this->velocity = Component();
    this->acceleration = Component();
    this->jerk = Component();
    this->color = c;
    this->radius = 0.5;
}

Circle::Circle(Component pos, Component initalVelocity, Color c = Color(255,255,255)) {
    this->position = pos;
    this->velocity = initalVelocity;
    this->acceleration = Component();
    this->jerk = Component();
    this->color = c;
    this->radius = 0.5;
}

void Circle::update(){

}