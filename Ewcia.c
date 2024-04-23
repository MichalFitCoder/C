#include <stdio.h>

void wyswietl(float *tab,int n,int m){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%f ",tab[i * m + j]);   
        }
        printf("\n");
    }
}

void wczytaj(float *tab,int n,int m){
     for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%f",tab+j+i*m);   
        }
    }
}

float suma(float *tab,int n,int m){
    float wyn=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
           wyn += tab[i * m + j];
        }
    }
    return wyn;
}

float srednia(float *tab,int n,int m){
    return suma(tab,n,m)/(n*m);
}

float przekatna(float *tab,int n){
float wyn=1;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
           if(i==j)wyn *= tab[i * n + j];
        }
    }

return wyn;
}

float nadprzekatna(float *tab,int n){
    float wyn=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
           if(j>i)wyn += tab[i * n + j];
        }
    }
    return wyn;
}



#define N 3
#define M 3

int main(){
    float tab[N][M];
    wczytaj((float*)tab,N,M);
    //printf("%f\n",srednia((float*)tab,N,M));
    wyswietl((float*)tab,N,M);
    printf("\n%f",nadprzekatna((float*)tab,N));
    
    
    return 0;
}



