//
// Created by jmobe on 2/12/2021.
//
#include <iostream>
#include <sstream>
#include <fstream>
#include "Pathfinder.h"
using namespace std;

Pathfinder::Pathfinder() {
    for(int lay=0; lay<LAYERS; lay++){
        for(int row=0; row<ROW_SIZE; row++){
            for(int col=0; col<COL_SIZE; col++){
                maze_grid[row][col][lay] = 1;
            }
        }
    }
}

bool Pathfinder::importMaze(string file_name) {
    isValidMaze = true;
    cout << "importMaze from "<<file_name<<endl;
    ifstream tempFile(file_name.c_str());
    int charCount = 0;
    int count = 0;
    if(tempFile.is_open()) {
        string temp;
        while(getline(tempFile, temp)) {
            if(count == 0 && temp.at(0)!='1') {
                isValidMaze = false;
            }
            else if (count == 28 && temp.at(temp.length()-1)!='1'){
                isValidMaze = false;
            }
            charCount++;
            count++;
            if(temp!="") {
                for (int i = 0; i < temp.length(); i++) {
                    if (temp.at(i) != '0' && temp.at(i) != '1' && temp.at(i) != ' '){
                        cout << temp.at(i);
                        isValidMaze = false;
                    }
                }
            }
        }
        if(charCount!=29) {
            isValidMaze = false;
        }
        tempFile.close();
    }
    ifstream file(file_name.c_str());
    if (file.is_open()) {
        if(!isValidMaze) {
            return false;
        }
        else {
            string line;
            for (int lay = 0; lay < LAYERS; lay++) {
                for (int row = 0; row < ROW_SIZE; row++) {
                    getline(file, line);
                    stringstream ss(line);
                    for (int col = 0; col < COL_SIZE; col++) {
                        int value;
                        ss >> value;
                        cout << "[" << row << "][" << col << "][" << lay << "]=" << value << endl;
                        maze_grid[row][col][lay] = value;
                    }
                }
                getline(file, line);
            }
            return true;
        }
    }
    else{
        return false;
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
                if(col < 4) {
                    ss << " ";
                }
            }
            ss << endl;
        }
        if(lay<4) {
            ss << endl;
        }
    }
    return ss.str();
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

vector<string> Pathfinder::solveMaze() {
    find_maze_path(maze_grid, 0,0,0);
    for(auto s:solution) {
        cout <<s<<endl;
    }
    return solution;
}