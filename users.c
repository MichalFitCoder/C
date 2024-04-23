#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct User{
    int id;
    char name[50];
    char surname[50];
    char nationality[50];
    int age;
    float weight;
    float height;
    float salary;
    short int married;
    short int hired; 
};

void AddUser(struct User *base,int id,char name[50],char surname[50], char nationality[50]
,int age, float weight, float height, float salary, short int married, short int hired){  

    (struct User*)realloc(base,(id+1)*sizeof(struct User));
    (base+id)->id = id;
    strcpy((base+id)->name,name);
    strcpy((base+id)->surname,surname);
    strcpy((base+id)->nationality,nationality);
    (base+id)->age = age;
    (base+id)->weight = weight;
    (base+id)->height = height;
    (base+id)->salary = salary;

    if(married != 1 && married != 0 && hired !=1 && hired !=0) printf("Nieprawidlowa wartosc parametrow married hired (True/False)");
    (base+id)->married = married;
    (base+id)->hired = hired;
    printf("Uzytkownik %s zostal dodany do bazy danych\n",name);
}

void ShowUser(struct User *base,int id){
    //printf("%d\n %d",(base+id)->id,(base+id)->age);
    printf("Id Uzytkownika: %d\nImie: %s\nNazwisko %s\nNarodowosc : %s\nwiek: %d\nwaga: %.2fkg\nwzrost: %.2fcm\nwynagrodzenie: %.2fzl\nzatrudniony: %d\nw zwiazku malzenskim: %d\n",(base+id)->id,(base+id)->name,(base+id)->surname,(base+id)->nationality,(base+id)->age,(base+id)->weight,(base+id)->height,(base+id)->salary,(base+id)->hired,(base+id)->married);    
}

void ShowAll(struct User *base,int size){
    printf("\n");
    for(int i=0;i < size;i++){
        ShowUser(base,i);
        printf("\n\n");
    } 
}

void DeleteUser(struct User *base,int id,int size){
    printf("Uzytkownik %s zostal usuniety\n",(base+id)->name);
    for(int i = id;i<size-1;i++){
        strcpy((base+i)->name,(base+i+1)->name);
        strcpy((base+i)->surname,(base+i+1)->surname);
        strcpy((base+i)->nationality,(base+i+1)->nationality);
        (base+i)->age = (base+i+1)->age;
        (base+i)->weight = (base+i+1)->weight;
        (base+i)->height = (base+i+1)->height;
        (base+i)->married = (base+i+1)->married;
        (base+i)->hired = (base+i+1)->hired;
    }
    (struct User*)realloc(base,(size-1)*sizeof(struct User));  
}

void AddUserKeyboard(struct User *base,int rozmiar_bazy){

    char name[50];
    char surname[50];
    char nationality[50];
    float age;
    float weight;
    float height;
    float salary;
    short int married;
    short int hired;

    printf("Podaj Imie: ");
    scanf("%s", &name);
    printf("Podaj Nazwisko: ");
    scanf("%s", &surname);
    printf("Podaj Narodowosc: ");
    scanf("%s", &nationality);
    printf("Podaj wiek: ");
    scanf("%d", &age);
    printf("Podaj wage: ");
    scanf("%f", &weight);
    printf("Podaj wzrost: ");
    scanf("%f", &height);
    printf("Podaj Zarobki: ");
    scanf("%f", &salary);
    printf("Czy jest w zwiazku malrzenskim: ");
    scanf("%d", &married);
    printf("Czy jest zatrudniony: ");
    scanf("%d", &hired);
    AddUser(base,rozmiar_bazy,name,surname,nationality,age,weight,height,salary,married,hired);
}

int main(){
    int a = 0,rozmiar_bazy = 1,id=0;
    // Tworzenie bazy danych
    struct User* base;
    base = (struct User*)malloc(sizeof(struct User));

    AddUser(base,0,"Michal","Gad","Polska",23,79,184,5400,0,1);

    while(a !=5){
        printf("---------------Podaj numer opcji----------------\n");
        printf("1.Dodaj uzytkownika\n");
        printf("2.Wyswietl uzytkownika\n");
        printf("3.Wyswietl uzytkownikow\n");
        printf("4.Usun uzytkownika\n");
        printf("5.Zakoncz program\n");
        scanf("%d",&a);
    switch(a){
        case 1:
            AddUserKeyboard(base,rozmiar_bazy);
            rozmiar_bazy++;
            break;
        case 2:
            printf("Podaj id uzytkownika: \n");
            scanf("%d",&id);
            ShowUser(base,id);
            break;
        case 3:
            if(rozmiar_bazy==0) printf("Baza Danych jest pusta\n");
            else ShowAll(base,rozmiar_bazy);
            break;
        case 4:
            printf("Podaj id uzytkownika: \n");
            scanf("%d",&id);
            DeleteUser(base,id,rozmiar_bazy);
            rozmiar_bazy--;
            break;
        case 5:
            printf("Dziekuje za korzystanie z programu!\n");
            break;
        default:
        printf("Niepoprawny numer\n");
    }
    }
    free(base);
    return 0;
}