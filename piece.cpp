#include<iostream>
#include<string>
#include<sstream>
#include "piece.h"

piece::piece()
{

}

piece::piece(piece* newPiece)
{
    this->pieceType = newPiece->getPieceType();
    this->side = newPiece->getSide();
    this->xPos = newPiece->getX();
    this->yPos = newPiece->getY();
}

piece::piece(std::string type, char side, int x, int y)
{
    this->pieceType = type;
    this->side = side;
    this->xPos = x;
    this->yPos = y;
}

piece::~piece()
{
    std::cout<<"("<<xPos<<","<<yPos<<") "<<side<<" "<<pieceType<< " deleted"<<std::endl; 
}

char piece::getSide()
{
    return side;
}

std::string piece::getPieceType()
{
    return pieceType;
}

int piece::getX()
{
    return xPos;
}

int piece::getY()
{
    return yPos;
}

void piece::setX(int x)
{
    this->xPos = x;
}

void piece::setY(int y)
{
    this->yPos = y;
}

std::ostream& operator<<(std::ostream& output,const piece& t)
{
    piece &ref = const_cast <piece&>(t);
    output<<ref.getSide()<<" "<<ref.getPieceType()<<" at ["<<ref.getX()<<","<<ref.getY()<<"]"<<std::endl;
    return output;
}

void piece::operator[](int pos)
{
    if(pos!=1 || pos!=0)
    {
        std::cout<<"Invalid Index"<<std::endl;
    }
    else if(pos == 1)
    {
        std::cout<<"y coord: "<< yPos <<std::endl;
    }
    else if(pos == 0)
    {
        std::cout<<"x coord: "<< xPos <<std::endl;
    }
}

piece& piece::operator+(std::string move)
{
    std::string line;
    int x;
    int y;
    int count=0;
    std::stringstream s(move);

    while(getline(s,line,','))
    {
        if(count == 0)
        {
            std::stringstream ss(line);
            ss >> x;
        }
        if(count == 1)
        {
            std::stringstream ss(line);
            ss >> y;
        }
        count++;
    }
    if(x>=0 && x<=7 && y>=0 && y<=7)
    {
        this->xPos = x;
        this->yPos = y;
    }
    return *this;
}
