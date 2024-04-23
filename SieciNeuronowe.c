#include<stdio.h>

void MatrixMultiply(float *x,float*v){
    
    //Macierz wag
    double w1[5][3] = 
    {   
        0.7, 0.6, 1.4,
        0.1, 0.2, 2.1,
        1.7, 1.1, 0.3,
        4.3,0.1, 0.1, 
        0.2, 0.1, 0.6
    };

    //Wektor Biasu
    float b1[5] = {
        10,8,4,6,1
    };

    for(int i =0;i<5;i++){
        for(int j=0;j<3;j++){
            v[i]+=x[j]*w1[i][j];
        }
        v[i]+=b1[i];
    }
}

void MatrixMultiplyw2(float *v1,float*v){
    
    //Macierz wag
    double w2[5][5] = 
    {   
        2.1, 3.5, 1.4, 0.1, 0.3, 
        2.5, 2.7, 3.2, 0.45, 4.3,
        0.1, 0.1, 0.2, 0.1, 0.6,
        2.5, 2.7, 3.2, 0.45, 4.3,
        2.1, 1.5, 4.4, 0.1, 0.3
    };

    //Wektor Biasu
    float b2[5] = {
        1,4,3,5,1
    };

    for(int i =0;i<5;i++){
        for(int j=0;j<5;j++){
            v[i]+=v1[j]*w2[i][j];
        }
        v[i]+=b2[i];
    }
}
void MatrixMultiplyw3(float *y,float*v){
    
    //Macierz wag
    double w3[5] = 
    {   
        0.1, 0.7, 0.4, 0.1, 0.3
    };

    //Wektor Biasu
    float b3[5] = {
        3,1,3,1,5
    };

        for(int i=0;i<5;i++){
            *y+=v[i]*w3[i];
            *y+=b3[i];
        }
        
}

void Factiv(float *v){
    // Funkcja aktywacji y = 2x+0
    for(int i=0;i<5;i++){
        v[i] = 2* v[i];
    }
}


int main(){
    //wektor wejścia
    float x[3] = {10,5,15};
    //Neuron wyjscia
    float y=0;
    

    double w2[5][5] = 
    {   
        2.1, 5.5, 6.4, 0.1, 0.3, 
        2.5, 2.7, 3.2, 0.45, 4.3,
        0.1, 0.1, 0.2, 0.1, 0.6,
        2.5, 2.7, 3.2, 0.45, 4.3,
        2.1, 1.5, 4.4, 0.1, 0.3
    };

    //Wektory warstwy ukrytej
    float v1[5]={0,0,0,0,0};
    float v2[5]={0,0,0,0,0};;

    MatrixMultiply(x,v1);
    Factiv(v1);
    MatrixMultiplyw2(v1,v2);
    Factiv(v2);
    MatrixMultiplyw3(&y,v2);
    //Funkcja Aktywacji
    y *=2;

    for(int i=0;i<5;i++){
        printf("%.2f  ",v1[i]);
    }
    printf("\n");
    for(int i=0;i<5;i++){
        printf("%.2f  ",v2[i]);
    }
    printf("\n%.2f",y);

    return 0;
}