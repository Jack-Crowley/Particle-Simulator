#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "circle.h"
#include "ParticleMap.h"
#include <stdio.h>
#include <vector>
#include <map>

extern std::map<std::string, ParticleMap> maps;
extern ParticleMap currentMap;

extern std::vector<Circle> circles;

void setCircles(std::vector<Circle> &newCircles);

std::vector<Circle>& getCircles();

void addCircles(Circle &circle);
void addCircles(std::vector<Circle> &newCircles);

void loadMaps();

#endif