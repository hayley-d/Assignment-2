#ifndef BOARD_H
#define BOARD_H
#include<iostream>
#include"piece.h"

class piece;

class board
{
    private:
            int numWhitePieces;
            int numBlackPieces;
            piece** whitePieces;
            piece** blackPieces;
            std::string** chessboard;
            std::string move;
            char sideToMove;
            board& operator++();
    public:
            board(std::string);
            ~board();
            board& operator--();
            bool checkIfPieceHasCheck(std::string,int,int,int,int);
};
#endif
