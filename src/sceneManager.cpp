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


float* calculateCircleWithRadius200(float x, int& size) {
    float posY = sqrt(pow(250, 2)-pow(x, 2));
    size = 2;
    float* y = new float[size];
    
    // Assign values to the array
    y[0] = posY;
    y[1] = -posY;
    
    return y;

}

float dotProduct(const Component& v1, const Component& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

Component reflect(const Component& v, const Component& n) {
    float dot = dotProduct(v, n);
    return Component(
        v.x - 2 * dot * n.x,
        v.y - 2 * dot * n.y
    );
}

Component normalize(const Component& v) {
    float magnitude = std::sqrt(v.x * v.x + v.y * v.y);
    return Component(v.x / magnitude, v.y / magnitude);
}

// Function to create a normal vector from a slope
Component normalFromSlope(float slope) {
    // A normal vector to the line with slope can be (-slope, 1) or (slope, -1)
    return normalize(Component(-slope, 1));
}

Component calculateDerivativeOfRadius200(Circle c, float x, float y) {
    Component vector(x-c.position_cur.x, y-c.position_cur.y);
    float slopeOfLine = -x/y;
    printf("(%f, %f)\n", x, y);

    Component normal = normalFromSlope(slopeOfLine);
    Component reflected = reflect(vector, normal);

    return reflected;
}

void loadMaps()
{
    ParticleMap circleMap = ParticleMap("circleMap");
    maps["circleMap"] = circleMap; 

    Obstacle bigCircle = Obstacle(-250, 250, GL_LINE_LOOP, &calculateCircleWithRadius200, &calculateDerivativeOfRadius200);

    circleMap.obstacles.push_back(bigCircle);

    currentMap = circleMap;
}
