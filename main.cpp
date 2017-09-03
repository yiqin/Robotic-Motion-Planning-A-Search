//
//  main.cpp
//
//  Created by Yi Qin on September 2, 2017.
//  Copyright © 2017 Yi Qin. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <vector>
#include <map>


struct Direction {
    int deltaX;
    int deltaY;
    int deltaZ;
    double cost;
    
    Direction(int deltaX, int deltaY, int deltaZ): deltaX(deltaX), deltaY(deltaY), deltaZ(deltaZ) {
        if (abs(deltaX) == 1 && abs(deltaY) == 1) {
            cost = sqrt(2);
        } else {
            cost = 1;
        }
    }
};

struct Position {
    int x;
    int y;
    int z;
    double value;
    bool outsideGrid;
    // TODO: Consider multiple pathes.
    std::vector<Position> path;
    
    Position(int x, int y, int z): x(x), y(y), z(z) {
        value = 0.0;
        outsideGrid = false;
    }
    
    Position(const Position &current, const Direction &direction, const size_t maxRow, const size_t maxColumn) {
        x = current.x + direction.deltaX;
        y = current.y + direction.deltaY;
        z = current.z + direction.deltaZ;
        if (x >= maxRow || y >= maxColumn || x < 0 || y < 0) {
            outsideGrid = true;
            value = INFINITY;
        } else {
            outsideGrid = false;
            value = current.value + direction.cost;
        }
        
        path = current.path;
        path.push_back(current);
    }
    
    void printPath() const {
        std::cout << "Found the end position\n";
        std::cout << "Min cost is ";
        std::cout << value << "\n";
        
        bool hasUsedHammer = false;
        for(auto &step: path) {
            std::cout << "(" << step.x << "," << step.y << ") ";
            if (!hasUsedHammer && step.z == 1) {
                std::cout << "Use the hammer. ";
                hasUsedHammer = true;
            }
            std::cout << "\n";
        }
        std::cout << "(" << x << "," << y << ")\n";
    }
    
    bool operator==(const Position &other) const {
        return x == other.x && y == other.y && z == other.z;
    }
    
    bool operator<(const Position &p) const {
        return x < p.x || (x == p.x && y < p.y) || (x == p.x && y == p.y && z < p.z);
    }
};


void Dijkstra(const std::vector<std::vector<int>> grid, const Position start, const Position end) {
    if (end.z == 1) {
        std::cout << "Enable the hammer\n\n";
    }
    
    size_t maxRow = grid.size();
    size_t maxColumn = grid[0].size();
    
    if (grid[start.x][start.y] != 0) {
        std::cout << "Valid star position\n";
    }
    
    if (grid[start.x][start.y] != 0) {
        std::cout << "Invalid end position\n";
    }
    
    const Direction directions[8*2] = {
        Direction(1, 0, 0),
        Direction(0, 1, 0),
        Direction(-1, 0, 0),
        Direction(0, -1, 0),
        Direction(1, 1, 0),
        Direction(1, -1, 0),
        Direction(-1, -1, 0),
        Direction(-1, 1, 0),
        Direction(1, 0, 1),
        Direction(0, 1, 1),
        Direction(-1, 0, 1),
        Direction(0, -1, 1),
        Direction(1, 1, 1),
        Direction(1, -1, 1),
        Direction(-1, -1, 1),
        Direction(-1, 1, 1),
    };
    
    std::map<Position, bool> range;
    range[start] = true;
    bool hasNewArea = true;
    
    // dijkstra
    while (hasNewArea) {
        hasNewArea = false;
        double minValue = INFINITY;
        std::vector<Position> newPositions;
        
        for (auto &item : range) {
            if (!item.second) {
                // std::cout << "Skip (" << item.first.x << "," << item.first.y << ") \n";
                continue;
            }
            hasNewArea = true;

            Position current = item.first;
            bool hasNewDirection = false;
            
            // Find direction
            for(const Direction direction : directions) {
                if (current.z  == 1 && direction.deltaZ == 1) {
                    continue;
                }
                
                Position newPosition = Position(current, direction, maxRow, maxColumn);
                if (newPosition.outsideGrid) {
                    continue;
                }
                if (range.find(newPosition) != range.end()) {
                    continue;
                }
                if (grid[newPosition.x][newPosition.y] != direction.deltaZ) {
                    continue;
                }
                
                hasNewDirection = true;
                
                if (newPosition.value < minValue) {
                    newPositions.clear();
                    newPositions.push_back(newPosition);
                    minValue = newPosition.value;
                    
                } else if (newPosition.value == minValue) {
                    newPositions.push_back(newPosition);
                }
            }
            if (!hasNewDirection) {
                item.second = false;
            }
        }
        
        for (Position position: newPositions) {
            range[position] = true;
        }
        newPositions.clear();
        
        // Check whether reach the end posotion
        Position notUseHammerPosition = Position(end.x, end.y, 0);
        if (range.find(notUseHammerPosition) != range.end()) {
            for (auto &item : range) {
                if (item.first == notUseHammerPosition) {
                    item.first.printPath();
                }
            }
            break;
        }
        if (end.z == 1) {
            if (range.find(end) != range.end()) {
                for (auto item : range) {
                    if (item.first == end) {
                        item.first.printPath();
                    }
                }
                break;
            }
        }
    }
    
    // If there is not new area, it fails to reach the end position.
    if (!hasNewArea) {
        std::cout << "Failed to reach the end position\n";
    }
}


