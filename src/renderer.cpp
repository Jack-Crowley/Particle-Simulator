#include "circle.h"
#include "GLFW/glfw3.h"
#include <vector>
#include <cmath>
#include "stdio.h"
#include "sceneManager.h"

// These all need to be divided by the same thing
float getNormalizedX(float x)
{
    return x / 500.0;
}

float getNormalizedY(float y)
{
    return y / 500.0;
}

float getNormalizedRadius(float r)
{
    return r / 500.0;
}

float getHeight(GLFWwindow *window) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return (float) height;
}

float getWidth(GLFWwindow *window) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return (float) width;
}

float calculateAspectRatio(GLFWwindow *window)
{
    return getHeight(window)/getWidth(window);
}

void drawCircles(GLFWwindow *window)
{
    float aspectRatio = calculateAspectRatio(window);

    for (Circle &circ : getCircles())
    {
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(circ.color.red, circ.color.green, circ.color.blue);
        float radius = getNormalizedRadius(circ.radius);
        for (int i = 0; i < 360; i++)
        {
            float x = aspectRatio * (radius * cos(i * 3.14159 / 180.0) + getNormalizedX(circ.position_cur.x));
            float y = radius * sin(i * 3.14159 / 180.0) + getNormalizedY(circ.position_cur.y);
            glVertex2f(x, y);
        }
        glEnd();
    }
}

void drawGrid(GLFWwindow *window, int size)
{
    float aspectRatio = calculateAspectRatio(window);

    glColor4f(0.2, 0.2, 0.2, 0.3);
    for (int i = 0; i < 1000; i += size)
    {
        glBegin(GL_LINES);
        glVertex2f(aspectRatio * getNormalizedX(i), -1.0f);
        glVertex2f(aspectRatio * getNormalizedX(i), 1.0f);
        glEnd();

        glBegin(GL_LINES);
        glVertex2f(aspectRatio * getNormalizedX(i) * -1, -1.0f);
        glVertex2f(aspectRatio * getNormalizedX(i) * -1, 1.0f);
        glEnd();
    }
    for (int i = 0; i < 1000; i += size)
    {
        glBegin(GL_LINES);
        glVertex2f(-1.0f, getNormalizedY(i));
        glVertex2f(1.0f, getNormalizedY(i));
        glEnd();

        glBegin(GL_LINES);
        glVertex2f(-1.0f, getNormalizedY(i) * -1);
        glVertex2f(1.0f, getNormalizedY(i) * -1);
        glEnd();
    }
}

void drawMap(GLFWwindow *window)
{
    float aspectRatio = calculateAspectRatio(window);

    float x = aspectRatio;

    for (Obstacle o : currentMap.obstacles) {
        int s;
        glBegin(GL_POINTS);
        glColor3f(1.0, 1.0, 1.0);
        for (float i = o.leftLimit; i < o.rightLimit; i+=5) {
            float x = aspectRatio * getNormalizedX(i);
            int size;
            float* y = o.calculate(i, size);
            for (int yi = 0; yi < size; yi++) {
                glVertex2f(x, getNormalizedY(y[yi]));
            }
        }
        glEnd();
    }

    glColor3f(0.04, 0.04, 0.04);

    glBegin(GL_QUADS);
    glVertex2f(1, -1.0f);
    glVertex2f(1, 1.0f);
    glVertex2f(x, 1.0f);
    glVertex2f(x, -1.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-1, -1.0f);
    glVertex2f(-1, 1.0f);
    glVertex2f(-x, 1.0f);
    glVertex2f(-x, -1.0f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_LINES);
    glVertex2f(x, -1.0f);
    glVertex2f(x, 1.0f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-x, -1.0f);
    glVertex2f(-x, 1.0f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-x, -1.0f);
    glVertex2f(x, -1.0f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(x, 1.0f);
    glVertex2f(-x, 1.0f);
    glEnd();
}