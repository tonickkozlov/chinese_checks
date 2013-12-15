#ifndef GAMEMATRIX_H
#define GAMEMATRIX_H

#include <exception>
#include "chinese_chess.h"

namespace ChineseChess
{

template<int n_rows, int n_cols>
class GameMatrix
{
public:
    enum class state //c++11, запрещает автоматическую конвертацию к int
    {
        BUSY,
        FREE,
        CLOSE
    };
    int get_n_rows() const { return n_rows; }
    int get_n_cols() const { return n_cols; }
    state at(int i, int j) const // получение элемента матрицы с некоторым ограничением/проверкой
    {
        check_range(i, j);
        return elements_[i][j];
    }

    void set_at(int i, int j, state new_state) // установить состояние для i-j элемента
    {
        check_range(i, j);
        elements_[i][j] = new_state;
    }

    explicit GameMatrix() // explicit для вызова конструктора только вручную
    {
        for(int i = 0; i < n_rows; ++i)
        {
            for(int j = 0; j < n_cols; ++j)
            {
                elements_[i][j] = state::CLOSE;
            }
        }
    }

private:
    state elements_[n_rows][n_cols];
    void check_range(int i, int j) const
    {
        if(( i < 0 || i >= n_rows ) || ( j < 0 || j >= n_cols ))
        {
            // TODO: обернуть в наше исключение
            throw std::out_of_range("b"); // стандартное исключение, выбрасывается при неверном i или j
        }
    }
};

typedef GameMatrix<CellsAtRow, CellsAtColumn> Mat;

}

#endif // GAMEMATRIX_H
