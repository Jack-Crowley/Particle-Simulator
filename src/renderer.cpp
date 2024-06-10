#include "circle.h"
#include "GLFW/glfw3.h"
#include <vector>
#include <cmath>
#include "stdio.h"

void drawCircles(GLFWwindow* window, std::vector<Circle> circles) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    float aspectRatio = ((float) height)/width;

    for (Circle circ : circles) {
        glBegin(GL_LINE_LOOP);
        glColor3f(1.0, 1.0, 1.0);
        double radius = circ.radius/50;
        double x, y;
        for (int i = 0; i < 360; i++) {
            x = aspectRatio * radius * cos(i * 3.14159 / 180.0) + circ.position.x/200.0;
            y = radius * sin(i * 3.14159 / 180.0) + circ.position.y/200.0;
            glVertex2f(x, y);
        }
        glEnd();
    }
}