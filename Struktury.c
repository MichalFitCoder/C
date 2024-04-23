#include <stdio.h>
#include <math.h>

struct Punkt{
    float x;  
    float y;
};

struct Punkt3D{
    float x;  
    float y;
    float z;
} p3 = {0,0,0}, p4 = {1,1,1};

float odl(struct Punkt p1,struct Punkt p2){
    return sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2));
}

void srodek(struct Punkt p1,struct Punkt p2){
    printf("Srodek tych dwoch punktow to punkt S=(%f,%f)",(p1.x+p2.x)/2,(p1.y+p2.y)/2);
}

void kolo(struct Punkt p1,struct Punkt p2){
    printf("Pole kola jest rowne P=%f ,a obwód Obw=%f",M_PI*pow(odl(p1,p2),2),2*M_PI*odl(p1,p2));
}

float kula(struct Punkt3D p1,struct Punkt3D p2){
    float r = sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2)+pow(p1.z-p2.z,2));
    return pow(r,3)*M_PI*(4/3.0);
}

typedef struct ListElement {
    int data;
    struct ListElement * next;
} ListElement_type;


int main(){
    struct Punkt p1;
    struct Punkt p2; 
    p1.x=0;
    p1.y=0;
    p2.x=2;
    p2.y=2;
    
    //printf("%f",odl(p1,p2));
    //srodek(p1,p2);
    //printf("%f",M_PI);
    //kolo(p1,p2);
    //printf("%f",kula(p3,p4));

    return 0;
}