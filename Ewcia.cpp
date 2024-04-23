#include <stdio.h>

// void wyswietl(float **tab,int n,int m); 
void wyswietl(float ** tab,int n,int m){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            // printf("%f ",tab[i + j * m]);   
        }
        printf("\n");
    }
}

int main(){
    float tab[3][3]= {{1,2,3},{4,5,6},{7,8,9}};

    wyswietl(tab,3,3);
    
    
    return 0;
}



