//
// Created by jmobe on 2/12/2021.
//

#ifndef LAB3_PATHFINDER_H
#define LAB3_PATHFINDER_H
#include "PathfinderInterface.h"

class Pathfinder: public PathfinderInterface {
protected:
    static const int ROW_SIZE = 5;
    static const int COL_SIZE = 5;
    static const int LAYERS = 5;
    const int BACKGROUND = 1;
    const int WALL = 0;
    const int TEMPORARY = 2; // Used to show this path has been explored
    const int PATH = 3;
    int maze_grid[ROW_SIZE][COL_SIZE][LAYERS]; // To hold values
    vector<string> solution;
    bool isValidMaze = true;
public:
    Pathfinder();
    string toString() const override;
    void createRandomMaze() override;
    bool importMaze(string file_name) override;
    bool find_maze_path(int grid[ROW_SIZE][COL_SIZE][LAYERS], int r, int c, int l);
    vector<string> solveMaze() override;
};

#endif //LAB3_PATHFINDER_H
