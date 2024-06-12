#include <vector>
#include "circle.h"
#include "component.h"






void handle_collision(Circle &circ1, Circle &circ2);


void find_collisions();

void applyGravity();

void applyConstraints();

void update_physics(float dt);

void summonForce(Component c);



void update_physics_sub_steps(float dt, int sub_steps);