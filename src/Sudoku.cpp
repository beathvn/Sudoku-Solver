//
//  Sudoku.cpp
//  SudokuSolver_linear
//
//  Created by Lukas Ellemunt on 16/04/2020.
//  Copyright © 2020 Lukas Ellemunt. All rights reserved.
//

#include "Sudoku.hpp"

int sumArr (const vector<int>& data) {
    int sum = 0;
    for (auto it : data) {
        sum += it;
    }
    
    return sum;
}

// maximize this sum!
int sumArr (const vector<vector<vector<int>>>& data) {
    int sum = 0;
     for (int i = 0; i < 9; i++) {
           for (int j = 0; j < 9; j++) {
               sum += sumArr(data[i][j]);
           }
     }
    return sum;
}

// function returns the sum of all givenNumbers found in a givenRow
int sumArrRow_withValue (const vector<vector<int>>& data, int givenValue) {
    int sum = 0;
    for (int i = 0; i < 9; i++) {
        sum += data[i][givenValue];
    }
    return sum;
}

// function returns the sum of all givenNumbers found in a givenColumn
int sumArrColumn_withValue (const vector<vector<vector<int>>>& data, int givenValue, int givenColumn) {
    int sum = 0;
    for (int i = 0; i < 9; i++) {
        sum += data[i][givenColumn][givenValue];
    }
    return sum;
}

bool Sudoku::isCellSet(const int& i, const int& j) {
    int buffer = sumArr(data[i][j]);
    if (buffer == 1) {
        return true;
    } else {return false;}
}

// returns the number (-1) which is set -> if nothing is set in this cell -> return -1
int Sudoku::getSetNumber(const int& givenRow, const int& givenColumn) {
    for (int i = 0; i < 9; i++) {
        if (data[givenRow][givenColumn][i] == 1) {return i;}
    }
    return -1;
}

bool Sudoku::legalSet(int givenRow, int givenColumn, int bufferValue) {
    //    setting the passed value
        data[givenRow][givenColumn][bufferValue] = 1;
        
        if (sumArrRow_withValue(data[givenRow], bufferValue) == 1 && sumArrColumn_withValue(data, bufferValue, givenColumn) == 1) {
            int sum = 0;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    sum += data[givenRow/3 * 3 + i][givenColumn / 3 * 3 + j][bufferValue];
                }
            }
            if (sum == 1) {
                return true;
                
            }
        }
        
    //    if it wasn't legal-> change it back to zero and return false
        data[givenRow][givenColumn][bufferValue] = 0;
        return false;
}

void Sudoku::undoSet(int givenRow, int givenColumn) {
    //    use range based for loop
    //    NOTE: auto it : data[givenRow][givenColumn] wasn't able to change the values
    //    in the vector, since a copy is returned
    for (int &it : data[givenRow][givenColumn]) {
        it = 0;
    }
}

// method calls itself recursively
void Sudoku::solve(int lastPosition) {
    //    function iterates over all cells in the sudoku. Once it found a cell, where no value is given, it tries all possible Values (bufferValue) and calls itself recursively
        while(lastPosition != 81) {
            int i = lastPosition / 9;
            int j = lastPosition % 9;
            if (!isCellSet(i, j)) {
                for (int bufferValue = 0; bufferValue < 9; bufferValue++) {
                    if (sumArr(data) == 81) break;
                    // if the sudoku is done don't change anything, just break
                    // if a deeper recursion layer returns here, we need to undo it's set and continue searching
                    // for a possible value by increasing the bufferValue
                    undoSet(i, j);
                    // try to set the value
                    if (legalSet(i, j, bufferValue)) {
                        this->solve((i * 9 + j));
                    }
                }
                if (sumArr(data) != 81) undoSet(i, j); //if the sudoku is not done yet, undo the last set
                return;
            }
            lastPosition++;
        }
}

Sudoku::Sudoku() {
    //    data[row][column][variable] -> everything starts at 0;
    //    1... set, 0...not set; sum over the last vector always 1 or 0; if 0 -> nothing is set, otherwise set
    //    example Sudoku -> save the set values
    
//    default constructor initializes the sudoku, by providing enough memory for the vectors and sets the values to given default vales

    data.resize(9, vector<vector<int>>(9, vector<int>(9)));
    
    
    data[1][0][2] = 1;
    data[1][2][1] = 1;
    data[1][3][8] = 1;
    data[1][8][6] = 1;
    
    data[2][1][8] = 1;
    data[2][4][2] = 1;
    data[2][5][7] = 1;
    data[2][7][4] = 1;
    
    data[3][2][3] = 1;
    data[3][7][5] = 1;
    
    data[4][1][7] = 1;
    data[4][8][8] = 1;
    
    data[5][1][0] = 1;
    data[5][3][6] = 1;
    data[5][4][3] = 1;
    data[5][5][5] = 1;
    data[5][6][4] = 1;
    
    
    data[6][0][8] = 1;
    data[6][4][0] = 1;
    
    data[7][1][4] = 1;
    data[7][5][3] = 1;

    data[8][5][4] = 1;
    data[8][7][8] = 1;
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
            // 0 means no set value-> we print an ' ', otherwise print the correct value
            std::string printValue;

            if ((getSetNumber(i, j) + 1) == 0) {
                printValue = " ";
            } else {
                printValue = std::to_string(getSetNumber(i, j) + 1);
            }

            std::cout << printValue << " ";
        }
        std::cout << "|";
    }
    std::cout << "\n -------------------\n" << std::endl;
}
