#include "circle.h"
#include "component.h"
#include "color.h"
#include <stdio.h>

Circle::Circle() {
    this->position = Component();
    this->velocity = Component();
    this->acceleration = Component();
    this->jerk = Component();
    this->color = Color(255,255,255);
    this->radius = 10;
}


Circle::Circle(Component pos) {
    this->position = pos;
    this->velocity = Component();
    this->acceleration = Component();
    this->jerk = Component();
    this->color = Color(255,255,255);
    this->radius = 10;
}


Circle::Circle(Component pos, Color c = Color(255,255,255)) {
    this->position = pos;
    this->velocity = Component();
    this->acceleration = Component();
    this->jerk = Component();
    this->color = c;
    this->radius = 10;
}

Circle::Circle(Component pos, Component initalVelocity, Color c = Color(255,255,255)) {
    this->position = pos;
    this->velocity = initalVelocity;
    this->acceleration = Component();
    this->jerk = Component();
    this->color = c;
    this->radius = 10;
}

void Circle::update(){
    // printf("(%f, %f)",position.x , position.y);
}

void Circle::shiftX(float shift){
    this->position = Component(this->position.x+shift,this->position.y); 

}

void Circle::shiftY(float shift){
     this->position = Component(this->position.x,this->position.y + shift); 
}