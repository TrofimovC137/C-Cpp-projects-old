#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
template<class T>
class CyclBuf{
    int Size;
    int NumberOfElements;
    int WriteIndex;
    int ReadIndex;
    T* Array;
public:
    CyclBuf();
    CyclBuf(int tSize);
    ~CyclBuf();
    void Push(T Value);
    T Pop();
};
template<class T>
CyclBuf<T>::CyclBuf(){
    Array=new T(100);
    Size=100;
    NumberOfElements=0;
    WriteIndex=0;
    ReadIndex=0;
}
template<class T>
CyclBuf<T>::CyclBuf(int tSize){
    Array=new T(Size);
    Size=tSize;
    NumberOfElements=0;
    WriteIndex=0;
    ReadIndex=0;
}
template<class T>
CyclBuf<T>::~CyclBuf(){
    delete Array;
    Size=0;
    NumberOfElements=0;
    WriteIndex=0;
    ReadIndex=0;
}
template <class T>
void CyclBuf<T>::Push(T Value){
    if (NumberOfElements<Size){
        Array[WriteIndex]=Value;
        WriteIndex++;
        NumberOfElements++;
        if(WriteIndex==Size){
            WriteIndex=0;
        }
    }
    else{
        exit(-1);
    }
}
template <class T>
T CyclBuf<T>::Pop(){
    if(NumberOfElements>0){
        T result=Array[ReadIndex];
        ReadIndex++;
        NumberOfElements--;
        if (ReadIndex==Size){
            ReadIndex=0;
        }
        return result;
    }
    else{
        exit(-1);
    }
}
int main()
{
    CyclBuf<int> a;
    for(int i=0;i<100;i++){
        a.Push(i);
        a.Pop();
    }
    return 0;
}
