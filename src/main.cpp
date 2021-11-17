//
//  main.cpp
//  SudokuSolver_linear
//
//  Created by Lukas Ellemunt on 06/04/2020.
//  Copyright © 2020 Lukas Ellemunt. All rights reserved.
//

#include <iostream>

#include "Sudoku.hpp"


int main() {

    Sudoku mySudoku;
    std::cout << "this is the given Sudoku:" << std::endl;
    mySudoku.print();

    // logging the start time, so we can see how long the algorithm took
    auto startTime = std::chrono::system_clock::now();

    mySudoku.solve(0);
    std::cout << "this is the solved Sudoku:" << std::endl;
    mySudoku.print();

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = endTime - startTime;
    std::cout << "Solving the Sudoku took " << elapsed_seconds.count() << " seconds!";
    
    return 0;
}
