#ifndef CONSOLEPRINTER_H
#define CONSOLEPRINTER_H
#include "chinese_chess.h"
#include "gamestate.h"
#include <iostream>

namespace ChineseChess {

class ConsolePrinter: public Printer
{
public:
    void Print(const Mat &matrix)
    {
        std::cout << "  ";
        for(int j = 0; j < matrix.get_n_cols(); ++ j)
        {
            std::cout << j <<" ";
        }
        std::cout << std::endl;
        for(int i = 0; i < matrix.get_n_cols(); ++i)
        {
            std::cout << i << " ";
            for(int j = 0; j < matrix.get_n_rows(); ++j)
            {
                switch (matrix.at(i,j))
                {

                case Mat::state::BUSY:
                    std::cout << "e";
                    break;
                case Mat::state::CLOSE:
                    std::cout << "x";
                    break;
                case Mat::state::FREE:
                    std::cout << "o";
                    break;
                }
                std::cout << " ";
            }
            std::cout << std::endl;
        }
    }
};

}

#endif // CONSOLEPRINTER_H
