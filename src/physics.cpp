#include <vector>
#include "circle.h"
#include <cmath>
#include <stdio.h>

 // Do we need like a centralized list of like circles?



void handle_collision(Circle &circ1, Circle &circ2){
    
    // Do trig stuff
           
    if (circ1.position.x < circ2.position.x){

        // circ1 is left
       
        float xDiff = circ2.position.x - circ1.position.x;
        float yDiff = circ2.position.y - circ1.position.y;

        float distanceBetweenCircles = sqrt(xDiff*xDiff + yDiff*yDiff);
       

        float overlap = circ1.radius + circ2.radius - distanceBetweenCircles;

        if (overlap > 0){
            printf("Dist: (%f)\n",overlap);
            float angleBetweenCircles = atan(yDiff/xDiff);

            float xToShift = cos(angleBetweenCircles) * overlap/2;
            float yToShift = sin(angleBetweenCircles) * overlap/2;

            printf("Initial circ1: (%f, %f)\n",circ1.position.x , circ1.position.y);
            printf("Initial circ2: (%f, %f)\n",circ2.position.x , circ2.position.y);
            circ1.shiftX(-xToShift);
            circ2.shiftX(xToShift);

            circ1.shiftY(-yToShift);
            circ2.shiftY(yToShift);

            printf("Final circ1: (%f, %f)\n",circ1.position.x , circ1.position.y);
            printf("Final circ2: (%f, %f)\n",circ2.position.x , circ2.position.y);
        }
    }

    
 

}


void find_collisions(std::vector<Circle> &circles){

    // very unoptimized rn

    for (Circle &circ1 : circles){
        for (Circle &circ2 : circles){
            if (&circ1 != &circ2){

                handle_collision(circ1, circ2);

            }
        }
    }
}

void update_physics(float dt, std::vector<Circle> &circles)
{
    
    // Idk if we want to put this here or if this should go in engine
    
    
    find_collisions(circles);
    for (Circle circle : circles){
        // Maybe there's a better way to synchronize things?
        circle.update();
        // Can probably have an apply forces method as well later on
    }

 
    

}



void update_physics_sub_steps(float dt, int sub_steps, std::vector<Circle> &circles)
{
    const float sub_dt = dt / float(sub_steps);
    for (int i{sub_steps};i--;)
    {
        update_physics(sub_dt, circles);
    }


}

void add_particles(std::vector<Circle> circles)
{
    for (Circle circle : circles) {
        
    }
}
