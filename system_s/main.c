#include <stdio.h>
#include <stdlib.h>
int ten_any_system(int number,int base){
    int res=0;
    int i=1;
    while (number>=base){
        res+=(number%base)*i;
        i*=10;
        number=number/base;
    }
    res+=number*i;
    return res;
    }
int main()
{
    int number;
    int base;
    printf("specify the number of the number system\n");
    scanf("%d%d",&number,&base);
    printf("%d",ten_any_system(number,base));
    return 0;
}
