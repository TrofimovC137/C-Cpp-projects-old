#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>


using namespace std;
class Color{
public:
    int R;
    int G;
    int B;
    Color();
    Color(int tR,int tG,int tB);
};
Color::Color(){
    int R=255;
    int G=255;
    int B=255;
}
Color::Color(int tR,int tG,int tB){
    R=tR;
    G=tG;
    B=tB;
}
class Position{
public:
    double y;
    double x;
    Position();
    Position(double tx,double ty);
};
Position::Position(double tx, double ty){
    x=tx;
    y=ty;
}
Position::Position(){
    x=0;
    y=0;
}
class Line{
    //y=ax+b
public:
    double a;
    double b;
    Position p1;
    Position p2;
    Line(Position tp1, Position tp2);
    double Position_relative_to_the_line(Position tp);
};
Line::Line(Position tp1,Position tp2){
    p1=tp1;
    p2=tp2;
    a=(tp2.y-tp1.y)/(tp2.x-tp1.x);
    b=(tp1.x*tp2.y-tp1.x*tp1.y)/(tp2.x-tp1.x)+tp1.y;
}
double Line::Position_relative_to_the_line(Position tp){
    if (((tp.x<p1.x)&&(tp.x<p2.x))||((tp.x>p1.x)&&(tp.x>p2.x))){
        return 0;
    }
    else if(((tp.y<p1.y)&&(tp.y<p2.y))||((tp.y>p1.y)&&(tp.y>p2.y))){
        return 0;
    }
    else{
        if(abs(tp.y)-abs((a*tp.x+b))<0){
            return -1;
        }
        else return 1;
    }
}
void drow_line(Color** image, Line l,Color p){
    if(l.p1.x<l.p2.x){
        for(int i=(int)(l.p1.x);i<l.p2.x;i++){
            image[i][(int)(l.a*i+l.b)]=p;
        }
    }
    else{
        for(int j=(int)(l.p2.x);j<l.p1.x;j++){
            //image[i][(int)(l.a*i+l.b)]=p;
        }
    }
}

class House{
    vector<Position> positions;
public:
    vector<Line> lines;
    House(vector<Position> p);
};
House::House(vector<Position> p){
    for (int i=0;i<p.size();i++){
        positions.push_back(p[i]);
    }
    for (int i=0;i<p.size()-1;i++){
        lines.push_back(Line(p[i],p[i+1]));
    }
    lines.push_back(Line(p[0],p[p.size()-1]));
}

class Map{
    vector<House> Houses;
    Color** image;
    int mx;
    int my;
    void show_house(Color house_color);
public:
    Map(Color field_color,int tmx,int tmy);
    ~Map();
    void addHouse(House new_house);
    void show();
    int GetMx();
    int GetMy();
};
int Map::GetMx(){
    return mx;
}
int Map::GetMy(){
    return my;
}
Map::Map(Color field_color,int tmx,int tmy){
    mx=tmx;
    my=tmy;
    image=new Color*[mx];
    for(int i=0;i<mx;i++){
        image[i]=new Color[my];
        for(int j=0;j<my;j++){
            image[i][j]=field_color;
        }
    }
}
Map::~Map(){
    for (int i=0;i<mx;i++){
        delete image[i];
    }
    delete image;
    mx=0;
    my=0;
}
void Map::addHouse(House new_house){
    Houses.push_back(new_house);
}
void Map::show(){
    FILE* fp=fopen("kartinka.pnm","w");
    fprintf(fp,"P3\n");
    fprintf(fp,"%d %d\n",mx,my);
    fprintf(fp,"255\n");
    Color house_color(0,0,0);
    show_house(house_color);
    for(int i=my-1;i>=0;i--){
        for (int j=0;j<mx;j++){
            fprintf(fp,"%d %d %d\n",image[j][i].R,image[j][i].G,image[j][i].B);
        }
    }
    fclose(fp);
}
void Map::show_house(Color house_color){
    vector<Line> all_line;
    int number_of_house=Houses.size();
    for(int i=0;i<number_of_house;i++){
        int number_of_line_in_house=Houses[i].lines.size();
        for(int j=0;j<number_of_line_in_house;j++){
            all_line.push_back(Houses[i].lines[j]);
        }
    }
    /*Position current_position(0,0);
    vector<float> distance_to_the_line;
    for (int i=0;i<all_line.size();i++){
        distance_to_the_line.push_back(all_line[i].Position_relative_to_the_line(current_position));
    }*/
    printf("%d\n",all_line.size());
    for(int i=0;i<all_line.size();i++){
        printf("x %f y %f | x %f y%f\n",all_line[i].p1.x,all_line[i].p1.y,all_line[i].p2.x,all_line[i].p2.y);
        drow_line(image,all_line[i],house_color);
    }
    /*for (int x=0;x<mx;x++){
        int Number_of_lines_passed=0;
        for(int y=0;y<my;y++){
            current_position.x=x;
            current_position.y=y;
            for(int i=0;i<all_line.size();i++){
                if((all_line[i].Position_relative_to_the_line(current_position))*distance_to_the_line[i]<0){
                    Number_of_lines_passed++;
                }
                distance_to_the_line[i]=all_line[i].Position_relative_to_the_line(current_position);
            }
            if(((Number_of_lines_passed%2)!=0)&&(Number_of_lines_passed!=0)){
                image[x][y]=house_color;
            }
        }
    }*/
}


int main()
{
    Color c(255,255,255);
    vector<Position> p;
    p.push_back(Position(10.0,10.0));
    p.push_back(Position(80.0,87.0));
    p.push_back(Position(33.0,50.0));
    House h(p);
    Map m(c,100,100);
    m.addHouse(h);
    m.show();
    return 0;
}
