#ifndef SOLVER_H
#define SOLVER_H
#include<iostream>

class board;

class solver
{
    private:
            int numGames;
            board** boards;
    public:
            solver(std::string);
            ~solver();
            
};
#endif
