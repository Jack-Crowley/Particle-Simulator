#include "circle.h"
#include "GLFW/glfw3.h"
#include <vector>
#include <cmath>
#include "stdio.h"


float getNormalizedX(float x) {
    return x/640.0;
}

float getNormalizedY(float y) {
    return y/360.0;
}

float getNormalizedRadius(float r) {
    return r/720.0;
}

void drawCircles(GLFWwindow* window, std::vector<Circle> circles, float &scaleFactor) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    float aspectRatio = ((float) height)/width;

    float scalingFactor = scaleFactor;

    for (Circle circ : circles) {
        glBegin(GL_LINE_LOOP);
        glColor3f(1.0, 1.0, 1.0);
        float radius = getNormalizedRadius(circ.radius);
        for (int i = 0; i < 360; i++) {
            float x = aspectRatio * (radius * cos(i * 3.14159 / 180.0) + getNormalizedX(circ.position.x));
            float y = radius * sin(i * 3.14159 / 180.0) + getNormalizedY(circ.position.y);
            glVertex2f(x, y);
        }
        glEnd();
    }
}

void drawGrid(GLFWwindow* window, int size) {
    glBegin(GL_LINES);
    for (int i = -640; i < 640; i+=size) {
        glBegin(GL_LINES);
        glVertex2f(getNormalizedX(i), -1.0f);
        glVertex2f(getNormalizedX(i), 1.0f);
        glEnd();
    }
    for (int i = -360; i < 360; i+=size) {
        glBegin(GL_LINES);
        glVertex2f(-1.0f, getNormalizedY(i));
        glVertex2f(1.0f, getNormalizedY(i));
        glEnd();
    }
    glEnd();
}