#include "gamestate.h"
#include <cassert>
#include <iostream>
namespace ChineseChess
{

GameState::GameState(Printer *print)
{
    if(print == 0)
    {
        std::invalid_argument("print, shit");
    }
    printer_ = print;
    fill_initial();
    printer_->Print(matrix_);
}

bool GameState::validate(Command com)
{
    try
    {
        bool result =
        matrix_.at(com.from.first, com.from.second) == Mat::state::BUSY &&
        matrix_.at(com.to.first, com.to.second) == Mat::state::FREE &&
        matrix_.at((com.from.first + com.to.first)/2,
                  (com.from.second + com.to.second)/2) == Mat::state::BUSY;
        return result;
    }
    catch(std::out_of_range &end_e)
    {
        std::cerr << end_e.what();
        return false;
    }

}

void GameState::make_move(Command com)
{
    if(validate(com))
    {
        try
        {
            matrix_.set_at(com.from.first, com.from.second, Mat::state::FREE);
            matrix_.set_at(com.to.first, com.to.second, Mat::state::BUSY);
            matrix_.set_at((com.from.first + com.to.first)/2,
                           (com.from.second + com.to.second)/2,
                           Mat::state::FREE);
            printer_->Print(matrix_);
        }
        catch(std::out_of_range &end_e)
        {
            std::cerr << end_e.what();
        }
    }
    else
    {
        std::cout << "command is not valid\n";
        return;
    }
}

void GameState::fill_initial()
{
    const int n_rows = matrix_.get_n_rows();
    const int n_cols = matrix_.get_n_cols();
    for(int i = 0; i < n_rows; ++i) {
        for(int j = 0; j < n_cols; ++j) {
            if( (i > 1 && i < 5) || (j > 1 && j < 5) ) {
                // Matrix[i][j] = 'o';
                matrix_.set_at(i, j, Mat::state::BUSY);
                if( (i == 3) && (j == 3))
                    //Matrix[i][j] = 'e';
                    matrix_.set_at(i, j, Mat::state::FREE);
            }
            else
                matrix_.set_at(i, j, Mat::state::CLOSE);
            }
        }
}

}
