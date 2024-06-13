#include "sceneManager.h"
#include "circle.h"
#include "GLFW/glfw3.h"
#include <stdio.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>


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

Color colors[7] = {
    Color(1.0f, 0.0f, 0.0f),
    Color(1.0f, 0.5f, 0.0f),
    Color(1.0f, 1.0f, 0.0f),
    Color(0.0f, 1.0f, 0.0f),
    Color(0.0f, 0.0f, 1.0f),
    Color(0.29f, 0.0f, 0.51f),
    Color(0.56f, 0.0f, 1.0f)
};

Color getRandomColor() {
    srand(static_cast<unsigned int>(time(0)));
    int randomIndex = rand() % 7;
    return colors[randomIndex];

}

float* calculateCircleWithRadius200(float x, int& size) {
    float posY = sqrt(pow(250, 2)-pow(x, 2));
    size = 2;
    float* y = new float[size];
    
    // Assign values to the array
    y[0] = posY;
    y[1] = -posY;
    
    return y;

}

float calculateDerivativeOfRadius200(float x, float y) {
    return -x/y;
}

float* calculateUpsidedownParabula(float x, int& size) {
    size = 1;
    float* y = new float[size];
    
    y[0] = pow(x,2)/500-500;
    
    return y;

}

float calculateUpsidedownDerivative(float x, float y) {
    return 2*x/500;
}

void loadMaps()
{
    loadParabola();
}

void spawnCircles() {
    std::vector<Circle> circles{
        Circle(Component(0,0), getRandomColor()),
    };

    setCircles(circles);
}

void loadCircle()
{
    spawnCircles();

    ParticleMap circleMap = ParticleMap("circleMap");
    maps["circleMap"] = circleMap; 

    Obstacle bigCircle = Obstacle(-250, 250, GL_LINE_LOOP, &calculateCircleWithRadius200, &calculateDerivativeOfRadius200);

    circleMap.obstacles.push_back(bigCircle);

    currentMap = circleMap;
}

void loadParabola() {
    spawnCircles();

    ParticleMap circleMap = ParticleMap("circleMap");
    maps["circleMap"] = circleMap; 

    Obstacle parabula = Obstacle(-500, 500, GL_LINE, &calculateUpsidedownParabula, &calculateUpsidedownDerivative);

    circleMap.obstacles.push_back(parabula);

    currentMap = circleMap;
}

void loadNothing() {
    spawnCircles();

    ParticleMap circleMap = ParticleMap("circleMap");
    maps["circleMap"] = circleMap; 

    currentMap = circleMap;
}