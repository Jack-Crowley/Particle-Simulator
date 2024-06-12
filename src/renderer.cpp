#include "circle.h"
#include "GLFW/glfw3.h"
#include <vector>
#include <cmath>
#include "stdio.h"
#include "sceneManager.h"

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
    return r / 1000.0;
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

    for (Circle circ : getCircles())
    {
        glBegin(GL_LINE_LOOP);
        glColor3f(1.0, 1.0, 1.0);
        float radius = getNormalizedRadius(circ.radius);
        for (int i = 0; i < 360; i++)
        {
            float x = aspectRatio * (radius * cos(i * 3.14159 / 180.0) + getNormalizedX(circ.position.x));
            float y = radius * sin(i * 3.14159 / 180.0) + getNormalizedY(circ.position.y);
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