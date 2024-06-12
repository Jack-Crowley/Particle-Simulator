#include <vector>
#include "circle.h"






void handle_collision(Circle &circ1, Circle &circ2);


void find_collisions(std::vector<Circle> &circles);

void applyGravity(std::vector<Circle> &circles);

void applyConstraints(std::vector<Circle> &circles);

void update_physics(float dt, std::vector<Circle> &circles);



void update_physics_sub_steps(float dt, int sub_steps, std::vector<Circle>& circles);