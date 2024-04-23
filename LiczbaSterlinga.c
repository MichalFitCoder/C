#include <stdio.h>

int liczbaSterlinga(int a,int b);

int main(){

    printf("%d",liczbaSterlinga(5,3));
    return 0;
}
int liczbaSterlinga(int a,int b){
    if (a==b) return 1;
    if (b==0 ) return 0;
    if (b>a) return 0;
    return (a-1)*liczbaSterlinga(a-1,b)+liczbaSterlinga(a-1,b-1);
}
 