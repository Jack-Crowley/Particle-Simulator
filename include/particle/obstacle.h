#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "GLFW/glfw3.h"
#include "circle.h"

class Obstacle {
public:
    int leftLimit;
    int rightLimit;

    GLenum lineMode;

    float* (*calculate)(float, int&);
    Component (*derivative)(Circle, float, float);
    Obstacle(int left, int right, GLenum mode, float* (*calculateFunction)(float, int&), Component (*derivativeFunction)(Circle, float, float));

    Component getXOfCross(Circle c);
};

#endif