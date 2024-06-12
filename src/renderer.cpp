#include "circle.h"
#include "GLFW/glfw3.h"
#include <vector>
#include <cmath>
#include "stdio.h"

void drawCircles(GLFWwindow* window, std::vector<Circle> circles, float &scaleFactor) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    float aspectRatio = ((float) height)/width;

    float scalingFactor = scaleFactor;

    for (Circle circ : circles) {
        glBegin(GL_LINE_LOOP);
        glColor3f(1.0, 1.0, 1.0);
        double radius = circ.radius/scalingFactor;
        double x, y;
        for (int i = 0; i < 360; i++) {
            // x = aspectRatio * radius * cos(i * 3.14159 / 180.0) + circ.position.x/scalingFactor;

            // Works without aspectRatio scaling atm
            x = aspectRatio * (radius * cos(i * 3.14159 / 180.0) + circ.position_cur.x/scalingFactor);
            y = radius * sin(i * 3.14159 / 180.0) + circ.position_cur.y/scalingFactor;
            glVertex2f(x, y);
        }
        glEnd();
    }
}