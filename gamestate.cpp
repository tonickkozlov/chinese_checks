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
    fill_matrix(matrix_, fill_initial<CellsAtRow, CellsAtColumn>);
    printer_->Print(matrix_);
    n_el = n_elements();
}

int GameState::get_n_el()
{
    return n_el;
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

int GameState::n_elements()
{
    int count = 0;
    for(int i = 0; i < matrix_.get_n_rows(); ++i)
    {
        for(int j = 0; j < matrix_.get_n_cols(); ++j)
        {
            if(matrix_.at(i, j) == Mat::state::BUSY)
                count++;
        }
    }
    return count;
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
            n_el--;
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

}
