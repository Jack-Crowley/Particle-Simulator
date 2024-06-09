#include <vector>


class Circle {

    public:
        double radius;

        double xPos;
        double yPos;

        double xVel;
        double yVel;

        double xAcc;
        double yAcc;

    Circle(double r, double xStart, double yStart){

        radius = r;

        xPos = xStart;
        yPos = yStart;

    }

    public:
    void update(){

        // Maybe can change this for concurrency 

        xVel += xAcc;
        xPos += xVel;

        yVel += yAcc;
        yPos += yVel;
    }
};

std::vector <Circle> circlesToSimulate = std::vector<Circle>();

void update_physics(float dt)
{
     // Do we need like a centralized list of like circles?
    for (Circle circle : circlesToSimulate){
        // Maybe there's a better way to synchronize things?
        circle.update();
        // Can probably have an apply forces method as well later on
    }
    

}

void handle_collision(Circle circ1, Circle circ2){
    
    // Do trig stuff
           
    if (circ1.xPos > circ2.xPos){
        Circle temp = circ1;
        circ1 = circ2;
        circ2 = temp;
    }

    // circ1 is left
    double xDiff = circ2.xPos - circ1.xPos;
    double yDiff = circ2.yPos - circ1.yPos;

    double distanceBetweenCircles = sqrt(xDiff*xDiff + yDiff*yDiff);

    double overlap = distanceBetweenCircles - circ1.radius - circ2.radius;

    double angleBetweenCircles = atan(yDiff/xDiff);

    double xToShift =  cos(angleBetweenCircles) * overlap/2;
    double yToShift = sin(angleBetweenCircles) * overlap/2;

    circ1.xPos -= xToShift;
    circ2.xPos += xToShift;

    circ1.yPos -= yToShift;
    circ2.yPos += yToShift;
    

}


void update_physics_sub_steps(float dt, int sub_steps)
{
    const float sub_dt = dt / float(sub_steps);
    for (int i{sub_steps};i--;)
    {
        update_physics(sub_dt);
    }


}
