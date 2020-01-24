#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;
class Image{
    vector<int> mas;
    int mx;
    int my;
public:
    Image(int tmx,int tmy);
    void load(char* filename);
    int At(int tx,int ty);
    void Set(int tx,int ty,int tcolor);
    void show();
    int GetMx();
    int GetMy();
    bool operator>(Image& a);
};
Image::Image(int tmx, int tmy){
    mx=tmx;
    my=tmy;
    for(int i=0;i<(tmx*tmy);i++){
        mas.push_back(0);
    }
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
void Image::load(char* filename){
    FILE* fp=fopen(filename,"r");
    for(int i=0;i<3;i++)fgetc(fp);
    int tmx=fgetint(fp);
    int tmy=fgetint(fp);
    if(mx*my<tmx*tmy){
        for(int i=0;i<(tmx*tmy-mx*my);i++){
            mas.push_back(0);
        }
    }
    mx=tmx;
    my=tmy;
    for(int i=0;i<mx*my;i++){
        mas[i]=fgetint(fp);
    }
}
int Image::At(int tx,int ty){
    return mas[ty*mx+tx];
}
void Image::Set(int tx,int ty,int tcolor){
    mas[ty*mx+tx]=tcolor;
}
void Image::show(){
    for(int i=0;i<mx;i++){
        for(int j=0;j<my;j++){
            printf("%d ",At(i,j));
        }
    printf("\n");
    }
}
int Image::GetMx(){
    return mx;
}
int Image::GetMy(){
    return my;
}
struct ImgCompore{
    Image*teamplate;
public:
    bool operator()(Image &a, Image &b);
};
vector<int> gistogramma(Image* a){
    vector<int> res;
    for(int i=0;i<255;i++){
        res.push_back(0);
    }
    int mx=a->GetMx();
    int my=a->GetMy();
    for(int i=0;i<mx;i++){
        for(int j=0;j<my;j++){
            res[a->At(i,j)]++;
        }
    }
    return res;
}
int metric(vector<int> v,vector<int> vt){
    int result=0;
    int Size=v.size();
    for(int i=0;i<Size;i++){
        result+=((v[i]-vt[i])*(v[i]-vt[i]));
    }
    return sqrt(result);
}
int metric0(vector<int> v){
    int result=0;
    int Size=v.size();
    for(int i=0;i<Size;i++){
        result+=(v[i]*v[i]);
    }
    return sqrt(result);
}
int comp( Image a,  Image b){
    vector<int>BGist=gistogramma(&b);
    vector<int>AGist=gistogramma(&a);
    int SelfMetric=metric0(BGist);
    int AMetric=metric0(AGist);
    if(SelfMetric>AMetric){
        return 1;
    }
    else{
        return 0;
    }
}
bool ImgCompore::operator()(Image &a,Image &b){
    vector<int>AGist=gistogramma(&a);
    vector<int>BGist=gistogramma(&b);
    vector<int>TempGist=gistogramma(teamplate);
    int MetricA=metric(AGist,TempGist);
    int MetricB=metric(BGist,TempGist);
    if(MetricA>MetricB){
        return 1;
    }
    else{
        return 0;
    }
}
void show_image_vector(vector<Image> vec){
    int vector_size=vec.size();
    if (vector_size>0){
        int mx=vec[0].GetMx();
        int my=vec[0].GetMy();
        for(int y=0;y<my;y++){
            for(int n=0;n<vector_size;n++){
                for(int x=0;x<mx;x++){
                    printf("%d ",vec[n].At(x,y));
                }
                printf("  ");
            }
            printf("\n");
        }
    }
    printf("\n");
}
int main()
{
    Image I1(3,3);
    I1.load("1.TXT");
    Image I2(3,3);
    I2.load("2.TXT");
    Image I3(3,3);
    I3.load("3.TXT");
    Image I4(3,3);
    I4.load("4.TXT");
    Image S(3,3);
    S.load("sort.TXT");
    ImgCompore IS;
    IS.teamplate=&S;
    vector<Image> vec;
    vec.push_back(I1);
    vec.push_back(I3);
    vec.push_back(I2);
    vec.push_back(I4);
    printf("before sorting\n");
    show_image_vector(vec);
    sort(vec.begin(),vec.end(),comp);
    printf("after sorting\n");
    show_image_vector(vec);
    printf("model element:\n");
    S.show();
    return 0;
}
