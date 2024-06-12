#include "obstacle.h"

Obstacle::Obstacle(int left, int right, GLenum mode, float* (*calculateFunction)(float, int&))
{
    leftLimit = left;
    rightLimit = right;
    lineMode = mode;
    calculate = calculateFunction;
}
