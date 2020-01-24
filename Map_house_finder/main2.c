#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

struct Position{
    int x;
    int y;
};
struct Pixel{
    int R;
    int G;
    int B;
};
class Line{
    Position p1;
    Position p2;
    //y=ax+b
    double a;
    double b;
public:
    Line (Position tp1, Position tp2);
    void drow_line()
};
