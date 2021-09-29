#include<iostream>
#include "piece.h"
int main ()
{
    piece p("wq", 'w', 3, 4);
    piece* ptr = &p;
    piece j(ptr);
    std::cout<<p.getSide()<<" "<<j.getSide()<<std::endl;
    return 0;
}
