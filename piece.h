#ifndef PIECE_H
#define PIECE_H
#include<iostream>

class piece
{
    private:
            std::string pieceType;
            char side;
            int xPos;
            int yPos;
    public:
            piece();
            piece(piece*);
            piece(std::string, char, int, int);
            ~piece();
            char getSide();
            std::string getPiece();
            int getX();
            int getY();
            void setX(int);
            void setY(int);
            friend std::ostream& operator<<(std::ostream&,const piece&);
            void operator[](int);
            piece& operator+(std::string);
};
#endif
