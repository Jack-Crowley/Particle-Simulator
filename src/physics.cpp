#include <vector>
#include "circle.h"
#include "staticManager.h"
#include "sceneManager.h"
#include <cmath>
#include <stdio.h>
#include "physics.h"
#include "partition.h"

// Do we need like a centralized list of like circles?

void handle_collision(Circle &circ1, Circle &circ2)
{

    // Do trig stuff

    if (circ1.position_cur.x < circ2.position_cur.x)
    {

        // circ1 is left

        float xDiff = circ2.position_cur.x - circ1.position_cur.x;
        float yDiff = circ2.position_cur.y - circ1.position_cur.y;

        float distanceBetweenCircles = circ1.getDistance(circ2.position_cur);

        float overlap = circ1.radius + circ2.radius - distanceBetweenCircles;
        if (overlap > 0.001)
        {
            if (debug)
                printf("Dist: (%f)\n", overlap);

            float angleBetweenCircles = atan(yDiff / xDiff);

            float xToShift = cos(angleBetweenCircles) * overlap / 2;
            float yToShift = sin(angleBetweenCircles) * overlap / 2;

            if (debug)
            {
                printf("Initial circ1: (%f, %f)\n", circ1.position_cur.x, circ1.position_cur.y);
                printf("Initial circ2: (%f, %f)\n", circ2.position_cur.x, circ2.position_cur.y);
            }

            circ1.shiftX(-xToShift);
            circ2.shiftX(xToShift);

            circ1.shiftY(-yToShift);
            circ2.shiftY(yToShift);

            if (debug)
            {
                printf("Final circ1: (%f, %f)\n", circ1.position_cur.x, circ1.position_cur.y);
                printf("Final circ2: (%f, %f)\n", circ2.position_cur.x, circ2.position_cur.y);
            }
           
          
            if (circlesRepel){
              
                summonForceOn(Component(repel_magnitude * xDiff/distanceBetweenCircles,repel_magnitude * yDiff/distanceBetweenCircles), circ1);
                summonForceOn(Component(-1*repel_magnitude * xDiff/distanceBetweenCircles,-1*repel_magnitude * yDiff/distanceBetweenCircles), circ2);
            }
        
        }

    }
}

void find_collisions()
{

    Grid grid(1280, 720, getCircles()[0].radius);
    grid.populateGrid(getCircles());

    for (Circle &circ1 : getCircles())
    {
        // if (!circ1.enabled)
        //     continue;
        std::vector<GridCell> checkCells = grid.getNeighborCells(circ1);

        //for (Circle &circ2 : getCircles())
        for (GridCell &cell : checkCells)
        {
            for (Circle &circ2 : cell.getCircles()) {
                // if (!circ2.enabled)
                //     continue;
                if (&circ1 != &circ2)
                {

                    handle_collision(circ1, circ2);
                }
            }
        }
    }
}

void detect_obstacles()
{
    for (Obstacle o : currentMap.obstacles)
    {
        for (Circle &circle : getCircles())
        {
            if (!circle.enabled)
                continue;

            Component c = o.getXOfCross(circle);
            if (c.x != 5000)
            {
                double angleRadians = atan2(c.y - circle.position_old.y, c.x - circle.position_old.x);

                // Incident vector (angle in standard position)
                double I_x = cos(angleRadians);
                double I_y = sin(angleRadians);

                // Normal vector to the surface
                double N_x = -o.derivative(c.x, c.y);
                double N_y = 1.0;

                // Normalize the normal vector
                double norm = sqrt(N_x * N_x + N_y * N_y);
                N_x /= norm;
                N_y /= norm;

                // Dot product I . N
                double dotProduct = I_x * N_x + I_y * N_y;

                // Reflection vector calculation
                double R_x = I_x - 2 * dotProduct * N_x;
                double R_y = I_y - 2 * dotProduct * N_y;
                R_y *= fallSpeed;

                circle.position_old.set(circle.position_cur);

            
                circle.accelerate(Component(R_x / 100, R_y / 100));

                double divisor = sqrt(pow(R_x, 2) + pow(R_y, 2));
                double d = circle.getDistance(c) * 10;
                double unitVectorX = (circle.position_cur.x - c.x) / d;
                double unitVectorY = (circle.position_cur.y - c.y) / d;

                circle.shiftX(unitVectorX);
                circle.shiftY(unitVectorY);

                double d1 = circle.getDistance(c) * 100;
                double newX = (circle.position_cur.x + c.x) / d1;
                double newY = (circle.position_cur.y + c.y) / d1;

                circle.position_old.set(circle.position_cur);
                circle.position_old.x += newX;
                circle.position_old.y += newY;
            }
        }
    }
}

