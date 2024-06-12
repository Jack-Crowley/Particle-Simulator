#include "sceneManager.h"
#include "circle.h"
#include <stdio.h>
#include <vector>

std::vector<Circle> circles;

void setCircles(std::vector<Circle> newCircles) {
    circles = newCircles;
}

std::vector<Circle>& getCircles() {
    return circles;
}


void addCircles(Circle circle) {
    circles.push_back(circle);
}

void addCircles(std::vector<Circle> newCircles) {
    for (Circle c : newCircles) {
        circles.push_back(c);
    }
}