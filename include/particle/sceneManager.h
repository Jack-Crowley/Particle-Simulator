#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "circle.h"
#include <stdio.h>
#include <vector>

extern std::vector<Circle> circles;

void setCircles(std::vector<Circle> newCircles);

std::vector<Circle>& getCircles();

void addCircles(Circle circle);
void addCircles(std::vector<Circle> newCircles);

#endif