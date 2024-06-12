#include "circle.h"
#include <stdio.h>
#include <vector>

static std::vector<Circle> circles;

void setCircles(std::vector<Circle> newCircles);

std::vector<Circle> getCircles();

void addCircles(Circle circle);
void addCircles(std::vector<Circle> newCircles);