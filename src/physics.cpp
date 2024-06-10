#include <vector>
#include "circle.h"
#include <cmath>

 // Do we need like a centralized list of like circles?



void handle_collision(Circle circ1, Circle circ2){
    
    // Do trig stuff
           
    if (circ1.position.x > circ2.position.x){
        Circle temp = circ1;
        circ1 = circ2;
        circ2 = temp;
    }

    // circ1 is left
    double xDiff = circ2.position.x - circ1.position.x;
    double yDiff = circ2.position.y - circ1.position.y;

    double distanceBetweenCircles = sqrt(xDiff*xDiff + yDiff*yDiff);

    double overlap = distanceBetweenCircles - circ1.radius - circ2.radius;

    if (overlap > 0){
        double angleBetweenCircles = atan(yDiff/xDiff);

        double xToShift = cos(angleBetweenCircles) * overlap/2;
        double yToShift = sin(angleBetweenCircles) * overlap/2;

        circ1.position.x  -= xToShift;
        circ2.position.x  += xToShift;

        circ1.position.y -= yToShift;
        circ2.position.y += yToShift;
    }

}


void find_collisions(std::vector<Circle> circles){

    // very unoptimized rn

    for (Circle circ1 : circles){
        for (Circle circ2 : circles){
            if (&circ1 != &circ2){

                handle_collision(circ1, circ2);

            }
        }
    }
}

void update_physics(float dt, std::vector<Circle> circles)
{
    
    // Idk if we want to put this here or if this should go in engine
    find_collisions(circles);

    for (Circle circle : circles){
        // Maybe there's a better way to synchronize things?
        circle.update();
        // Can probably have an apply forces method as well later on
    }
    

}



void update_physics_sub_steps(float dt, int sub_steps, std::vector<Circle> circles)
{
    const float sub_dt = dt / float(sub_steps);
    for (int i{sub_steps};i--;)
    {
        update_physics(sub_dt, circles);
    }


}
