#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <thread>

using namespace std;

class Ball{
public:
    int id;
    int TTL;
    int x;
    int y;
    int vy;
    int Move(int dt, int MaxY);
};
int Ball::Move(int dt,int MaxY){
    TTL-=dt;
    y+=vy*dt;
    if((y<0)||(y>MaxY)){
        vy*=(-1);
    }
    if(TTL<=0){
        return 1;
    }
    else{
        return 0;
    }
}
class Box{
    int Time;
    int Dt;
    int MaxY;
    int BoxSize;
    vector<Ball> balls;
public:
    Box(int dt, int tMaxY);
    void model();
    void add(char* filename);
};
struct ReadBall{
    Ball a;
    int AddTime;
};
Box::Box(int dt, int tMaxY){
    MaxY=tMaxY;
    Time=0;
    Dt=dt;
}
int fgetint(FILE* fp){
    int result=0;
    char c;
    c=fgetc(fp);
    while ((c!=' ')&&(c!='\n')&&(c!=EOF)){
        result+=(int(c)-48);
        result*=10;
        c=fgetc(fp);
    }
    result/=10;
    return result;
}
void Box::model(){
    while(1){
        int i=0;
        int BoxSize=balls.size();
        while(i<BoxSize){
            if(balls[i].Move(Dt,MaxY)){
                balls.erase(balls.begin()+i);
            }
            i++;
        }
    }
}
void Box::add(char* filename){
    FILE* fp=fopen(filename,"w");
    vector<ReadBall> ReadBalls;
    int Size=fgetint(fp);
    ReadBall RB;
    for(int i=0;i<Size;i++){
        RB.AddTime=fgetint(fp);
        RB.a.id=fgetint(fp);
        RB.a.x=fgetint(fp);
        RB.a.y=fgetint(fp);
        RB.a.vy=fgetint(fp);
        RB.a.TTL=100;
        ReadBalls.push_back(RB);
    }
    while(1){
        for(int i=0;i<ReadBalls.size();i++){
            if((ReadBalls[i].AddTime)>Time){
                if(balls.size()==BoxSize){
                    balls.push_back(ReadBalls[i].a);
                }
                else{
                    balls[i]=ReadBalls[i].a;
                }
                BoxSize++;
            }
        }
    }
}
int main()
{
    Box B(1,10);
    thread read(&Box::add,this,"1.TXT");
    thread Model(&Box::model,this);
    return 0;
}
