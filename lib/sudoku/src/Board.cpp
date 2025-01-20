#include "sudoku/Board.hpp"
#include <stdexcept>

namespace sudoku
{
    void Board::Set(const std::uint8_t row, const std::uint8_t col, const SudokuValue value)
    {
        if(row > 8 || col > 8)
        {
            throw std::invalid_argument("Row and column must be less than 9");
        }
        _state[row][col] = value;
    }

    SudokuValue Board::Get(const std::uint8_t row, const std::uint8_t col) const
    {
        if(row > 8 || col > 8)
        {
            throw std::invalid_argument("Row and column must be less than 9");
        }
        return _state[row][col];
    }

    SudokuSolved Board::CheckBoard() const
    {
        for(std::uint8_t i = 0; i < 9; ++i)
        {
            if(CheckRow(i) == SudokuSolved::NO)
            {
                return SudokuSolved::NO;
            }
            if(CheckColumn(i) == SudokuSolved::NO)
            {
                return SudokuSolved::NO;
            }
        }

        for(std::uint8_t i = 0; i < 9; i += 3)
        {
            for(std::uint8_t j = 0; j < 9; j += 3)
            {
                if(CheckBox(i, j) == SudokuSolved::NO)
                {
                    return SudokuSolved::NO;
                }
            }
        }

        return SudokuSolved::YES;
    }

    SudokuSolved Board::CheckColumn(const std::uint8_t col) const
    {
        if(col > 8)
        {
            throw std::invalid_argument("Column must be less than 9");
        }

        std::array<SudokuValue, 9> slice = {
            _state[0][col], //
            _state[1][col],
            _state[2][col],
            _state[3][col],
            _state[4][col],
            _state[5][col],
            _state[6][col],
            _state[7][col],
            _state[8][col]};

        return CheckArray(slice);
    }

    SudokuSolved Board::CheckRow(const std::uint8_t row) const
    {
        if(row > 8)
        {
            throw std::invalid_argument("Row must be less than 9");
        }
        std::array<SudokuValue, 9> slice = {
            _state[row][0], //
            _state[row][1],
            _state[row][2],
            _state[row][3],
            _state[row][4],
            _state[row][5],
            _state[row][6],
            _state[row][7],
            _state[row][8]};

        return CheckArray(slice);
    }

    SudokuSolved Board::CheckBox(const std::uint8_t row, const std::uint8_t col) const
    {
        if(row > 8 || col > 8)
        {
            throw std::invalid_argument("Row and column must be less than 9");
        }
        std::array<SudokuValue, 9> slice = {
            _state[row][col], //
            _state[row][col + 1],
            _state[row][col + 2],
            _state[row + 1][col],
            _state[row + 1][col + 1],
            _state[row + 1][col + 2],
            _state[row + 2][col],
            _state[row + 2][col + 1],
            _state[row + 2][col + 2]};
        return CheckArray(slice);
    }
    SudokuSolved Board::CheckArray(const std::span<SudokuValue> array)
    {
        return !ContainsBlank(array) && HasUniqueElements(array) ? SudokuSolved::YES :
                                                                   SudokuSolved::NO;
    }

    inline bool Board::HasUniqueElements(const std::span<SudokuValue> array)
    {
        std::unordered_set<SudokuValue> set(array.begin(), array.end());
        return set.size() == array.size();
    }

    inline bool Board::ContainsBlank(const std::span<SudokuValue> numbers)
    {
        return std::find(numbers.begin(), numbers.end(), SudokuValue::__) !=
            numbers.end();
    }
}