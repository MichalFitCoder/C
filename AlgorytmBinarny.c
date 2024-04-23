#include <stdio.h>



int NWD(int a,int b){
    int c = 1, x=0;
    while(a!=1 && b!=1 && a!=b){
        if(a%2==0 && b%2==0){
            a = a/2;
            b = b/2;
            c *=2;
        }
        else if(a%2 == 1 && b%2 == 1){
            x=a;
            if(a>b){
                a = b;
            }
            if(a>=b) b = x - b;
            else b = b - x;
        }
        else if(a%2==1 && b%2==0){
            b = b/2;
        }
        else if(a%2==0 && b%2==1){
            a = a/2;
        }
    }
    if (b == 1) return c;
    else return a*c;
}


int main(){

    printf("%d",NWD(25234,110110));
    return 0;
}