#include <stdio.h>



int main(){
    int macierzA[3][3] ={
        {1,2,5},
        {1,2,3},
        {1,2,3}
    };
    int macierzB[3][3] ={
        {2,4,3},
        {2,1,3},
        {2,4,3}
    };
    
    //dodawanie
    int tabsuma[3][3];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            tabsuma[i][j]=macierzA[i][j] + macierzB[i][j];
        }
    }
    //Odejmowanie
    int tabiloczyn[3][3];
    int tabroznica[3][3];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            tabroznica[i][j]=macierzA[i][j] - macierzB[i][j];
            tabiloczyn[i][j]=0;
        }
    }
    //Mnożenie
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            for (int k=0;k<3;k++){
            tabiloczyn[i][j]+=macierzA[i][k] * macierzB[k][j] ;
            }
        }
    }
    // Dodana macierz
    printf("Suma macierzy A i B: \n");
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf("%d ",tabiloczyn[i][j]);
        }
        printf("\n");
    }
}


