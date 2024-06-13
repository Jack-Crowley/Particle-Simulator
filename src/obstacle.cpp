#include "obstacle.h"
#include "component.h"

Obstacle::Obstacle(int left, int right, GLenum mode, float* (*calculateFunction)(float, int&), Component (*derivativeFunction)(Circle, float, float))
{
    leftLimit = left;
    rightLimit = right;
    lineMode = mode;
    calculate = calculateFunction;
    derivative = derivativeFunction;
}

Component Obstacle::getXOfCross(Circle c)
{
    for (int x = c.position_cur.x-c.radius; x < c.position_cur.x+c.radius; x++) {
        int size;
        float* y = calculate(x, size);
        for (int i = 0; i < size; i++) {
            Component comp = Component((float) x, y[i]);
            if (c.getDistance(comp) < c.radius) {
                return Component(x, y[i]);
            }
        }
    }

    return Component(0,0);
}
