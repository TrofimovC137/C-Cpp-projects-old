#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

class Position{
public:
    double x;
    double y;
    Position(double tx,double ty);
    Position();
};
Position::Position(double tx,double ty){
    x=tx;
    y=ty;
}
Position::Position(){
    x=0;
    y=0;
}
class Pixel{
public:
    int R;
    int G;
    int B;
    Pixel();
    Pixel(int R,int G,int B);
};
Pixel::Pixel(){
    R=255;
    G=255;
    B=255;
}
Pixel::Pixel(int tR,int tG,int tB){
    R=tR;
    G=tG;
    B=tB;
}
class Hous{
public:
    Position real_coordinat;
    Position image_coordinat;
};
class Map{
    Pixel** image;
    int mx;
    int my;
public:
    Map(int tmx,int tmy);
    ~Map();
};
Map::Map(int tmx,int tmy){
    mx=tmx;
    my=tmy;
    image=new Pixel*[mx];
    for(int i=0;i<mx;i++){
        image[i]=new Pixel[my];
    }
}
Map::~Map(){
    for(int i=0;i<mx;i++){
        delete image[i];
    }
    delete image;
    mx=0;
    my=0;
}
int main(){
    return 0;
}
