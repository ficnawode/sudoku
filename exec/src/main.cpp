#include <iostream>
#include "classic_solver/ClassicSolver.hpp"

int main()
{
    auto arrays = sudoku::LoadSudokuArrays("p096_sudoku.txt");
    sudoku::ClassicSolver solver(arrays[0]);
    solver.PrintBoard();
    auto solvedBoard = solver.Solve();
    solver.PrintBoard();
    return 0;
}