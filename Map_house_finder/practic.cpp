#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;
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
    Position GetP1();
    Position GetP2();
    Line (Position tp1, Position tp2);
    void Drow_line(Pixel** image, Pixel color);
};
Line::Line(Position tp1, Position tp2){
    p1=tp1;
    p2=tp2;
    a=(p2.y-p1.y)/(p2.x-p1.x);
    b=((p1.y-a*p1.x)+(p2.y-a*p2.x))/2;
}
Position Line::GetP1(){
    return p1;
}
Position Line::GetP2(){
    return p2;
}
float mod(float value){
    if(value>=0){
        return value;
    }
    else{
        return value*(-1);
    }
}
void Line::Drow_line(Pixel** image, Pixel color){
    float x=p1.x;
    float y;
    float d=0.0001;
    printf("x1=%f y1=%f x2=%f y2=%f\n",p1.x,p1.y,p2.x,p2.y);
    printf("y=%f*x+%f\n",a,b);
    printf("__________________________________________\n");
    while(mod(x-p2.x)>0.0001){
        y=a*x+b;
        if ((x-p2.x)<0){
            x=x+d;
        }
        else{
            x=x-d;
        }
        image[616-(int)y][(int)x]=color;
    }
}
int fgetint(FILE* fp){
    int result=0;
    char c;
    c=fgetc(fp);
    while ((c!=' ')&&(c!='\n')&&(c!=EOF)&&(c!='.')){
        result+=(int(c)-48);
        result*=10;
        c=fgetc(fp);
    }
    result/=10;
    return result;
}
float fgetfloat(FILE* fp){
    float result=0;
    float whole_part=fgetint(fp);
    float fraction=fgetint(fp);
    while (fraction>1){
        fraction*=0.1;
    }
    result=whole_part+fraction;
    return result;
}
class House{
    vector<Line> Lines;
public:
    void Draw_house(Pixel** image,Pixel color);
    void Add_line(Line l);
    void print_line();
};
void House::Add_line(Line l){
    Lines.push_back(l);

}
void House::print_line(){
    for(int i=0;i<Lines.size();i++){
        printf("x1=%f y1=%f || x2=%f y2=%f\n",Lines[i].GetP1().x,Lines[i].GetP1().y,Lines[i].GetP2().x,Lines[i].GetP2().y);
    }
}
void House::Draw_house(Pixel** image,Pixel color){
    for(int i=0;i<Lines.size();i++){
        Lines[i].Drow_line(image,color);
    }
}
class Map{
    int mx;
    int my;
    Pixel** image;
    vector<House> Houses;
public:
    Map(int mx, int my);
    ~Map();
    void Load_image(char* filename);
    void show();
    int Get_mx();
    int Get_my();
    void Add_house(House h);
};
Map::Map(int tmx,int tmy){
    mx=tmx;
    my=tmy;
    Pixel color;
    color.R=255;color.G=255;color.B=255;
    image=new Pixel*[mx];
    for(int i=0;i<mx;i++){
        image[i]=new Pixel[my];
        for(int j=0;j<my;j++){
            image[i][j]=color;
        }
    }
}
Map::~Map(){
    for(int i=0;i<mx;i++){
        delete image[i];
    }
    delete image;
}
int Map::Get_mx(){
    return mx;
}
int Map::Get_my(){
    return my;
}
void Map::show(){
    Pixel color;
    color.R=0;color.G=0;color.B=0;
    for(int i=0;i<Houses.size();i++){
        Houses[i].Draw_house(image,color);
    }
    FILE* fp=fopen("result.pnm","w");
    fprintf(fp,"P3\n");
    fprintf(fp,"%d %d\n",mx, 616);
    fprintf(fp,"255\n");
    for(int i=0;i<mx;i++){
        for(int j=0;j<my;j++){
                fprintf(fp,"%d %d %d\n",image[i][j].R,image[i][j].G,image[i][j].B);
        }
    }
    fclose(fp);
}
void Map::Add_house(House h){
    Houses.push_back(h);
}
void Map::Load_image(char* filename){
    FILE* fp=fopen(filename,"r");
    for (int i=0;i<10;i++){
        fgetint(fp);
    }
    for(int i=0;i<mx;i++){
        for(int j=0;j<my;j++){
            image[i][j].G=fgetint(fp);
            image[i][j].B=fgetint(fp);
            image[i][j].R=fgetint(fp);
        }
    }
    fclose(fp);
}
Position coord_to_pixel(Position Min,Position Max,Position p){
    p.x=(950/(Max.x-Min.x))*(p.x-Min.x);
    p.y=(616/(Max.y-Min.y))*(p.y-Min.y);
    return p;
}
void Print_Image(char* image_filename, char* coordinats_filename){
    FILE* fcoord=fopen(coordinats_filename,"r");
    FILE* fimage=fopen(image_filename,"r");
    Map m(fgetint(fcoord),fgetint(fcoord));
    m.Load_image(image_filename);
    Position Min(fgetfloat(fcoord),fgetfloat(fcoord));
    Position Max(fgetfloat(fcoord),fgetfloat(fcoord));
    House hous;
    Position p0;
    Position new_pos;
    Position old_pos;
    for(int i=0;i<4;i++){
        if(i==0){
            p0.y=fgetfloat(fcoord);
            p0.x=fgetfloat(fcoord);
            p0=coord_to_pixel(Min,Max,p0);
            old_pos=p0;
            new_pos=coord_to_pixel(Min,Max,Position(fgetfloat(fcoord),fgetfloat(fcoord)));
            hous.Add_line(Line(p0,new_pos));
        }
        else{
            if(i==3){
                old_pos=new_pos;
                hous.Add_line(Line(old_pos,p0));
            }
            else{
                old_pos=new_pos;
                new_pos=coord_to_pixel(Min,Max,Position(fgetfloat(fcoord),fgetfloat(fcoord)));
                hous.Add_line(Line(old_pos,new_pos));
            }
        }
    }
    m.Add_house(hous);
    m.show();
    fclose(fcoord);
    fclose(fimage);
}
int main(){
    Print_Image("mai.pnm","coordinats.txt");
    return 0;
}
