#include <vector>
#include "circle.h"
#include "staticManager.h"
#include "sceneManager.h"
#include <cmath>
#include <stdio.h>

 // Do we need like a centralized list of like circles?



void handle_collision(Circle &circ1, Circle &circ2){
    
    // Do trig stuff
           
    if (circ1.position_cur.x < circ2.position_cur.x){

        // circ1 is left
       
        float xDiff = circ2.position_cur.x - circ1.position_cur.x;
        float yDiff = circ2.position_cur.y - circ1.position_cur.y;

        float distanceBetweenCircles = circ1.getDistance(circ2.position_cur);

        float overlap = circ1.radius + circ2.radius - distanceBetweenCircles;
        if (overlap > 0.001){
            if (debug)
                printf("Dist: (%f)\n",overlap);

            float angleBetweenCircles = atan(yDiff/xDiff);

            float xToShift = cos(angleBetweenCircles) * overlap/2;
            float yToShift = sin(angleBetweenCircles) * overlap/2;

            if (debug) {
                printf("Initial circ1: (%f, %f)\n",circ1.position_cur.x , circ1.position_cur.y);
                printf("Initial circ2: (%f, %f)\n",circ2.position_cur.x , circ2.position_cur.y);
            }

            circ1.shiftX(-xToShift);
            circ2.shiftX(xToShift);

            circ1.shiftY(-yToShift);
            circ2.shiftY(yToShift);

            if (debug) {
                printf("Final circ1: (%f, %f)\n",circ1.position_cur.x , circ1.position_cur.y);
                printf("Final circ2: (%f, %f)\n",circ2.position_cur.x , circ2.position_cur.y);
            }
        }
    }

    
 

}


void find_collisions(){

    // very unoptimized rn

    for (Circle &circ1 : getCircles()){
        if (!circ1.enabled) continue;
        for (Circle &circ2 : getCircles()){
            if (!circ2.enabled) continue;
            if (&circ1 != &circ2){

                handle_collision(circ1, circ2);

            }
        }
    }
}

void detect_obstacles() {
    // for (Obstacle o : currentMap.obstacles) {
    //     for (Circle &circle : getCircles()){ 
    //         Component c = o.getXOfCross(circle);
    //         if (c.x != 0) {
    //             circle.enabled = false;
    //             // Component c1 = o.derivative(circle, c.x, c.y);
    //             // printf("%f, %f\n", c1.x, c1.y);
    //             return;
    //         }
    //     }
    // }
}

void applyGravity(){
    // printf("fall speed: (%f)\n",fallSpeed);
    Component gravity = Component(0.0, -fallSpeed);
    for (Circle &circle : getCircles()) {
        if (!circle.enabled) continue;
        // circle.position_cur.y -= fallSpeed;
        // Maybe there's a better way to synchronize things?
        circle.accelerate(gravity);
        // Can probably have an apply forces method as well later on
    }
}

void applyContraints(){
    Component origin = Component(0.0, 0.0);
    float radius = 300.0;
    for (Circle &circle : getCircles()){
        if (!circle.enabled) continue;
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

void summonForce(Component c){
    for (Circle &circle : getCircles()){
        if (!circle.enabled) continue;
        Component force = Component((c.x-circle.position_cur.x)/3,(c.y - circle.position_cur.y)/3);
        circle.accelerate(force);
    }
}


void update_physics(float dt)
{
    
    // Idk if we want to put this here or if this should go in engine
    
    
    find_collisions();
    applyGravity();
    applyContraints();
    detect_obstacles();
    for (Circle &circle : getCircles()){
        if (!circle.enabled) continue;
        // Maybe there's a better way to synchronize things?
        circle.update(dt);
        // Can probably have an apply forces method as well later on
    }

 
    

}



void update_physics_sub_steps(float dt, int sub_steps)
{
    const float sub_dt = dt / float(sub_steps);
    for (int i{sub_steps};i--;)
    {
        update_physics(sub_dt);
    }


}

void add_particles()
{
    for (Circle circle : getCircles()) {
        
    }
}
