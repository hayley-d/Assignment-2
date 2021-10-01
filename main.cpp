#include<iostream>
#include "piece.h"
#include "board.h"
int main ()
{
    /*piece p("wq", 'w', 3, 4);
    std::cout << p.getPieceType() << std::endl;
    piece* ptr = &p;
    piece j(ptr);
    std::cout<<p.getSide()<<" "<<j.getSide()<<std::endl;*/
    board b("game1.txt");//works
    //std::cout<<"here"<<std::endl;
    //b--;
    board &c = b.operator--();
    return 0;
}
