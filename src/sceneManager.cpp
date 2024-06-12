#include "sceneManager.h"
#include "circle.h"
#include "GLFW/glfw3.h"
#include <stdio.h>
#include <cmath>
#include <vector>

std::vector<Circle> circles;
std::map<std::string, ParticleMap> maps;
ParticleMap currentMap("default");

void setCircles(std::vector<Circle> &newCircles) {
    circles = newCircles;
}

std::vector<Circle>& getCircles() {
    return circles;
}


void addCircles(Circle &circle) {
    circles.push_back(circle);
}

void addCircles(std::vector<Circle> &newCircles) {
    for (Circle &c : newCircles) {
        circles.push_back(c);
    }
}


// Map Creation Stuff


float* calculateCircleWithRadius200(float x, int& size) {
    float posY = sqrt(pow(250, 2)-pow(x, 2));
    size = 2;
    float* y = new float[size];
    
    // Assign values to the array
    y[0] = posY;
    y[1] = -posY;
    
    return y;

}

void loadMaps()
{
    ParticleMap circleMap = ParticleMap("circleMap");
    maps["circleMap"] = circleMap; 

    Obstacle bigCircle = Obstacle(-250, 250, GL_LINE_LOOP, &calculateCircleWithRadius200);

    circleMap.obstacles.push_back(bigCircle);

    currentMap = circleMap;
}
