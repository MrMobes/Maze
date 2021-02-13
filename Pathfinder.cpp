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
    ifstream file (file_name.c_str());
    if (file.is_open()) {
        string line;
        int row_count = 0;
        for(int row = 0; row < ROW_SIZE; row++) {
            getline(file, line);
            stringstream ss(line);
            for(int col = 0; col < COL_SIZE; col++) {
                int value;
                ss >> value;
                cout << "["<<row<<"]["<<col<<"]="<<value<<endl;
                maze_grid[row][col] = value;
            }
        }
    }
    return(true);
}

void createRandomMaze(){
    cout << "TODO" << endl;
}

string Pathfinder::toString() const {
    stringstream ss;
    for(int row = 0; row < ROW_SIZE; row++) {
        for(int col = 0; col < COL_SIZE; col++) {
            ss << maze_grid[row][col];
        }
        ss << endl;
    }
    return ss.str();
}

vector<string> solveMaze() {
    cout << "TODO" << endl;
}