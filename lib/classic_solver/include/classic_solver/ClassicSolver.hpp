#pragma once
#include <iostream>
#include <set>
#include "sudoku/Board.hpp"

namespace sudoku
{
    class ClassicSolver
    {
    public:
        ClassicSolver(const Board& board) :
            _board{board}, _blanks{GetBlanks(board)}
        {
        }

        Board Solve()
        {
            using namespace std;
            while(_board.CheckBoard() != SudokuSolved::YES)
            {
                auto numOfBlanks = _blanks.size();
                for(auto it = _blanks.begin(); it != _blanks.end(); it++)
                {
                    auto row = it->first;
                    auto col = it->second;

                    auto advanceSucceeded = TryAdvance(row, col);
                    // cout << "Trying to advance at " << static_cast<int>(row)
                    //  << ", " << static_cast<int>(col) << "..." << endl;
                    if(advanceSucceeded)
                    {
                        it = _blanks.erase(it);
                        cout << "Guessed! " << static_cast<int>(_board.Get(row, col))
                             << " at " << static_cast<int>(row) << ", "
                             << static_cast<int>(col) << endl;
                        if(_blanks.size() == 0)
                        {
                            break;
                        }
                    }
                }
                cout << _blanks.size() << " blanks left." << endl;
                if(numOfBlanks == _blanks.size())
                {
                    cout << "Failed to solve sudoku." << endl;
                    break;
                }
            }
            return _board;
        }

        void PrintBoard()
        {
            std::cout << _board << std::endl;
        }

        bool TryAdvance(const std::uint8_t row, const std::uint8_t col)
        {
            std::unordered_set<SudokuValue> possibleValues;
            for(std::uint8_t i = 1; i <= 9; ++i)
            {
                auto candidate = static_cast<SudokuValue>(i);
                if(!RowContains(row, candidate) && !ColumnContains(col, candidate) &&
                   !BoxContains(row, col, candidate))
                {
                    possibleValues.insert(candidate);
                }
            }
            if(possibleValues.size() == 1)
            {
                _board.Set(row, col, *possibleValues.begin());
                return true;
            }

            // for(auto value: possibleValues)
            // {
            //     if(!FindAnotherPossiblePlace(row, col, value))
            //     {
            //         _board.Set(row, col, value);
            //         return true;
            //     }
            // }
            return false;
        }

        bool FindAnotherPossiblePlace(std::uint8_t row, std::uint8_t col, SudokuValue value)
        {
            std::set<std::pair<std::uint8_t, std::uint8_t>> availableBlanks;

            for(const auto& [r, c]: _blanks)
            {
                if(r == row && c == col)
                {
                    continue;
                }
                if(r == row || c == col || WhichBox(r, c) == WhichBox(row, col))
                {
                    availableBlanks.insert({r, c});
                }
            }
            for(const auto& [r, c]: availableBlanks)
            {
                if(!RowContains(r, value) && !ColumnContains(c, value) &&
                   !BoxContains(r, c, value))
                {
                    // _board.Set(r, c, value);
                    return true;
                }
            }
            return false;
        }

        static std::uint8_t WhichBox(const std::uint8_t row, const std::uint8_t col)
        {
            return (row / 3) * 3 + (col / 3);
        }

        bool RowContains(const std::uint8_t row, const SudokuValue value)
        {
            if(row > 8)
            {
                throw std::invalid_argument("Row must be less than 9");
            }
            std::array<SudokuValue, 9> slice = {
                _board.Get(row, 0), //
                _board.Get(row, 1),
                _board.Get(row, 2),
                _board.Get(row, 3),
                _board.Get(row, 4),
                _board.Get(row, 5),
                _board.Get(row, 6),
                _board.Get(row, 7),
                _board.Get(row, 8)};

            return Contains(slice, value);
        }

        bool ColumnContains(const std::uint8_t col, const SudokuValue value)
        {
            if(col > 8)
            {
                throw std::invalid_argument("Column must be less than 9");
            }

            std::array<SudokuValue, 9> slice = {
                _board.Get(0, col), //
                _board.Get(1, col),
                _board.Get(2, col),
                _board.Get(3, col),
                _board.Get(4, col),
                _board.Get(5, col),
                _board.Get(6, col),
                _board.Get(7, col),
                _board.Get(8, col)};

            return Contains(slice, value);
        }

        bool BoxContains(const std::uint8_t row, const std::uint8_t col, const SudokuValue value)
        {
            if(row > 9 || col > 9)
            {
                throw std::invalid_argument(
                    "Row and column must be less than 7 for box index ");
            }

            auto boxRow = (row / 3) * 3;
            auto boxCol = (col / 3) * 3;

            std::array<SudokuValue, 9> slice = {
                _board.Get(boxRow, boxCol), //
                _board.Get(boxRow, boxCol + 1),
                _board.Get(boxRow, boxCol + 2),
                _board.Get(boxRow + 1, boxCol),
                _board.Get(boxRow + 1, boxCol + 1),
                _board.Get(boxRow + 1, boxCol + 2),
                _board.Get(boxRow + 2, boxCol),
                _board.Get(boxRow + 2, boxCol + 1),
                _board.Get(boxRow + 2, boxCol + 2)};

            return Contains(slice, value);
        }

        inline bool Contains(const std::span<SudokuValue> numbers, SudokuValue value)
        {
            return std::find(numbers.begin(), numbers.end(), value) != numbers.end();
        }

        std::set<std::pair<std::uint8_t, std::uint8_t>> GetBlanks(const Board& board)
        {
            std::set<std::pair<std::uint8_t, std::uint8_t>> blanks;
            for(std::uint8_t i = 0; i < 9; ++i)
            {
                for(std::uint8_t j = 0; j < 9; ++j)
                {
                    if(board.Get(i, j) == SudokuValue::__)
                    {
                        blanks.insert({i, j});
                    }
                }
            }
            return blanks;
        }

    private:
        Board _board;
        std::set<std::pair<std::uint8_t, std::uint8_t>> _blanks;
    };
}