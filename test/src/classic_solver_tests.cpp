#include <classic_solver/ClassicSolver.hpp>
#include <gtest/gtest.h>
// #include "sudoku/util.hpp"
#include "euler_sudokus.hpp"

namespace
{
    TEST(ClassicSolverTests, WhichBoxtests)
    {
        EXPECT_EQ(sudoku::ClassicSolver::WhichBox(0, 0), 0);
        EXPECT_EQ(sudoku::ClassicSolver::WhichBox(0, 1), 0);
        EXPECT_EQ(sudoku::ClassicSolver::WhichBox(0, 2), 0);
        EXPECT_EQ(sudoku::ClassicSolver::WhichBox(1, 0), 0);
        EXPECT_EQ(sudoku::ClassicSolver::WhichBox(1, 1), 0);
        EXPECT_EQ(sudoku::ClassicSolver::WhichBox(1, 2), 0);
        EXPECT_EQ(sudoku::ClassicSolver::WhichBox(2, 0), 0);
        EXPECT_EQ(sudoku::ClassicSolver::WhichBox(2, 1), 0);
        EXPECT_EQ(sudoku::ClassicSolver::WhichBox(2, 2), 0);

        EXPECT_EQ(sudoku::ClassicSolver::WhichBox(0, 3), 1);
        EXPECT_EQ(sudoku::ClassicSolver::WhichBox(0, 4), 1);
        EXPECT_EQ(sudoku::ClassicSolver::WhichBox(0, 5), 1);
        EXPECT_EQ(sudoku::ClassicSolver::WhichBox(1, 3), 1);

        EXPECT_EQ(sudoku::ClassicSolver::WhichBox(3, 3), 4);
        EXPECT_EQ(sudoku::ClassicSolver::WhichBox(8, 8), 8);
    }

    TEST(ClassicSolverTests, SolveOneMissing)
    {
        sudoku::Board unsolvedBoard(
            {{4, 3, 5, 2, 6, 9, 7, 8, 1},
             {6, 8, 2, 5, 7, 1, 4, 9, 3},
             {1, 9, 7, 8, 3, 4, 5, 6, 2},
             {8, 2, 6, 1, 9, 5, 3, 4, 7},
             {3, 7, 4, 6, 8, 2, 9, 1, 5},
             {9, 5, 1, 7, 4, 3, 6, 2, 8},
             {5, 1, 9, 3, 0, 6, 8, 7, 4},
             {2, 4, 8, 9, 5, 7, 1, 3, 6},
             {7, 6, 3, 4, 1, 8, 2, 5, 9}});
        sudoku::ClassicSolver solver(unsolvedBoard);
        auto solvedBoard = solver.Solve();
        EXPECT_EQ(solvedBoard.CheckBoard(), sudoku::SudokuSolved::YES);
    }

    TEST(ClassicSolverTests, Contains)
    {
        sudoku::Board unsolvedBoard(
            {{0, 0, 3, 0, 0, 0, 0, 8, 4},
             {0, 0, 6, 0, 0, 0, 2, 7, 0},
             {0, 0, 0, 4, 7, 0, 0, 6, 0},
             {6, 9, 0, 0, 0, 0, 3, 5, 0},
             {3, 0, 0, 8, 5, 0, 4, 9, 0},
             {0, 1, 5, 3, 9, 0, 7, 0, 0},
             {5, 7, 0, 0, 3, 1, 0, 0, 0},
             {4, 0, 9, 0, 0, 2, 0, 1, 0},
             {1, 0, 0, 0, 0, 5, 0, 0, 9}});
        sudoku::ClassicSolver solver(unsolvedBoard);
        using enum sudoku::SudokuValue;
        EXPECT_TRUE(solver.RowContains(0, _3));
        EXPECT_TRUE(solver.RowContains(0, _8));
        EXPECT_TRUE(solver.RowContains(0, _4));
        EXPECT_FALSE(solver.RowContains(0, _1));

        EXPECT_TRUE(solver.ColumnContains(0, _6));
        EXPECT_TRUE(solver.ColumnContains(0, _5));
        EXPECT_TRUE(solver.ColumnContains(0, _1));
        EXPECT_FALSE(solver.ColumnContains(0, _9));

        EXPECT_TRUE(solver.BoxContains(0, 0, _3));
        EXPECT_TRUE(solver.BoxContains(0, 1, _6));
        EXPECT_TRUE(solver.BoxContains(2, 2, _3));
        EXPECT_FALSE(solver.BoxContains(2, 0, _1));
        EXPECT_TRUE(solver.BoxContains(4, 4, _3));
        EXPECT_TRUE(solver.BoxContains(5, 5, _5));
    }

    TEST(ClassicSolverTests, SolveModerate)
    {
        sudoku::Board unsolvedBoard(
            {{0, 0, 3, 0, 0, 0, 0, 8, 4},
             {0, 0, 6, 0, 0, 0, 2, 7, 0},
             {0, 0, 0, 4, 7, 0, 0, 6, 0},
             {6, 9, 0, 0, 0, 0, 3, 5, 0},
             {3, 0, 0, 8, 5, 0, 4, 9, 0},
             {0, 1, 5, 3, 9, 0, 7, 0, 0},
             {5, 7, 0, 0, 3, 1, 0, 0, 0},
             {4, 0, 9, 0, 0, 2, 0, 1, 0},
             {1, 0, 0, 0, 0, 5, 0, 0, 9}});
        sudoku::ClassicSolver solver(unsolvedBoard);
        auto solvedBoard = solver.Solve();
        EXPECT_EQ(solvedBoard.CheckBoard(), sudoku::SudokuSolved::YES);
    }

    class SudokuTest : public ::testing::TestWithParam<sudoku::Board>
    {
    protected:
        bool isSolved(const sudoku::Board& board)
        {
            return board.CheckBoard() == sudoku::SudokuSolved::YES;
        }
    };

    TEST_P(SudokuTest, SolveEulerSudokus)
    {
        sudoku::Board board = GetParam();
        auto solver = sudoku::ClassicSolver(board);
        auto solvedBoard = solver.Solve();
        EXPECT_TRUE(isSolved(solvedBoard));
    }

    INSTANTIATE_TEST_SUITE_P(SudokuClassicSolverTests, SudokuTest, ::testing::ValuesIn(sudoku::eulerBoards));
}
