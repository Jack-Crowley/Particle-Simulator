#include "obstacle.h"
#include "component.h"
#include "stdio.h"

Obstacle::Obstacle(int left, int right, GLenum mode, float* (*calculateFunction)(float, int&), float (*derivativeFunction)(float, float))
{
    leftLimit = left;
    rightLimit = right;
    lineMode = mode;
    calculate = calculateFunction;
    derivative = derivativeFunction;
}

Component Obstacle::getXOfCross(Circle c)
{
    float closest = 100000;
    for (float x = c.position_old.x-c.radius; x < c.position_old.x+c.radius; x+=.1) {
        int size;
        float* y = calculate(x, size);
        for (int i = 0; i < size; i++) {
            Component comp = Component((float) x, y[i]);
            if (c.getDistanceOld(comp) < closest) {
                closest = c.getDistanceOld(comp);
            }
            if (c.getDistanceOld(comp) < c.radius) {
                return Component(x, y[i]);
            }
        }
    }

    return Component(5000,0);
}
