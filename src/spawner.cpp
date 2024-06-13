#include "spawner.h"
#include "sceneManager.h"
#include "circle.h"
#include <math.h>

float pi = atan(1)*4;

float minAngle = -3*pi/4;
float maxAngle = -1*pi/4;

float currentAngle = -1*pi/4;
float currentDirection = -1;

int counterForSpawner = 0;

void spawnCircle()
{
    if (++counterForSpawner < 25) return;

    currentAngle+=pi/12*currentDirection;
    if (currentAngle < minAngle) {
        currentDirection*=-1;
    }
    else if (currentAngle > maxAngle) {
        currentDirection*=-1;
    }

    Circle c(Component(0, 300), getRandomColor());
    c.accelerate(Component(50*cos(currentAngle), 50*sin(currentAngle)));
    addCircles(c);

    counterForSpawner = 0;
}