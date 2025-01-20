#pragma once

#include <algorithm>
#include <array>
#include <span>
#include <unordered_set>

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

}