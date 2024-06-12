#include "circle.h"
#include "vector"
#include "GLFW/glfw3.h"

void drawMap(GLFWwindow* window);

void drawCircles(GLFWwindow* window);

void drawGrid(GLFWwindow* window, int size);

float getNormalizedX(float x);

float getNormalizedY(float y);

float getNormalizedRadius(float r);

float getWidth(GLFWwindow *window);

float getHeight(GLFWwindow *window);

float calculateAspectRatio(GLFWwindow *window);