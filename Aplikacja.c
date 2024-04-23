#include<stdio.h>


void tab_cpy(int *tab1, int *tab2,int size);
void ctab_cpy(char **tab1, char **tab2,int size);
int main(){
    int tab[] = {1232,42115,5354,262,6322};
    int tablica[5] = {0,0,0,0,0};

    char *imiona[]={"Michal", "Kacper","Bartek","Jan","Karol"};
    char *pusta[5];

    ctab_cpy(imiona,pusta,5);
    //printf("%d",sizeof tab/sizeof *tab);
    tab_cpy(tab,tablica,5);
    for(int i=0;i<sizeof tab/sizeof *tab;i++){
        //printf("%d\n",tablica[i]);
        printf("%s\n",pusta[i]);

    }

    return 0;
}

void tab_cpy(int *tab1,int *tab2,int size){
    for(int i=0;i<size;i++){
        *tab2=*tab1;
        tab1++;
        tab2++;
    }
}

void ctab_cpy(char **tab1, char **tab2,int size){
    for(int i=0;i<size;i++){
        *tab2=*tab1;
        tab1++;
        tab2++;
    }
}
