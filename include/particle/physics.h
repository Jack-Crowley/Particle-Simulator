#include <vector>
#include "circle.h"
#include "component.h"






void handle_collision(Circle &circ1, Circle &circ2);


void find_collisions();

void applyGravity();

void applyConstraints();

void oldApplyConstraints();

void update_physics(float dt);

void createCircle(Component c);

void summonForceTowards(Component c);

void summonForceOn(Component c, Circle &circ);

void update_physics_sub_steps(float dt, int sub_steps);