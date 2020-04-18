//
//  Sudoku.cpp
//  SudokuSolver_linear
//
//  Created by Lukas Ellemunt on 16/04/2020.
//  Copyright © 2020 Lukas Ellemunt. All rights reserved.
//

#include "Sudoku.hpp"

int sumArr (const vector<int>& myVec) {
    int sum = 0;
    for (auto it : myVec) {
        sum += it;
    }
    
    return sum;
}

int sumArr (vector<vector<int>>& myVec) {
    int sum = 0;
    for (int i = 0; i < 9; i++) {
        sum += sumArr(myVec[i]);
    }
    return sum;
}

//maximize this sum!
int sumArr (const vector<vector<vector<int>>>& myVec) {
    int sum = 0;
     for (int i = 0; i < 9; i++) {
           for (int j = 0; j < 9; j++) {
               sum += sumArr(myVec[i][j]);
           }
     }
    return sum;
}

//function returns the sum of all givenNumbers found in a givenRow
int sumArrRow_withValue (const vector<vector<int>>& myVec, int givenValue) {
    int sum = 0;
    for (int i = 0; i < 9; i++) {
        sum += myVec[i][givenValue];
    }
    return sum;
}

//function returns the sum of all givenNumbers found in a givenColumn
int sumArrColumn_withValue (const vector<vector<vector<int>>>& myVec, int givenValue, int givenColumn) {
    int sum = 0;
    for (int i = 0; i < 9; i++) {
        sum += myVec[i][givenColumn][givenValue];
    }
    return sum;
}

bool Sudoku::isCellSet(const int& i, const int& j) {
    int buffer = sumArr(myVec[i][j]);
    if (buffer == 1) {
        return true;
    } else {return false;}
}

//returns the number (-1) which is set -> if nothing is set in this cell -> return -1
int Sudoku::getSetNumber(const int& givenRow, const int& givenColumn) {
    for (int i = 0; i < 9; i++) {
        if (myVec[givenRow][givenColumn][i] == 1) {return i;}
    }
    return -1;
}

bool Sudoku::legalSet(int givenRow, int givenColumn, int bufferValue) {
    //    setting the passed value
        myVec[givenRow][givenColumn][bufferValue] = 1;
        
        if (sumArrRow_withValue(myVec[givenRow], bufferValue) == 1 && sumArrColumn_withValue(myVec, bufferValue, givenColumn) == 1) {
            int sum = 0;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    sum += myVec[givenRow/3 * 3 + i][givenColumn / 3 * 3 + j][bufferValue];
                }
            }
            if (sum == 1) {
                return true;
                
            }
        }
        
    //    if it wasn't legal -> change it back to zero and return false
        myVec[givenRow][givenColumn][bufferValue] = 0;
        return false;
}

void Sudoku::undoSet(int givenRow, int givenColumn) {
    //    use rangebased for loop; NOTE: auto it : myVec[givenRow][givenColumn] wasn't able to change the values in the vector!?
    for (vector<int>::iterator it = myVec[givenRow][givenColumn].begin(); it != myVec[givenRow][givenColumn].end(); it++) {
        *it = 0;
    }
}

//method calls itself recursively
void Sudoku::solve(int lastPosition) {
    //    function iterates over all cells in the sudoku. Once it found a cell, where no value is given, it tries all possible Values (buffervalue) and calls itself rekursively
        while(lastPosition != 81) {
            int i = lastPosition / 9;
            int j = lastPosition % 9;
            if (!isCellSet(i, j)) {
                for (int bufferValue = 0; bufferValue < 9; bufferValue++) {
                    if (sumArr(myVec) == 81) break; //if the sudoku is done don't change anything, just break
    //                    if a deeper recursion layer returns here, we need to undo it's set and continue searching for a possible value by increasing the buffervalue
    //                    TODO: optimize the amount of calling this function
                    undoSet(i, j);
    //                    try to set the value
                    if (legalSet(i, j, bufferValue)) {
                        this->solve((i * 9 + j));
                    }
                }
                if (sumArr(myVec) != 81) undoSet(i, j); //if the sudoku is not done yet, undo the last set
                return;
            }
            lastPosition++;
        }
}

Sudoku::Sudoku() {
    //    myVec[row][column][variable] -> everything starts at 0;
    //    1... set, 0...not set; sum over the last vector always 1 or 0; if 0 -> nothing is set, otherwise set
    //    example Sudoku -> save the set values
    
//    default constructor initializes the sudoku, by providing enough memory for the vectors and sets the values to given default vales
//    TODO: think about other way to read in Sudoku data
    
    myVec.resize(9, vector<vector<int>>(9, vector<int>(9)));
    
    
    myVec[0][0][3] = 1;
    myVec[0][6][2] = 1;
    
    myVec[1][5][6] = 1;
    myVec[1][7][1] = 1;
    myVec[1][8][4] = 1;
    
    myVec[2][1][0] = 1;
    myVec[2][4][3] = 1;
    myVec[2][5][1] = 1;
    myVec[2][7][5] = 1;
    myVec[2][8][7] = 1;
    
    myVec[3][0][7] = 1;
    myVec[3][6][4] = 1;
    myVec[3][8][3] = 1;
    
    myVec[5][2][5] = 1;
    myVec[5][5][2] = 1;
    myVec[5][7][7] = 1;
    
    myVec[6][4][0] = 1;
    
    myVec[7][1][8] = 1;
    myVec[7][6][1] = 1;
    
    myVec[8][0][0] = 1;
    myVec[8][3][5] = 1;
    myVec[8][4][7] = 1;
    myVec[8][8][6] = 1;
}

void Sudoku::print() {
    for (int i = 0; i < 9; i++) {
        if (i == 0 || i == 3 || i == 6) {
            std::cout << "\n -------------------";
        }
        std::cout << std::endl;
        for (int j = 0; j < 9; j++) {
            if (j == 0 || j == 3 || j == 6) {
                std::cout << "|";
            }
            std::cout << (getSetNumber(i, j) + 1) << " ";
        }
        std::cout << "|";
    }
    std::cout << "\n -------------------\n" << std::endl;
}
