#include <vector>
#include "circle.h"
#include "renderer.h"
#include "physics.h"

#include <iostream>
#include <vector>

struct GridCell {
    std::vector<Circle> circles;

    void addCircle(const Circle& circle) {
        circles.push_back(circle);
    }
};

struct Grid {
    int width, height;
    int radius;
    std::vector<std::vector<GridCell>> cells;

    int rows = height/radius;
    int cols = width/radius;

    Grid(int width_, int height_, int radius_)
        : width(width_), height(height_), radius(radius_) {
        cells.resize(rows, std::vector<GridCell>(cols));
    }

    void addCircle(const Circle& circle) {
        int col = static_cast<int>(circle.position_cur.x / circle.radius);
        int row = static_cast<int>(circle.position_cur.y / circle.radius);

        if (col >= 0 && col < cols && row >= 0 && row < rows) {
            cells[row][col].addCircle(circle);
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
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                std::cout << "Cell (" << r << "," << c << "): ";
                for (const auto& circle : cells[r][c].circles) {
                    std::cout << "[" << circle.position_cur.x << "," << circle.position_cur.y << "," << circle.radius << "] ";
                }
                std::cout << std::endl;
            }
        }
    }
};

