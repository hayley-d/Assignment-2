#include<iostream>
#include<fstream>
#include<sstream>
#include "board.h"
#include "piece.h"

board::board(std::string pieceList)
{
//read from file
    std::string line;
    int counter;
    char delim = ',';
    char side;
    char movingSide;
    std::string type;
    std::string num;
    int xpos;
    int ypos;
    int count = 0;
    int countpos = 0;
    
    std::ifstream infile;
    infile.open(pieceList.c_str());
    while(getline(infile,line))
    {
        std::stringstream s(line);
        if(count == 0)
        {
            movingSide = line[0];
        }
        else if(count==1)
        {
            move = line;
        }//end else
        else
        {
            while(getline(s,num,','))
            {
                if(countpos == 0)
                {
                    side = num[0];
                }
                else if(countpos == 1)
                {
                    type = num;
                }
                else if(countpos == 2)
                {
                    std::stringstream pos(num);
                    pos >> xpos;
                }
                else if(countpos == 3)
                {
                    std::stringstream pos(num);
                    pos >> ypos;
                }
                countpos++;
            }//end while
        }//end else
        count++;
    }
    
}

board::~board()
{
    
    delete [] blackPieces;
    delete [] whitePieces;
    for(int i = 0; i < 8; i++)
    {
       delete [] chessboard[i];
    }
    delete [] chessboard;
    int num = numBlackPieces+numWhitePieces;
    std::cout<<"Num Pieces Removed: "<<num<<std::endl;
         
}

board& board::operator++()
{
    std::string line;
    char delim = ',';
    int xi;
    int yi;
    int xf;
    int yf;
    int count = 0;
    std::stringstream s(move);
    while(getline(s,line,delim))
    {
        if(count == 0)
        {
            std::stringstream num(line);
            num >> xi;
            count++;
        }//end else

        else if(count == 1)
        {
            std::stringstream num(line);
            num >> yi;
            count++;
        }//end else

        else if(count ==2)
        {   
            std::stringstream num(line);
            num >> xf;
            count++;
        }//end else

        else if(count==3)
        {
            std::stringstream num(line);
            num >> yf;
            count++;
        }//end else
    }//end while
    
    std::string cpiece  = chessboard[xi][yi];
    char colour = cpiece[0];
    if(colour == 'b')
    {
        for(int i = 0; i<numBlackPieces; i++)
        {
            if(blackPieces[i]->getX() == xi && blackPieces[i]->getY() == yi)
            {
                blackPieces[i]->setX(xf);
                blackPieces[i]->setX(yf);
            }//end if
        }//end for
    }//end if
    else if(colour == 'w')
    {
        for(int i = 0; i<numWhitePieces; i++)
        {
            if(whitePieces[i]->getX() == xi && whitePieces[i]->getY() == yi)
            {
                whitePieces[i]->setX(xf);
                whitePieces[i]->setX(yf);
            }//end if
        }//end for
    }//end if  
    chessboard[xf][yf] = cpiece;
    chessboard[xi][yi] = "-"; 
    return *this;
}

