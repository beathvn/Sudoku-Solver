//
//  Sudoku.hpp
//  SudokuSolver_linear
//
//  Created by Lukas Ellemunt on 16/04/2020.
//  Copyright © 2020 Lukas Ellemunt. All rights reserved.
//

#ifndef Sudoku_hpp
#define Sudoku_hpp

#include <cstdio>
#include <vector>
#include <iostream>

using std::vector;

// call solve the first time with 0 (you want to start solving from position 0

class Sudoku {
private:
    vector<vector<vector<int>>> data;
    
    bool isCellSet (const int& i, const int& j);
    int getSetNumber (const int& givenRow, const int& givenColumn);
    bool legalSet (int givenRow, int givenColumn, int bufferValue);
    void undoSet (int givenRow, int givenColumn);
    
public:
    Sudoku();
    void solve(int lastPosition);
    void print();
};

#endif /* Sudoku_hpp */
