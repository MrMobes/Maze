//
// Created by jmobe on 2/12/2021.
//
#include <iostream>
#include <sstream>
#include <fstream>
#include "Pathfinder.h"
using namespace std;

bool Pathfinder::importMaze(string file_name) {
    cout << "importMaze from "<<file_name<<endl;
    ifstream file(file_name.c_str());
    if (file.is_open()) {
        int count = 0;
        string line;
        string temp;
        int row_count = 0;
        for (int lay = 0; lay < LAYERS; lay++) {
            for (int row = 0; row < ROW_SIZE; row++) {
                getline(file, line);
                cout << "Line contents = " << line << endl;
                stringstream ss(line);
                for (int col = 0; col < COL_SIZE; col++) {
                    count++;
                    int value;
                    ss >> value;
                    if(value!=0 && value!=1) {
                        isValidMaze = false;
                    }
                    cout << "[" << row << "][" << col << "][" << lay << "]=" << value << endl;
                    maze_grid[row][col][lay] = value;
                }
            }
            getline(file, line);
        }
        if(count!=(LAYERS*ROW_SIZE*COL_SIZE)) {
            isValidMaze = false;
        }
        if(!isValidMaze) {
            return false;
        }
        else {
            return true;
        }
    }
}

void Pathfinder::createRandomMaze() {
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            for(int k = 0; k < 5; k++) {
                maze_grid[i][j][k] = rand() % 2;
            }
        }
    }
    maze_grid[0][0][0] = 1;
    maze_grid[4][4][4] = 1;
}

string Pathfinder::toString() const {
    stringstream ss;
    for(int lay = 0; lay < LAYERS; lay++) {
        for(int row = 0; row < ROW_SIZE; row++) {
            for(int col = 0; col < COL_SIZE; col++) {
                ss << maze_grid[row][col][lay];
            }
            ss << endl;
        }
        ss << endl;
    }
    return ss.str();
}

vector<string> Pathfinder::solveMaze() {
    find_maze_path(maze_grid, 0,0,0);
    for(auto s:solution) {
        cout <<s<<endl;
    }
    return solution;
}

bool Pathfinder::find_maze_path(int grid[ROW_SIZE][COL_SIZE][LAYERS], int r, int c, int l) {
    cout << "find_maze_path ["<<r<<"]["<<c<<"]["<<l<<"]"<<endl;
    cout << this->toString();
    if (r < 0 || c < 0 || l < 0 || r >= ROW_SIZE || c >= COL_SIZE || l >= LAYERS)
        return false;      // Cell is out of bounds.
    else if (grid[r][c][l] != BACKGROUND)
        return false;      // Cell is on barrier or dead end.
    else if (r == ROW_SIZE - 1 && c == COL_SIZE - 1 && l == LAYERS - 1) {
        grid[r][c][l] = PATH;         // Cell is on path
        solution.push_back("("+to_string(r)+","+to_string(c)+","+to_string(l)+")");
        return true;               // and is maze exit.
    }
    else {
        // Recursive case.
        // Attempt to find a path from each neighbor.
        // Tentatively mark cell as on path.
        grid[r][c][l] = PATH;
        if (find_maze_path(grid, r - 1, c, l) // North
            || find_maze_path(grid, r + 1, c, l) // South
            || find_maze_path(grid, r, c - 1, l) // West
            || find_maze_path(grid, r, c + 1, l)  // East
            || find_maze_path(grid, r, c, l + 1) // Up
            || find_maze_path(grid, r, c, l - 1) // Down
             ) {
            solution.push_back("("+to_string(r)+","+to_string(c)+","+to_string(l)+")");
            return true;
        }
        else {
            grid[r][c][l] = TEMPORARY;  // Dead end.
            return false;
        }
    }
}