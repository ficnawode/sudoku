#pragma once

#include <cstdint>
#include "sudoku/fwd.hpp"

namespace sudoku
{
    enum class SudokuValue : std::uint8_t
    {
        __ = 0,
        _1 = 1,
        _2 = 2,
        _3 = 3,
        _4 = 4,
        _5 = 5,
        _6 = 6,
        _7 = 7,
        _8 = 8,
        _9 = 9
    };

    enum class SudokuSolved : bool
    {
        NO = false,
        YES = true
    };

    using SudokuArray = std::array<std::array<SudokuValue, 9>, 9>;
}