#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int min(int *tab,int n);
float srednia(int *tab,int n);
void losuj(int *tab,int n);
int ileRazy2(int *tab,int n,int liczba);

int main(){
    srand(0);
    int n = 10;
    int tab3[5] = {1,2,3,4,11};
    int tab4[] = {1,2,3,4,5,6,7,8,12,10};
    int tab5[n];
    losuj(tab5,n);

    for(int i=0;i<n;i++){
        printf("%d ",tab5[i]);
    }

    //printf("%f",srednia(tab4,sizeof(tab4)/sizeof(*tab4)));
    //Buziaka chce

    return 0;
}

int min(int *tab,int n){
    int mini = 10;
    for(int i=0;i<n;i++){
        if(mini>*(tab+i)) mini = *(tab+i);
    }
    return mini;
}

float srednia(int *tab,int n){
    float sum = 0;
    for(int i=0;i<n;i++){
        sum+=*(tab+i);
    }
    return sum/n;
}

void losuj(int *tab,int n){
    for(int i=0;i<n;i++){
        *(tab+i) = rand()%10;
    }
    //Nawet dwa
}

int ileRazy2(int *tab,int n,int liczba){
    //tab razy[]
    //Dokończe przysięgam
}