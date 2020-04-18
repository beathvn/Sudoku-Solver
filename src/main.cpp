//
//  main.cpp
//  SudokuSolver_linear
//
//  Created by Lukas Ellemunt on 06/04/2020.
//  Copyright © 2020 Lukas Ellemunt. All rights reserved.
//

#include <iostream>
#include <vector>
#include "Sudoku.hpp"

//TODO: refactor
//TODO: find method to read properly in

int main(int argc, const char * argv[]) {

    Sudoku mySudoku;
    std::cout << "the default Sudoku looks like this:" << std::endl;
    mySudoku.print();
    
    mySudoku.solve(0);
    std::cout << "the solved Sudoku looks like this:" << std::endl;
    mySudoku.print();
    
    return 0;
}
