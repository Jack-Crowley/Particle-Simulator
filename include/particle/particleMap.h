#ifndef PARTICLE_MAP_H
#define PARTICLE_MAP_H

#include <string>
#include <vector>
#include "obstacle.h"

class ParticleMap {
public:
    std::vector<Obstacle> obstacles;
    std::string name;

    ParticleMap();
    ParticleMap(std::string n);
};

#endif