#include<iostream>
#include<sstream>
#include<fstream>
#include "solver.h"
#include "board.h"
#include "piece.h"


solver::solver(std::string games)
{
    std::string line;
    std::string countlines;
    std::string gameName;
    std::string wholeline;
    int count = 0;
    char delim = ',';
    int pri;
    int index = 0;
    int countGames = 0;
    numGames = 0;
    std::ifstream infile(games.c_str());
    while(getline(infile,countlines))
    {
        std::stringstream c(countlines);
        //while(getline(c,wholeline,'\n'))
        //{
            numGames++; 
        //}
    }
    //std::cout<<numGames<<std::endl;
    infile.close();
    boards = new board* [numGames];
    int priArr [3];
    int indexp = 0;
    std::ifstream infile2(games.c_str());
    
    while(getline(infile2,line))
    {
        std::stringstream s(line);
        //std::cout<<"line "<<line<<std::endl;
        while(getline(s,gameName,delim))
        {
            
            if(count == 0)
            {
                boards[index] = new board(gameName);
                index++; 
            }
        
            if(count == 1)
            {
            std::stringstream ss(gameName);
            ss >> pri;
            //std::cout<<"num from file "<< pri <<std::endl;
            priArr[indexp] = pri;
            indexp++;
            count = -1;
            }    
            count++; 
        }
    }
    //sort
    for(int i = 0; i < numGames-1; i++)
    {
        if(priArr[i] > priArr[i+1])
        {
            
            board *temp = boards[i];
            boards[i] = boards[i+1];
            boards[i+1] = temp;
            int tempPri = priArr[i];
            priArr[i] = priArr[i+1];
            priArr[i+1] = tempPri;
        }
    }
    //if check mate
    for(int i = 0; i < numGames; i++)
    {
        //std::string ifmate = boards[i]->operator--();
        std::cout<< "["<<priArr[i]<<"] ";
        boards[i]->operator--();
        
        
    }
}

solver::~solver()
{
    delete [] boards;
    std::cout<<"Num Boards Deleted: "<<numGames<<std::endl;  
}
