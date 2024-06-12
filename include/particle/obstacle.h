#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "GLFW/glfw3.h"

class Obstacle {
public:
    int leftLimit;
    int rightLimit;

    GLenum lineMode;

    float* (*calculate)(float, int&);
    Obstacle(int left, int right, GLenum mode, float* (*calculateFunction)(float, int&));
};

#endif