board& board::operator--()
{
    std::string output;
    std::stringstream s(move);
    int counter = 0;
    int posX;   
    int posY;
    std::string line;
    while(getline(s,line,','))
    {
        if(counter == 2)
        {
            std::stringstream ss(line);
            ss >> posX;
        } 
        else if(counter == 3)
        {
            std::stringstream ss(line);
            ss >> posY;
        } 
        counter++;  
    }
    std::string thePiece = chessboard[posX][posY];
    char colour = thePiece[0];
    piece* moved;
    piece* king;

    if(colour == 'w')
    {
        for(int i = 0; i < numWhitePieces; i++)
        {
            if(whitePieces[i]->getX() == posX && whitePieces[i]->getY() == posY)
            {
               moved = whitePieces[i];
            }  
        }//end for piece
        for(int i = 0; i < numBlackPieces; i++)
        {
            if(blackPieces[i]->getPiece() == "king")
            {
               king = blackPieces[i];
            }
        }//end for king
    }//end if

    if(colour == 'b')
    {
        for(int i = 0; i < numBlackPieces; i++)
        {
            if(blackPieces[i]->getX() == posX && blackPieces[i]->getY() == posY)
            {
               moved = blackPieces[i];
            }
        }//end for piece
        for(int i = 0; i < numWhitePieces; i++)
        {
            if(whitePieces[i]->getPiece() == "king")
            {
               king = whitePieces[i];
            }
        }//end for king
    }//end if
    int kingX = king->getX();
    int kingY = king->getY();
    char kingColour = king->getSide();
    
    bool check = checkIfPieceHasCheck(thePiece,posX,posY,kingX,kingY);

    if(check == true)//need to see if a checkmate not just check and add the filed output if it is just a check
    {
        int x1 = kingX-1;
        int x2 = kingX-1;
        int x3 = kingX-1;
        int y1 = kingY-1;
        int y2 = kingY+1;
        int y3 = kingY;
        
        int x4 = kingX+1;
        int x5 = kingX+1;
        int x6 = kingX+1;
        int y4 = kingY-1;
        int y5 = kingY+1;
        int y6 = kingY;
        
        int x7 = kingX;
        int x8 = kingX;
        int y7 = kingY-1;
        int y8 = kingY+1;
        
        bool flag = false;
        int wayOut = 0;
        if(x1<=7 && x1>=0 && y1<=7 && y1>=0)
        {
            flag = checkIfPieceHasCheck(thePiece,posX,posY,x1,y1);
            if(flag == false)
            {
                wayOut++;
            }
            flag = false;
        }
        if(x2<=7 && x2>=0 && y2<=7 && y2>=0)
        {
            flag = checkIfPieceHasCheck(thePiece,posX,posY,x2,y2);
            if(flag == false)
            {
                wayOut++;
            }
            flag = false;
        }
        if(x3<=7 && x3>=0 && y3<=7 && y3>=0)
        {
            flag = checkIfPieceHasCheck(thePiece,posX,posY,x3,y3);
            if(flag == false)
            {
                wayOut++;
            }
            flag = false;
        }
        if(x4<=7 && x4>=0 && y4<=7 && y4>=0)
        {
            flag = checkIfPieceHasCheck(thePiece,posX,posY,x4,y4);
            if(flag == false)
            {
                wayOut++;
            }
            flag = false;
        }
        if(x5<=7 && x5>=0 && y5<=7 && y5>=0)
        {
            flag = checkIfPieceHasCheck(thePiece,posX,posY,x5,y5);
            if(flag == false)
            {
                wayOut++;
            }
            flag = false;
        }
        if(x6<=7 && x6>=0 && y6<=7 && y6>=0)
        {
            flag = checkIfPieceHasCheck(thePiece,posX,posY,x6,y6);
            if(flag == false)
            {
                wayOut++;
            }
            flag = false;
        }
        if(x7<=7 && x7>=0 && y7<=7 && y7>=0)
        {
            flag = checkIfPieceHasCheck(thePiece,posX,posY,x7,y7);
            if(flag == false)
            {
                wayOut++;
            }
            flag = false;
        }
        if(x8<=7 && x8>=0 && y8<=7 && y8>=0)
        {
            flag = checkIfPieceHasCheck(thePiece,posX,posY,x8,y8);
            if(flag == false)
            {
                wayOut++;
            }
            flag = false;
        }
        if(wayOut == 0)
        {
            std::cout<<"Success: Checkmate of "<<kingColour<<" King at ["<<kingX<<","+kingY<<"]"<<std::endl;
        }
        else if( wayOut != 0 )
        {
            std::cout<<"Failed: No Checkmate of "<< kingColour<<" King"<<std::endl ;
        }
    }//end if
    if(check == false)//need to add if just a check not a checkmate
    {
        std::cout<<"Failed: No Checkmate of "<<kingColour<<" King" ;
        
    }//end else 
    return *this;  
}

