#include <vector>
#include "circle.h"
#include "renderer.h"
#include "physics.h"
#include <stdio.h>

#include <iostream>
#include <vector>

struct GridCell {
    std::vector<Circle> circles;

    void addCircle(const Circle& circle);

    std::vector<Circle> getCircles();
};

struct Grid {
    int width, height;
    int radius;
    int rows, cols;
    std::vector<std::vector<GridCell>> cells;

    Grid(int width_, int height_, int radius_);

    GridCell getCell(const Circle& circle);

    std::vector<GridCell> getNeighborCells(const Circle& circle);

    void addCircle(const Circle& circle);

    void populateGrid(const std::vector<Circle>& circles);

    void printGrid();
};

