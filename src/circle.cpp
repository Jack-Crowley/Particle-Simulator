#include "circle.h"
#include "component.h"
#include "color.h"
#include <math.h>
#include <stdio.h>

Circle::Circle() {
    this->position_cur = Component();
    this->position_old = Component();
    this->velocity = Component();
    this->acceleration = Component();
    this->jerk = Component();
    this->color = Color(255,255,255);
    this->radius = 10;
}


Circle::Circle(Component pos) {
    this->position_cur = pos;
    this->position_old = pos;
    this->velocity = Component();
    this->acceleration = Component();
    this->jerk = Component();
    this->color = Color(255,255,255);
    this->radius = 10;
}


Circle::Circle(Component pos, Color c = Color(255,255,255)) {
    this->position_cur = pos;
    this->position_old = pos;
    this->velocity = Component();
    this->acceleration = Component();
    this->jerk = Component();
    this->color = c;
    this->radius = 10;
}

Circle::Circle(Component pos, Component initalVelocity, Color c = Color(255,255,255)) {
    this->position_cur = pos;
    this->position_old = pos;
    this->velocity = initalVelocity;
    this->acceleration = Component();
    this->jerk = Component();
    this->color = c;
    this->radius = 10;
}

void Circle::update(float dt){
    //printf("(%f, %f)",position_cur.x , position_cur.y);
    velocity = Component(position_cur.x-position_old.x, position_cur.y-position_old.y);

    position_old = position_cur;

    position_cur = Component(position_cur.x+velocity.x+acceleration.x*dt*dt,position_cur.y+velocity.y+acceleration.y*dt*dt);

    acceleration = Component();
}

void Circle::accelerate(Component acc){

    acceleration = Component(acc.x+acceleration.x, acc.y+acceleration.y);
}

void Circle::shiftX(float shift){
    this->position_cur = Component(this->position_cur.x+shift,this->position_cur.y); 

}

void Circle::shiftY(float shift){
     this->position_cur = Component(this->position_cur.x,this->position_cur.y + shift); 
}

float Circle::getDistance(Component pos) {
    return sqrt(pow(position_cur.x - pos.x, 2) + pow(position_cur.y - pos.y, 2));
}
