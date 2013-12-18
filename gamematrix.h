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

    struct MatrixRangeExeption {};

private:
    state elements_[n_rows][n_cols];
    void check_range(int i, int j) const
    {
        if(( i < 0 || i >= n_rows ) || ( j < 0 || j >= n_cols ))
        {
            throw MatrixRangeExeption();
        }
    }
};

typedef GameMatrix<CellsAtRow, CellsAtColumn> Mat;
/*!
    шаблон принимает количество столбцов и колчество строк и подразумевает возможность
    конкретизации для любого размера марицы с определенной геометрицеской логикой
    Данный шаблон является реализацией паттерна Стратегия
*/
template <int nrows, int ncols>
void fill_initial(GameMatrix<nrows, ncols> &matrix);

template<>
inline void fill_initial(Mat &matrix) // конкретизация шаблона для матрицы 7*7
{
    const int n_rows = matrix.get_n_rows();
    const int n_cols = matrix.get_n_cols();
    for(int i = 0; i < n_rows; ++i)
    {
        for(int j = 0; j < n_cols; ++j)
        {
            if( (i > 1 && i < 5) || (j > 1 && j < 5) )
            {
                matrix.set_at(i, j, Mat::state::BUSY);
                if( (i == 3) && (j == 3))
                    matrix.set_at(i, j, Mat::state::FREE);
            }
            else
                matrix.set_at(i, j, Mat::state::CLOSE);
            }
        }
}

/*!
    Шаблон fill_matrix подразумевает возможность заполнения матрицы любых размеров
    филлером-заполнителем любой геометрической логики, то есть может использовать любую стратегию
*/
template <class MatrixFiller, int nrows, int ncols>
void fill_matrix(GameMatrix<nrows, ncols> &mat, MatrixFiller filler)
{
    filler(mat);
}

}

#endif // GAMEMATRIX_H