bool board::checkIfPieceHasCheck(std::string pieceType,int xPos,int yPos,int kingX,int kingY)
{
    std::string cpiece = chessboard[xPos][yPos];
    bool check = false;
    char colour = cpiece[0];
    char type = cpiece[1];
    
    if(colour == 'b')
    {
        for(int i = 0; i<numBlackPieces; i++)
        {
            if(blackPieces[i]->getX() == xPos && blackPieces[i]->getY() == yPos)
            {
                piece* currPiece = blackPieces[i];
            }//end if
        }//end for
    }//end if
    else if(colour == 'w')
    {
        for(int i = 0; i<numWhitePieces; i++)
        {
            if(whitePieces[i]->getX() == xPos && whitePieces[i]->getY() == yPos)
            {
                piece* currPiece = whitePieces[i];
            }//end if
        }//end for
    }//end if  
    
    if(type == 'p')
    {
        if(colour=='w')
        {
            int x1 = xPos-1;
            int x2 = xPos-1;
            int y1 = yPos-1;
            int y2 = yPos+1;
            if(kingX == x1 && kingY == y1)
            {
              check = true;  
            }
            if(kingX == x2 && kingY == y2)
            {
                check = true;
            }
        }//end if

        if(colour=='b')
        {
            int x1 = xPos+1;
            int x2 = xPos+1;
            int y1 = yPos-1;
            int y2 = yPos+1;
            if(kingX == x1 && kingY == y1)
            {
              check = true;  
            }
            if(kingX == x2 && kingY == y2)
            {
              check = true;
            }
        }//end if
    }//end p if

    else if(type == 'q')
    {
        int row = xPos;
        int col = yPos;
        int max = col;
        int min = kingY;

       
        if(kingY > col)
        {
            max = kingY;
            min = col;
        }//end if
        
        if(colour == 'w')
        {
            if(kingX == row)
            {
                bool flag = false;
                for(int i = 0; i < numWhitePieces; i++)
                {
                    if(whitePieces[i]->getX()==row && whitePieces[i]->getY()<max && whitePieces[i]->getY() > min)
                    {
                        flag = true;
                    }
                }//end for
                if(flag == false)
                    check = true;
                    
            }//end if

            else if(kingY = col)
            {
                if(kingX > row)
                {
                    max = kingX;
                    min = row;
                }//end if
                bool flag = false;
                for(int i = 0; i < numWhitePieces; i++)
                {
                    if(whitePieces[i]->getY()==col && whitePieces[i]->getX()<max && whitePieces[i]->getX() > min)
                    {
                        flag = true;
                    }
                }//end for
                if(flag == false)
                    check = true;
            }//end else
             
        }//end if  
        else if(colour == 'b')
        {
            if(kingX == row)
            {
                bool flag = false;
                for(int i = 0; i < numBlackPieces; i++)
                {
                    if(blackPieces[i]->getX()==row && blackPieces[i]->getY()<max && blackPieces[i]->getY() > min)
                    {
                        flag = true;
                    }
                }//end for
                if(flag == false)
                    check = true;
                    
            }//end if

            else if(kingY = col)
            {
                if(kingX > row)
                {
                    max = kingX;
                    min = row;
                }//end if
                bool flag = false;
                for(int i = 0; i < numBlackPieces; i++)
                {
                    if(blackPieces[i]->getY()==col && blackPieces[i]->getX()<max && blackPieces[i]->getX() > min)
                    {
                        flag = true;
                    }
                }//end for
                if(flag == false)
                    check = true;
            }//end else
             
        }//end if 
        bool tile = false;//balck is true
        int value = xPos%2;
        int value2 = yPos%2;
        int kingmodx = kingX%2;
        int kingmody = kingY%2;
        
        if( value == 0 && value2 != 0)
        {
            tile = true;
        }
        if(value !=0 && value2 == 0)
        {
            tile = true;
        }
        if(kingmodx==0 && kingmody==0)//if king on white tile but bishop on black
        {
            if(tile == true)
            {
                check = false;
            }
        }
        else if(kingmodx != 0 && kingmody != 0)
        {
            if(tile == true)
            {
                check = false;
            }
        }
        else if(kingmodx==0 && kingmody != 0)//if king on black but bishop on white
        {
            if(tile == false)
            {
                check = false;
            }
        }
        else if(kingmodx!=0 && kingmody == 0)
        {
            if(tile == false)
            {
                check = false;
            }
        }
        
        int xArr [50];//stores avaliable tiles
        int yArr [50];//stores available tiles
        
        int numX = xPos;
        int numX2 = xPos;
        int countX = 0;//for x array
        int numY = yPos;
        int numY2 = yPos;
        int countY = 0;//for y array
        for(int i  = 0; i < 8; i++)
        {
            numX = numX-1;
            numX2 = numX2 +1;
            numY = numY-1;
            numY2 = numY2 +1;
            if((numX>=0 && numX2 <8 )|| (numY>=0 && numY2 <8))
            {
                xArr[countX] = numX;
                countX++;
                xArr[countX] = numX;
                countX++;
                xArr[countX] = numX2;
                countX++;
                xArr[countX] = numX2;
                
                yArr[countY] = numY;
                countY++;
                yArr[countY] = numY2;
                countY++;
                yArr[countY] = numY;
                countY++;
                yArr[countY] = numY2;
            }
            countX++;
            countY++;
        }
        bool inWay = false;
        
            for(int i = 0; i < numBlackPieces; i++)
            {
                for(int j = 0; j <50; j++)
                {
                    if(blackPieces[i]->getX()==xArr[j] && blackPieces[i]->getY()==yArr[j])
                    {
                        inWay = true;
                    }
                }
                
            }
            
            for(int i = 0; i < numWhitePieces; i++)
            {
                for(int j = 0; j <50; j++)
                {
                    if(whitePieces[i]->getX()==xArr[j] && whitePieces[i]->getY()==yArr[j])
                    {
                        inWay = true;
                    }
                }
                
            }
            if(inWay == false)
            {
                check = true;
            }   
    }//end queen if

    else if(type == 'k')
    {
        int x1 = xPos-2;
        int x2 = xPos-2;
        int x3 = xPos+2;
        int x4 = xPos+2;
        int x5 = xPos+1;
        int x6 = xPos+1;
        int x7 = xPos+1;
        int x8 = xPos+1;
        int y1 = yPos+1;
        int y2 = yPos-1;
        int y3 = yPos-1;
        int y4 = yPos+1;
        int y5 = yPos+2;
        int y6 = yPos-2;
        int y7 = yPos+2;
        int y8 = yPos-2;
        if(kingX == x1 && kingY == y1)
        {
            check = true;
        }
        else if(kingX == x2 && kingY == y2)
        {
            check = true;
        }
        else if(kingX == x3 && kingY == y3)
        {
            check = true;
        }
        else if(kingX == x4 && kingY == y4)
        {
            check = true;
        }
        else if(kingX == x5 && kingY == y5)
        {
            check = true;
        }
        else if(kingX == x6 && kingY == y6)
        {
            check = true;
        }
        else if(kingX == x7 && kingY == y7)
        {
            check = true;
        }
        else if(kingX == x8 && kingY == y8)
        {
            check = true;
        }
    }//end if k

    else if(type == 'r')
    {
        int row = xPos;
        int col = yPos;
        int max = col;
        int min = kingY;

       
        if(kingY > col)
        {
            max = kingY;
            min = col;
        }//end if
        
        if(colour == 'w')
        {
            if(kingX == row)
            {
                bool flag = false;
                for(int i = 0; i < numWhitePieces; i++)
                {
                    if(whitePieces[i]->getX()==row && whitePieces[i]->getY()<max && whitePieces[i]->getY() > min)
                    {
                        flag = true;
                    }
                }//end for
                if(flag == false)
                    check = true;
                    
            }//end if

            else if(kingY = col)
            {
                if(kingX > row)
                {
                    max = kingX;
                    min = row;
                }//end if
                bool flag = false;
                for(int i = 0; i < numWhitePieces; i++)
                {
                    if(whitePieces[i]->getY()==col && whitePieces[i]->getX()<max && whitePieces[i]->getX() > min)
                    {
                        flag = true;
                    }
                }//end for
                if(flag == false)
                    check = true;
            }//end else
             
        }//end if  
        else if(colour == 'b')
        {
            if(kingX == row)
            {
                bool flag = false;
                for(int i = 0; i < numBlackPieces; i++)
                {
                    if(blackPieces[i]->getX()==row && blackPieces[i]->getY()<max && blackPieces[i]->getY() > min)
                    {
                        flag = true;
                    }
                }//end for
                if(flag == false)
                    check = true;
                    
            }//end if

            else if(kingY = col)
            {
                if(kingX > row)
                {
                    max = kingX;
                    min = row;
                }//end if
                bool flag = false;
                for(int i = 0; i < numBlackPieces; i++)
                {
                    if(blackPieces[i]->getY()==col && blackPieces[i]->getX()<max && blackPieces[i]->getX() > min)
                    {
                        flag = true;
                    }
                }//end for
                if(flag == false)
                    check = true;
            }//end else
             
        }//end if     
    }//end r if

    else if(type == 'b')
    {
        bool tile = false;//balck is true
        int value = xPos%2;
        int value2 = yPos%2;
        int kingmodx = kingX%2;
        int kingmody = kingY%2;
        
        if( value == 0 && value2 != 0)
        {
            tile = true;
        }
        if(value !=0 && value2 == 0)
        {
            tile = true;
        }
        if(kingmodx==0 && kingmody==0)//if king on white tile but bishop on black
        {
            if(tile == true)
            {
                check = false;
            }
        }
        else if(kingmodx != 0 && kingmody != 0)
        {
            if(tile == true)
            {
                check = false;
            }
        }
        else if(kingmodx==0 && kingmody != 0)//if king on black but bishop on white
        {
            if(tile == false)
            {
                check = false;
            }
        }
        else if(kingmodx!=0 && kingmody == 0)
        {
            if(tile == false)
            {
                check = false;
            }
        }
        
        int xArr [50];//stores avaliable tiles
        int yArr [50];//stores available tiles
        
        int numX = xPos;
        int numX2 = xPos;
        int countX = 0;//for x array
        int numY = yPos;
        int numY2 = yPos;
        int countY = 0;//for y array
        for(int i  = 0; i < 8; i++)
        {
            numX = numX-1;
            numX2 = numX2 +1;
            numY = numY-1;
            numY2 = numY2 +1;
            if((numX>=0 && numX2 <8 )|| (numY>=0 && numY2 <8))
            {
                xArr[countX] = numX;
                countX++;
                xArr[countX] = numX;
                countX++;
                xArr[countX] = numX2;
                countX++;
                xArr[countX] = numX2;
                
                yArr[countY] = numY;
                countY++;
                yArr[countY] = numY2;
                countY++;
                yArr[countY] = numY;
                countY++;
                yArr[countY] = numY2;
            }
            countX++;
            countY++;
        }
        bool inWay = false;
        
            for(int i = 0; i < numBlackPieces; i++)
            {
                for(int j = 0; j <50; j++)
                {
                    if(blackPieces[i]->getX()==xArr[j] && blackPieces[i]->getY()==yArr[j])
                    {
                        inWay = true;
                    }
                }
                
            }
            
            for(int i = 0; i < numWhitePieces; i++)
            {
                for(int j = 0; j <50; j++)
                {
                    if(whitePieces[i]->getX()==xArr[j] && whitePieces[i]->getY()==yArr[j])
                    {
                        inWay = true;
                    }
                }
                
            }
            if(inWay == false)
            {
                check = true;
            }   
    }//end b if
            
    return check;   
}


