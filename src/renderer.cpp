#include "circle.h"
#include "GLFW/glfw3.h"
#include <vector>
#include <cmath>

void drawCircles(std::vector<Circle> circles) {
    for (Circle circ : circles) {
        glBegin(GL_LINE_LOOP);
        glColor3f(1.0, 1.0, 1.0); // Set color to white
        double radius = 0.5;
        double x, y;
        for (int i = 0; i < 360; i++) {
            x = radius * cos(i * 3.14159 / 180.0);
            y = radius * sin(i * 3.14159 / 180.0);
            glVertex2f(x, y);
        }
        glEnd();
    }
}