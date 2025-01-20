#pragma once
#include <array>
#include <cstdint>
#include <fstream>
#include <initializer_list>
#include <vector>
#include <stdexcept>

#include "sudoku/types.hpp"

namespace sudoku
{
    inline SudokuValue Uint8ToSudokuValue(const std::uint8_t value)
    {
        if(value >= 0 && value <= 9)
        {
            return static_cast<SudokuValue>(value);
        }
        throw std::invalid_argument("Value must be between 0 and 9");
    }

    inline std::vector<SudokuArray> LoadSudokuArrays(const std::string filename)
    {
        using namespace std;
        ifstream file(filename);
        vector<SudokuArray> boards;
        string line;

        while(getline(file, line))
        {
            if(line.rfind("Grid", 0) == 0)
            {
                SudokuArray sudokuArray;

                for(int i = 0; i < 9; ++i)
                {
                    getline(file, line);
                    for(int j = 0; j < 9; ++j)
                    {
                        sudokuArray[i][j] = static_cast<SudokuValue>(line[j] - '0');
                    }
                }
                boards.push_back(sudokuArray);
            }
        }

        return boards;
    }

    inline SudokuArray
        CreateSudokuArray(std::initializer_list<std::initializer_list<std::uint8_t>> numberArray)
    {
        auto ncols = numberArray.size();
        if(ncols != 9)
        {
            throw std::invalid_argument("Number of columns must be 9");
        }

        for(const auto& row: numberArray)
        {
            if(row.size() != 9)
            {
                throw std::invalid_argument("Number of rows must be 9");
            }
        }

        SudokuArray array;
        for(std::size_t i = 0; i < 9; ++i)
        {
            for(std::size_t j = 0; j < 9; ++j)
            {
                auto value = ((numberArray.begin() + i)->begin())[j];
                array[i][j] = Uint8ToSudokuValue(value);
            }
        }
        return array;
    }
}