void applyGravity()
{
    // printf("fall speed: (%f)\n",fallSpeed);
    Component gravity = Component(0.0, -fallSpeed);
    for (Circle &circle : getCircles())
    {
        if (!circle.enabled)
            continue;
        // circle.position_cur.y -= fallSpeed;
        // Maybe there's a better way to synchronize things?
        circle.accelerate(gravity);
        // Can probably have an apply forces method as well later on
    }
}

void applyContraints()
{
    for (Circle &circle : getCircles())
    {
        if (!circle.enabled)
            continue;

        if (circle.position_cur.x < -491)
        {
            circle.position_cur = Component(-491,circle.position_cur.y);
        }
        if (circle.position_cur.x > 491)
        {
            circle.position_cur = Component(491,circle.position_cur.y);
        }

        if (circle.position_cur.y < -491)
        {
            circle.position_cur = Component(circle.position_cur.x,-491);
        }
        if (circle.position_cur.y > 450)
        {
            circle.position_cur = Component(circle.position_cur.x,450);
        }
    }
}


void oldApplyConstraints(){
    Component origin = Component(0.0, 0.0);
    float radius = 240.0;
    for (Circle &circle : getCircles()){
        // Maybe there's a better way to synchronize things?
        Component to_obj = Component(circle.position_cur.x - origin.x, circle.position_cur.y - origin.y);

        float dist = sqrt(to_obj.x*to_obj.x +  to_obj.y*to_obj.y);
        // printf("Final circ2: (%f)\n",dist);
        if (dist > radius){

            // Component n = Component(to_obj.x/dist, to_obj.y/dist);
            // circle.position_cur = Component(circle.position_cur.x + n.x*(dist-50.0f),circle.position_cur.y + n.y*(dist-50.0f));
            circle.position_cur = Component(circle.position_cur.x *radius/dist, circle.position_cur.y *radius/dist);
        }
        // Can probably have an apply forces method as well later on
    }

}

void summonForceOn(Component c, Circle &circle){
    
    Component force = Component(c.x,c.y);
    circle.accelerate(force);
    // printf("Force at: (%f, %f)\n",force.x , force.y);
}

void summonForceTowards(Component c){
    for (Circle &circle : getCircles()){
        // if (!circle.enabled) continue;
        Component force = Component((c.x-circle.position_cur.x),(c.y - circle.position_cur.y));
        summonForceOn(force, circle);
      
    }
}




void update_physics(float dt)
{

    // Idk if we want to put this here or if this should go in engine

    find_collisions();
    applyGravity();
    if (oldConstraints){
        oldApplyConstraints();
    }
    else{
        applyContraints();
        detect_obstacles();
    }
    for (Circle &circle : getCircles())
    {
        if (!circle.enabled)
            continue;
        // Maybe there's a better way to synchronize things?
        circle.update(dt);
        // Can probably have an apply forces method as well later on
    }
}

void update_physics_sub_steps(float dt, int sub_steps)
{
    const float sub_dt = dt / float(sub_steps);
    for (int i{sub_steps}; i--;)
    {
        update_physics(sub_dt);
    }
}

void add_particles()
{
    for (Circle circle : getCircles())
    {
    }
}
