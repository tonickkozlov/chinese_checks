#include "gamestate.h"
#include <cassert>
namespace ChineseChess
{

GameState::GameState(IOutput* output)
{
    assert(output != nullptr);
    output_ = output;
    fill_initial();
    output->Draw(matrix_);
}

void GameState::fill_initial()
{
    const int n_rows = matrix_.get_n_rows();
    const int n_cols = matrix_.get_n_cols();
    for(int i = 0; i < n_rows; ++i) {
        for(int j = 0; j < n_cols; ++j) {
            if( (i > 2 && i < 6) || (j > 2 && j < 6) ) {
                // Matrix[i][j] = 'o';
                matrix_.set_at(i, j, Mat::state::BUSY);
                if( (i == 4) && (j == 4))
                    //Matrix[i][j] = 'e';
                    matrix_.set_at(i, j, Mat::state::FREE);
            }
            else
                matrix_.set_at(i, j, Mat::state::CLOSE);
            }
        }
}

}
