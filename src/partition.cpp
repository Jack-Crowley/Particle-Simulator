#include <vector>
#include "circle.h"
#include "renderer.h"
#include "physics.h"
#include <stdio.h>

#include <iostream>
#include <vector>

struct GridCell {
    std::vector<Circle> circles;

    void addCircle(const Circle& circle) {
        circles.push_back(circle);
    }

    std::vector<Circle> getCircles() {
        return circles;
    }
};

struct Grid {
    int width, height;
    int radius;
    int rows, cols;
    std::vector<std::vector<GridCell>> cells;

    Grid(int width_, int height_, int radius_) {
        this->width = width_;
        this->height = height_;
        this->radius = radius_;

        this->rows = this->height/this->radius;
        this->cols = this->width/this->radius;

        cells.resize(this->rows, std::vector<GridCell>(this->cols));
    }

    GridCell getCell(const Circle& circle) {
        int col = static_cast<int>(circle.position_cur.x / circle.radius);
        int row = static_cast<int>(circle.position_cur.y / circle.radius);

        return this->cells[row][col];
    }

    std::vector<GridCell> getNeighborCells(const Circle& circle) {
        std::vector<GridCell> neighbors;
        GridCell origCell = getCell(circle);
        neighbors.push_back(origCell);

        int col = static_cast<int>(circle.position_cur.x / circle.radius);
        int row = static_cast<int>(circle.position_cur.y / circle.radius);

        if (row-1 >= 0 && col-1 >= 0) {
            neighbors.push_back(this->cells[row-1][col-1]);
        }
        if (row-1 >= 0 && col >= 0) {
            neighbors.push_back(this->cells[row-1][col]);
        }
        if (row-1 >= 0 && col+1 < this->cols) {
            neighbors.push_back(this->cells[row-1][col+1]);
        }
        if (row >= 0 && col-1 >= 0) {
            neighbors.push_back(this->cells[row][col-1]);
        }
        if (row >= 0 && col+1 < this->cols) {
            neighbors.push_back(this->cells[row][col+1]);
        }
        if (row+1 < this->rows && col-1 >= 0) {
            neighbors.push_back(this->cells[row+1][col-1]);
        }
        if (row+1 < this->rows && col >= 0) {
            neighbors.push_back(this->cells[row+1][col]);
        }
        if (row+1 < this->rows && col+1 < this->cols) {
            neighbors.push_back(this->cells[row+1][col+1]);
        }
        return neighbors;
    }

    void addCircle(const Circle& circle) {
        int col = static_cast<int>(circle.position_cur.x / circle.radius);
        int row = static_cast<int>(circle.position_cur.y / circle.radius);

        if (col >= 0 && col < this->cols && row >= 0 && row < this->rows) {
            this->cells[row][col].addCircle(circle);
        } else {
            std::cerr << "Circle is out of grid bounds!" << std::endl;
        }
    }

    void populateGrid(const std::vector<Circle>& circles) {
        for (const auto& circle : circles) {
            addCircle(circle);
        }
    }

    void printGrid() const {
        for (int r = 0; r < this->rows; ++r) {
            for (int c = 0; c < this->cols; ++c) {
                std::cout << "Cell (" << r << "," << c << "): ";
                for (const auto& circle : cells[r][c].circles) {
                    std::cout << "[" << circle.position_cur.x << "," << circle.position_cur.y << "," << circle.radius << "] ";
                }
                std::cout << std::endl;
            }
        }
    }
};

