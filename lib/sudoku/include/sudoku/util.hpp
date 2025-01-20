#pragma once
#include <array>
#include <cstdint>
#include <initializer_list>
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
