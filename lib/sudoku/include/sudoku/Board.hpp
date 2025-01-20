#pragma once

#include <algorithm>
#include <array>
#include <iostream>
#include <span>
#include <unordered_set>

#include "sudoku/fwd.hpp"
#include "sudoku/types.hpp"
#include "sudoku/util.hpp"

namespace sudoku
{

    class Board
    {
    public:
        Board(SudokuArray startingArray) : _state{startingArray}
        {
        }

        Board(std::initializer_list<std::initializer_list<std::uint8_t>> numberStartingList) :
            _state{CreateSudokuArray(numberStartingList)}
        {
        }

        void Set(const std::uint8_t row, const std::uint8_t col, const SudokuValue value);

        SudokuValue Get(const std::uint8_t row, const std::uint8_t col) const;
        SudokuSolved CheckBoard() const;
        SudokuSolved CheckColumn(const std::uint8_t col) const;
        SudokuSolved CheckRow(const std::uint8_t row) const;
        SudokuSolved CheckBox(const std::uint8_t row, const std::uint8_t col) const;

    private:
        static SudokuSolved CheckArray(const std::span<SudokuValue> array);

        static inline bool HasUniqueElements(const std::span<SudokuValue> array);

        static inline bool ContainsBlank(const std::span<SudokuValue> numbers);

        SudokuArray _state;
    };

    // overwrite stream operator to print a board layout for debug
    inline std::ostream& operator<<(std::ostream& os, const Board& board)
    {
        for(std::size_t i = 0; i < 9; ++i)
        {
            for(std::size_t j = 0; j < 9; ++j)
            {
                os << static_cast<int>(board.Get(i, j)) << " ";
            }
            os << std::endl;
        }
        return os;
    }

}