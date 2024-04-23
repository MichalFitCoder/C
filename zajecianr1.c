#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>
// Kod Haminga

void Haming(int*tab,int *tabW);
void WykrywanieBledu(int*tab,int* tabB);

int main(){
    srand(time(0));
    int x=rand()%7,x2=0;
    int tabW[7],tabB[3],tab[4]={1,1,0,0};
    int tab40[40],tab70[70],tabB70[30];

    for(int i=0;i<40;i++){ tab40[i]=1;}

    Haming(tab,tabW);
    for(int i=0;i<10;i++){
        Haming(tab40+(i*4),tab70+(i*7));
    }
    
    //Tworzenie błędu
    if(tabW[x]) tabW[x]=0;
    else tabW[x]=1;

    for(int i=0;i<10;i++){
        x2=rand()%7;
        if(tab70[x2+(7*i)]) tab70[x2+(7*i)]=0;
        else tab70[x2+(7*i)]=1; 
    }

    printf("Kod z bledami[70]: \n");
    for(int i=0;i<70;i++){
        printf("%d ",tab70[i]);
    }
    printf("\n");

    WykrywanieBledu(tabW,tabB);
    for(int i=0;i<10;i++){
        WykrywanieBledu(tab70+(7*i),tabB70+(3*i));
    }

    printf("Kod bez bledow[70]: \n");
    for(int i=0;i<70;i++){
        printf("%d ",tab70[i]);
    }

    printf("\n\nNumer wygenerowanego bledu dla 7: %d\n",x+1);

    for(int i=0;i<7;i++){
        printf("%d ",tabW[i]);
    }
    printf("\nKod Bledu:\n");
    for(int i=2;i>=0;i--){
        printf("%d ",tabB[i]);
    }


    return 0;
}

void Haming(int*tab,int *tabW){
    int wyn=0;
    int tabH[7][4]={
        {1,1,0,1},
        {1,0,1,1},
        {1,0,0,0},
        {0,1,1,1},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}  
    };
    for(int i=0;i<7;i++){
        for(int j=0;j<4;j++){
            wyn += tab[j]*tabH[i][j];
        }
        *(tabW+i) = wyn%2;
        wyn=0;
    }
}

void WykrywanieBledu(int*tab,int*TabB){
    int kodB=0;
    int wyn=0;
    int TabP[3];
    int tabP[3][7] = {
        {1,0,1,0,1,0,1},
        {0,1,1,0,0,1,1},
        {0,0,0,1,1,1,1}
    };
    for(int i=0;i<3;i++){
        for(int j=0;j<7;j++){
            wyn += tab[j]*tabP[i][j];
        }
        *(TabB+i) = wyn%2;
        wyn=0;
    }

    //Błąd w dziesietnym 
    for(int i=0;i<3;i++){
        kodB+= *(TabB+i)*pow(2,i);
    }
    
    //Naprawianie Stworzonego Błędu
    kodB--;
    if(tab[kodB]==1) tab[kodB]=0;
    else tab[kodB]=1;
    
}