void findPath(std::vector<std::vector<int>> grid, int startX, int startY, int endX, int endY, bool enableHammer) {
    Position start = Position(startX, startY, 0);
    int z = enableHammer? 1 : 0;
    Position end = Position(endX, endY, z);
    Dijkstra(grid, start, end);
}

void printGrid(std::vector<std::vector<int>> grid) {
    std::cout << "2D Grid\n";
    for(std::vector<int> column : grid) {
        for(int item : column) {
            std::cout << item << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


int main(int argc, const char * argv[]) {
    std::cout << "############\n";
    std::cout << "Part 1 - Test case 1:\n";
    
    std::vector<std::vector<int>> grid1;
    grid1.push_back({0, 1, 0, 0});
    grid1.push_back({0, 1, 0, 0});
    grid1.push_back({0, 1, 0, 0});
    grid1.push_back({0, 1, 0, 0});
    grid1.push_back({0, 1, 0, 0});
    grid1.push_back({0, 0, 0, 0});
    printGrid(grid1);
    // (0, 0) -> (0, 3)
    findPath(grid1, 0, 0, 0, 3, false);


    std::cout << "\n\n############\n";
    std::cout << "Part 2 - Test case 2:\n";
    printGrid(grid1);
    // (0, 0) -> (0, 3)
    findPath(grid1, 0, 0, 0, 3, true);

    
    std::cout << "\n\n############\n";
    std::cout << "Part 1 - Test case 3:\n";
    
    std::vector<std::vector<int>> grid2;
    grid2.push_back({0, 1, 0});
    grid2.push_back({0, 0, 0});
    grid2.push_back({1, 0, 0});
    printGrid(grid2);
    
    // (1, 0) -> (2, 2)
    findPath(grid2, 1, 0, 2, 2, false);
    
    std::cout << "\n\n############\n";
    std::cout << "Part 2 - Test case 4:\n";
    printGrid(grid2);
    // (1, 0) -> (2, 2)
    findPath(grid2, 1, 0, 2, 2, true);
    

    std::cout << "\n\n############\n";
    std::cout << "Part 1 - Test case 5:\n";
    
    std::vector<std::vector<int>> grid3;
    grid3.push_back({0, 1, 0});
    grid3.push_back({1, 1, 0});
    grid3.push_back({1, 0, 0});
    printGrid(grid3);
    // (0, 0) -> (2, 2)
    findPath(grid3, 0, 0, 2, 2, false);

    std::cout << "\n\n############\n";
    std::cout << "Part 2 - Test case 5:\n";
    printGrid(grid3);
    // (0, 0) -> (2, 2)
    findPath(grid3, 0, 0, 2, 2, true);

    return 0;
}
