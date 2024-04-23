#include <stdio.h>

void wyswietl(int **tab);
int main(){
    /*char napis[20] = "Siema co tam  ";
    char *p =&napis[0];
    while(*p){
        printf("%c",*p++);
    }*/
    //int x = 100;
    //int *p = &x;
    int tab[3][3]= {{1,23,31},{432,10,631},{327,832,94}};
    int *wtab1=tab[3];
    int **wtab2=&wtab1;
    //printf("adress %d",tab);
    wyswietl(wtab2);
    //printf("%d",*p);
    return 0;
}
void wyswietl(int **tab){
    printf("tablica %d",*(tab+4));
}
