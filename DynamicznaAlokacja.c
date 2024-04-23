#include<stdio.h>
#include<stdlib.h>

int main(){
    int n;
    int flaga = 0,k=0;
    int *tab = (int*)malloc(sizeof(int));

    printf("Podaj do jakiej liczby szukamy liczb pierwszych: ");
    scanf("%d",&n);
    for(int i=2;i<n;i++){
    for(int j=2;j*j<=i;j++){
        if(i%j==0){
        flaga = 1;
        break;
        }     
    }
    if(flaga==0) {
        *(tab+k) = i;
        k++;
        tab = realloc(tab,sizeof(int)*(k+1)); 
        if(tab==NULL) printf("There is no memory");
    }
    flaga = 0;
    }

    for(int i=0;i<k;i++){
        printf("%d ",*(tab+i));
    }

    return 0;
}