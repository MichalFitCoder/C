#include<stdio.h>

int silnia(int a);
double Newton(double a,double b);
//void test();

int main(){
int ile_razy = 0,najczestrza=0;
int tab[] ={1,2,3,4,1,2,3,4,1,5,5,5,5,7,7,7,7,7,7,7,7,7,7,7,7,7};
int licznik[10];
    for(int i=0;i<10;i++){
    licznik[i]=0;
    }

    for(int i=0;i<(sizeof tab/sizeof *tab);i++){
    licznik[tab[i]]++; 
    }
    for(int i=0;i<10;i++){
        if(licznik[i]>ile_razy) {
        ile_razy=licznik[i];
        najczestrza = i;
        }
    }
    printf("Najczestrza jest %d, wystapila %d razy",najczestrza,ile_razy);


    return 0;
}
int silnia(int a){
    if(a==1) return 1;
    return a*silnia(a-1);
}
void test(){
    static int licznik = 1;
    printf("Wywołane po raz %d\n",licznik);
    licznik++;
}