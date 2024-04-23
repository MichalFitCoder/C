//====================================================================================================
// Teoria Informacji i Kodowania - Michał Gogacz  ćwiczenie laboratoryjne nr 3
//====================================================================================================
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFSIZE 216 // rozmiar tablicy bufora
#define fileNameSize 30 // Długosc nazw plikow

char fileIn[fileNameSize];
char fileOut[fileNameSize];
char recoveryFile[fileNameSize];
int symboleTab[256];

struct source // Struktura zawierająca nazwy plikow
{
    char sourceFile[fileNameSize];
    char modelFile[fileNameSize];
    char sortedModelFile[fileNameSize];
    char howManyByteFile[fileNameSize];
    char treeFile[fileNameSize];
    char fullCodingTableFile[fileNameSize];
    char codingTableFile[fileNameSize];
    char fileOut[fileNameSize];
    int byteNum;
    int symbolNum;
    int symbolNumAdded;
} dokumentacja;

struct symbolDane
{
    int symbol;
    int ilosc;
} modelShannon[256], modelSortShannon[256];

struct galaz
{
    int ojciec;
    int potomek1;
    int potomek2;
} drzewo[256], drzewoKodowania[256];

struct slowoDlaSymbolu
{
    int symbol;
    unsigned char slowo[4];
    int liczbaBitow;
} tablicaKoduFull[512], tablicaKodu[256];

void changeExt(char *name, char *extension, char* new);
void bazaNazw(char *nazwa);
void rewriteName(char *nazwa, char *nowaNazwa);
void modelNieSort();
void modelSort();
void makeTree();
void zapiszTablicaKodu(int liczbaSymboli, struct slowoDlaSymbolu tablicaKodu[], char *nazwaPliku);
void zrobTablicaKodu();
void kompresjaZapisDK();
void bazaNazwDeKomp(char *nazwa);
void dekompresjaZapisDK();


int main(int argc, char *argv[])
{
    char *fileName;
    char *option;

    if(argc == 3){
        option = argv[1];
        fileName = argv[2];
        printf("wybrana opcja: %s\n", option);
    }
	else
    {
        printf("Prosze podac tylko dwa argumenty (Lab3 dokuj/dekoduj nazwa_pliku\n");
        exit(EXIT_FAILURE);
    }

    if(strcmp(option, "koduj") == 0){
        bazaNazw(fileName);
        modelNieSort();
        modelSort();
        makeTree();
        zrobTablicaKodu();
        kompresjaZapisDK(); 
    }else if(strcmp(option, "dekoduj") == 0){
        bazaNazwDeKomp(fileName);
        dekompresjaZapisDK(); 
    }else{
        printf("Prosze wybrac jedna z opcji koduj/dekoduj jako pierwszy argument programu\n");
    }
	return 0;
}



// Zastepuje znaki po kropce nowym rozszerzeniem
void changeExt(char *name, char *extension, char* new) 
{
    char newName[24];
    int flaga = 0;
    int i = 0;
    while(name[i] != '.' && name[i] != '\0' && i < 29){
        newName[i] = name[i];
        i++;
    }
    newName[i] = '.';
    i++;
    int j = 0;
    while(extension[j] != '\0' && i < 30){
        newName[i] = extension[j];
        i++;
        j++;
    }
    newName[i] = '\0';
    
    char *p1 = newName;
    char *p2 = new;

    while (*p1) {
        *p2 = *p1;
        p1++;
        p2++;
    }
    *p2 = '\0';

}

//Przepisuje łancuch znaków do innego łańcucha znaków   
void rewriteName(char *nazwa, char *nowaNazwa)
{
    char *znakNazwy;
    int i;

    for (i = 0; i < fileNameSize; i++){
       nowaNazwa[i] = 0;
    }
    i = 0;
    znakNazwy = nazwa;
    nowaNazwa[i] = *znakNazwy;
    while (nazwa[i] != '\0') // While po całej nazwie
    {
        i++;
        znakNazwy++;
        nowaNazwa[i] = *znakNazwy;
    }
}

// Tworzenie nazw plikow
void bazaNazw(char *nazwa)
{
	char rozModel[] = "model";
    char rozModelSort[] = "modelSort";
    char rozileBajtow[] = "ileBajtow";
	char rozDrzewo[] = "drzewo";
	char rozTabelaKoduFull[] = "tabelaKoduFull";
	char rozTabelaKodu[] = "tabelaKodu";
	char rozPlikOut[] = "Huffman";
	dokumentacja.byteNum=0;
    dokumentacja.symbolNum=0;

    rewriteName(nazwa, fileIn);
    printf("================================================= \n");
    printf("!!!========== Wybrany plik: %s ==========!!! \n", fileIn);
    printf("================================================= \n");

    printf("========== Lista Utworzonych plikow ==========\n");

    changeExt(nazwa,rozModel, dokumentacja.modelFile);
    printf("- %s \n", dokumentacja.modelFile);

    changeExt(nazwa,rozModelSort, dokumentacja.sortedModelFile);
    printf("- %s \n", dokumentacja.sortedModelFile);

    changeExt(nazwa,rozileBajtow, dokumentacja.howManyByteFile);
    printf("- %s \n", dokumentacja.howManyByteFile);

    changeExt(nazwa,rozDrzewo, dokumentacja.treeFile);
    printf("- %s \n", dokumentacja.treeFile);

    changeExt(nazwa,rozTabelaKoduFull, dokumentacja.fullCodingTableFile);
    printf("- %s \n", dokumentacja.fullCodingTableFile);

    changeExt(nazwa,rozTabelaKodu, dokumentacja.codingTableFile);
    printf("- %s \n", dokumentacja.codingTableFile);

    changeExt(nazwa,rozPlikOut, fileOut);     
    printf("- %s \n", fileOut);

}

// Zliczanie wystapien poszczegolnych znakow ASCII bez sortowania
void modelNieSort(void)
{
   

	int n ,k ,i ;
    int indeks = 0;
    int ileFakt = 0;
    int licznikBajtow = 0;
    int licznikSymboliZrodla = 0;
    unsigned char buforIn[BUFSIZE];
 
    for (k = 0; k < 256; k++)
    {
     modelShannon[k].symbol = k;
     modelShannon[k].ilosc = 0;
    }
   
    FILE *wskaznikPlikuIn=NULL;
	wskaznikPlikuIn = fopen(fileIn,"rb"); 

    if (wskaznikPlikuIn == NULL)
	{
		printf("Nie mozna otworzyc pliku: %s  \n", fileIn);
		exit(EXIT_FAILURE);
	}
		

	while(ileFakt=fread(buforIn,sizeof(unsigned char),BUFSIZE,wskaznikPlikuIn)) 
    {
 	    for(i = 0; i < ileFakt; i++)
	    {
            indeks = buforIn[i];
            modelShannon[indeks].ilosc++; 
        }
        licznikBajtow+=ileFakt;
    }   
    
    fclose(wskaznikPlikuIn);  

    FILE *wsk = NULL;
	wsk=fopen(dokumentacja.howManyByteFile,"wb"); 

    if (wsk == NULL)
	{
		printf( "Czytanie pliku %s nie powiodo sie. \n", fileIn);
		exit(EXIT_FAILURE);
	}
    
    fprintf(wsk, "%d   ", licznikBajtow); // Zapisanie do pliku ile bajtwow 
    fclose(wsk);    
    
    for (i = 0; i < 256; i++){
        if(modelShannon[i].ilosc != 0){

            modelShannon[licznikSymboliZrodla].symbol=modelShannon[i].symbol;
            modelShannon[licznikSymboliZrodla].ilosc  =modelShannon[i].ilosc;
            licznikSymboliZrodla++;
        }
       }
 
    FILE *wskaznikModel = NULL;
	wskaznikModel = fopen(dokumentacja.modelFile,"wb"); 
	    if (wskaznikModel == NULL)
	{
		printf("Nie mozna utworzyc pliku: %s \n", dokumentacja.modelFile);
		exit(EXIT_FAILURE); 
	}

    for (i = 0; i < licznikSymboliZrodla; i++)
        {
	
			fprintf(wskaznikModel, "%d  %d  \n", modelShannon[i].symbol, modelShannon[i].ilosc);   
			
        }
    
    
    dokumentacja.symbolNum = licznikSymboliZrodla;
    dokumentacja.byteNum = licznikBajtow;
    
    printf("Model Shannona nieposortowany zapisano do pliku  %s \n", dokumentacja.modelFile);
	fclose(wskaznikModel); 

}



int porownajLiczebnosci(const void *operand1,const void *operand2) 
{
    const struct symbolDane *pointer1 = (const struct symbolDane*) operand1;
    const struct symbolDane *pointer2 = (const struct symbolDane*) operand2;
    if((pointer1->ilosc) == (pointer2->ilosc)) return 0;
    else if((pointer1->ilosc) < (pointer2->ilosc))return 1;
    else return -1;
}


void modelSort()
{  

	
	struct symbolDane modelRobol[256];
	int liczbaSymboli;
	int i;

    liczbaSymboli = dokumentacja.symbolNum;
    printf("Liczba symboli  %d \n", liczbaSymboli);
    for(i = 0; i < liczbaSymboli; i++)
        {
            modelRobol[i].symbol = modelShannon[i].symbol;
            modelRobol[i].ilosc = modelShannon[i].ilosc;
        }
      
	qsort(modelRobol,liczbaSymboli,sizeof(struct symbolDane), porownajLiczebnosci); // SOrtowanie
	
    FILE *wskaznikPliku = NULL;
	wskaznikPliku=fopen(dokumentacja.sortedModelFile,"wb"); 
    if (wskaznikPliku == NULL)
	{
		printf("Nie mozna utworzyc pliku: %s \n", dokumentacja.sortedModelFile);
		exit(EXIT_FAILURE);
	}

    printf("========= Posortowany model =========\n");
    for( i=0; i<liczbaSymboli; ++i)
        {
            modelSortShannon[i].symbol= modelRobol[i].symbol;
            modelSortShannon[i].ilosc=modelRobol[i].ilosc;
            fprintf(wskaznikPliku, "  %d  %d\n", modelSortShannon[i].symbol, modelSortShannon[i].ilosc); 
            printf("%d indeks tablicy %d liczebnosc  %d\n", i, modelRobol[i].symbol, modelRobol[i].ilosc);
        }
    
    pclose(wskaznikPliku); 
    printf("Posortowany model zapisano do pliku%s \n", dokumentacja.sortedModelFile);
 
}    

// Z posortowanego tablicy Znakow ASCII po ich ilosci tworzy drzewo
void makeTree()
{
int liczbaSymboli = dokumentacja.symbolNum;
int licznikSymboli = dokumentacja.symbolNum;
int licznikSymboliDodanych = 0;
int n,k;
struct symbolDane treeModel[256];
    for(k = 0; k < liczbaSymboli; k++)
    { 
        treeModel[k].symbol   = modelSortShannon[k].symbol;
        treeModel[k].ilosc = modelSortShannon[k].ilosc;
    }
    for(k = 0; k < liczbaSymboli - 1; k++)
    {
        drzewo[k].ojciec = 256+k;
        drzewo[k].potomek1 =  treeModel[liczbaSymboli-1-k].symbol;
        drzewo[k].potomek2 =  treeModel[liczbaSymboli-2-k].symbol;
        treeModel[liczbaSymboli-2-k].symbol = 256 + k;
        treeModel[liczbaSymboli-2-k].ilosc = treeModel[liczbaSymboli-1-k].ilosc + treeModel[liczbaSymboli-2-k].ilosc;
        licznikSymboli--;
        int i = 0;
        for(; i<licznikSymboli; ++i)
        {
        	int j = 0;
            for(; j < licznikSymboli-i-1; ++j)
            {
                if (treeModel[j].ilosc < treeModel[j + 1].ilosc)
                {
                    struct symbolDane temp = treeModel[j];
                    treeModel[j] = treeModel[j + 1];
                    treeModel[j + 1] = temp;
                }
            }
        }
        licznikSymboliDodanych++;
     }
    FILE *filePtr = NULL;
	filePtr = fopen(dokumentacja.treeFile,"wb");

    if (filePtr == NULL)
	    {
		    printf("Nie mozna utworzyc pliku: \n", dokumentacja.treeFile);
		    exit(EXIT_FAILURE);
	    };

    printf("========= Drzewo Huffmana =========\n");
    for(k = 0; k < licznikSymboliDodanych; k++)
    {
           fprintf(filePtr, "%d %d %d\n ", drzewo[k].ojciec, drzewo[k].potomek1, drzewo[k].potomek2 );
           printf("%d %d %d\n ", drzewo[k].ojciec, drzewo[k].potomek1, drzewo[k].potomek2 );
    };
    fclose(filePtr);

    dokumentacja.symbolNumAdded=licznikSymboliDodanych;
    
    FILE *wskaznikPlikuIle=NULL;
	wskaznikPlikuIle=fopen(dokumentacja.howManyByteFile,"ab"); 
 	        
    if (filePtr == NULL)
	    {
		printf("Nie mozna utworzyc pliku: \n", dokumentacja.howManyByteFile);
		exit(EXIT_FAILURE);
	    };
	
	fprintf(wskaznikPlikuIle, "%d \n ", licznikSymboliDodanych);    
	
    fclose(wskaznikPlikuIle); 


}

void zapiszTablicaKodu(int liczbaSymboli, struct slowoDlaSymbolu tablicaKodu[], char *nazwaPliku)
{
	int k, i;
	unsigned char Four[4];

	FILE *filePtr = NULL;
	filePtr = fopen(nazwaPliku,"wb");

    if (filePtr == NULL)
	{
		printf("Nie mozna utworzyc pliku: %s \n", nazwaPliku);
		exit(EXIT_FAILURE);
	}

    printf("Tablica kodu w zapisie bajtowym do pliku %s \n", nazwaPliku);
    for(k = 0; k < liczbaSymboli; k++)
        {
        for(i = 0; i < 4; i++)
          Four[i] = tablicaKodu[k].slowo[i];
        printf( " %d %d  %d  %d %d %d \n", tablicaKodu[k].symbol, Four[0],Four[1],Four[2],Four[3],tablicaKodu[k].liczbaBitow);
        fprintf(filePtr, " %d %d  %d  %d %d %d \n", tablicaKodu[k].symbol, Four[0],Four[1],Four[2],Four[3],tablicaKodu[k].liczbaBitow);
        }
        fclose(filePtr);
}


// Tworzy tablicę kodu na podstawie danych z wcześniej zbudowanego drzewa Huffmana
void zrobTablicaKodu()
{
	int liczbaSymboli =  dokumentacja.symbolNum;
	int symbol;
    int n, k, i;
    int fatherId, symbolOjca;
    int licznikDrzewa;
    int counter;
    int dlugoscCiagu=0;
    int pozycja, ktoryBajt, ktoryBit;
    unsigned char four[4];
    unsigned char bajt, jedynka = 1;


    for(k = 0; k < 512; k++)
    {
        for(i = 0; i < 4; i++)
            tablicaKoduFull[k].slowo[i] = 0;
            tablicaKoduFull[k].symbol = 0;
            tablicaKoduFull[k].liczbaBitow = 0;
    }

    licznikDrzewa = liczbaSymboli - 2;
    counter = 0;
    tablicaKoduFull[counter].symbol = drzewo[licznikDrzewa].ojciec;

    while(licznikDrzewa + 1)
     {
        symbolOjca = drzewo[licznikDrzewa].ojciec;
        tablicaKoduFull[counter+1].symbol=drzewo[licznikDrzewa].potomek1;
        tablicaKoduFull[counter+2].symbol=drzewo[licznikDrzewa].potomek2;

        fatherId = -1;
        for (i = 0; i < counter+1; i++)
            {
                if ((tablicaKoduFull[i].symbol) == (symbolOjca))
                  {
                    fatherId = i;
                    break;
                  }
            }
        if(fatherId == -1)
        {
            printf("Blad tworzenie tablicy kodu\n");
            exit(EXIT_FAILURE);
        }

       dlugoscCiagu = tablicaKoduFull[fatherId].liczbaBitow;

       for(i = 0; i < 4; i++)
           {
                tablicaKoduFull[counter + 1].slowo[i] = tablicaKoduFull[fatherId].slowo[i];
                tablicaKoduFull[counter + 2].slowo[i] = tablicaKoduFull[fatherId].slowo[i];
           }

        pozycja = dlugoscCiagu;
        ktoryBajt = pozycja / 8;
        ktoryBit = pozycja % 8;
        jedynka = 1;
        jedynka = jedynka << 7 - ktoryBit;
        
        bajt = tablicaKoduFull[fatherId].slowo[ktoryBajt];
        bajt = bajt|jedynka;

        tablicaKoduFull[counter+1].slowo[ktoryBajt] = bajt;
        tablicaKoduFull[counter+1].liczbaBitow = dlugoscCiagu+1;
        tablicaKoduFull[counter+2].liczbaBitow = dlugoscCiagu+1;
        counter += 2;
        licznikDrzewa--;
    }

    zapiszTablicaKodu (counter+1, tablicaKoduFull, dokumentacja.fullCodingTableFile);



   //Elimonowanie dodatkowych symboli
    counter = 0;
    for(k = 0; k < 256; k++)
      {
        for(i = 0; i < 4; i++)
          tablicaKodu[k].slowo[i]=0;
        tablicaKodu[k].symbol=0;
        tablicaKodu[k].liczbaBitow=0;
      }

    for (k = 0; k < 2*liczbaSymboli-1; k++)
     {
         symbol=tablicaKoduFull[k].symbol;
         if (symbol < 256)
         {
             tablicaKodu[counter].symbol = symbol;
             tablicaKodu[counter].liczbaBitow = tablicaKoduFull[k].liczbaBitow;
             for (i = 0; i < 4; i++)
                tablicaKodu[counter].slowo[i] = tablicaKoduFull[k].slowo[i];
             counter++;
         }
     }

    zapiszTablicaKodu (liczbaSymboli, tablicaKodu,  dokumentacja.codingTableFile);

}

void kompresjaZapisDK(){
	
    unsigned int liczbaBajtowPlikuIn, licznikBajtowIn;
    int liczbaGaleziDrzewa;
	unsigned int licznikBajtowKodu, licznikBitowKodu;
    
	
    unsigned char buforWejscia[BUFSIZE];
    unsigned char buforWyjscia[BUFSIZE];
    
    unsigned char symbol, dopisek, bajtOut;
    int kursorSlowka, kursorOut;
    int liczbaBitowSlowaKodu, liczbaWolneBity, liczbaPozostaleBitySlowka, numerSlowka;

    int n,i,m,k;
    unsigned char maska1, maska2, maska, slowko[4];
	unsigned char four[4];
    
    liczbaGaleziDrzewa = dokumentacja.symbolNumAdded; 
	liczbaBajtowPlikuIn = dokumentacja.byteNum;
	licznikBajtowIn = 0;
	licznikBajtowKodu = 0;
	licznikBitowKodu = 0;
    
    FILE *wskaznikPlikuOut = NULL;
	wskaznikPlikuOut = fopen(fileOut,"wb+"); 
	   	    
    if (wskaznikPlikuOut == NULL)
	{
		printf("Nie mozna utworzyc pliku: %s  \n", fileOut);
		exit(EXIT_FAILURE);
	}

	fwrite(&licznikBajtowKodu, sizeof(unsigned int), 1, wskaznikPlikuOut);
	fwrite(&licznikBitowKodu, sizeof(unsigned int), 1, wskaznikPlikuOut);
	fwrite(&liczbaBajtowPlikuIn, sizeof(int), 1, wskaznikPlikuOut);
	printf("Zapisano do pliku wynikowego liczbe bajtow przed kompresja %d \n", liczbaBajtowPlikuIn);
	fwrite(&liczbaGaleziDrzewa,sizeof(int),1,wskaznikPlikuOut);
	printf("Zapisano do pliku wynikowego liczbe galezi drzewa kodowania %d \n", liczbaGaleziDrzewa);
    fwrite(drzewo,sizeof(struct galaz), liczbaGaleziDrzewa, wskaznikPlikuOut);
    printf("Zapisano binarnie drzewo kodowania do pliku wynikowego \n"); 
 
   
    printf("Kodowanie symboli i zapis binarnego strumienia kodu do pliku wynikowego\n"); 
    FILE *wskaznikPlikuIn=NULL;
	wskaznikPlikuIn=fopen(fileIn, "rb"); 
    if (wskaznikPlikuIn == NULL)
	{
		printf("Nie mozna otworzyc pliku: %s  \n", fileIn);
		exit(EXIT_FAILURE);
	}
   
    numerSlowka=0;
    kursorOut=0;
    bajtOut=0;

    while(n = fread(buforWejscia, sizeof(unsigned char), BUFSIZE, wskaznikPlikuIn)) 
    {
    for(i = 0; i < n; i++)
      {
        symbol = buforWejscia[i];
       
        for (m = 0; m < dokumentacja.byteNum; m++)
        {
          if (symbol == tablicaKodu[m].symbol){
            for (k = 0; k < 4; k++)
                slowko[k] = tablicaKodu[m].slowo[k];
            liczbaBitowSlowaKodu = tablicaKodu[m].liczbaBitow; 
            licznikBitowKodu = licznikBitowKodu + liczbaBitowSlowaKodu;
            kursorSlowka = 0;
            numerSlowka = 0;
            break;
           }
        }
     
        while (liczbaBitowSlowaKodu > 0)
        {
           liczbaPozostaleBitySlowka = 8 - kursorSlowka;
           if (liczbaPozostaleBitySlowka > liczbaBitowSlowaKodu)
              liczbaPozostaleBitySlowka = liczbaBitowSlowaKodu;
           liczbaWolneBity = 8 - kursorOut;
           if (liczbaPozostaleBitySlowka < liczbaWolneBity)
                liczbaWolneBity = liczbaPozostaleBitySlowka;
           maska1 = 255>>kursorSlowka;
           maska2 = 255<<(8-(kursorSlowka+liczbaWolneBity));
           maska = maska1&maska2;
           dopisek = slowko[numerSlowka]&maska;
           dopisek = dopisek<<kursorSlowka;
           dopisek = dopisek>>kursorOut;
           bajtOut = bajtOut|dopisek;
           kursorOut += liczbaWolneBity;   
           liczbaBitowSlowaKodu -= liczbaWolneBity;  
           kursorSlowka += liczbaWolneBity;
           liczbaPozostaleBitySlowka -= liczbaWolneBity;  
           if (liczbaPozostaleBitySlowka == 0){
                numerSlowka++;  
                kursorSlowka = 0;                             
                if (liczbaBitowSlowaKodu >= 8)
                liczbaPozostaleBitySlowka = 8;
                else
                liczbaPozostaleBitySlowka = liczbaBitowSlowaKodu;
           }                                        
         
           if (kursorOut == 8){
                fwrite(&bajtOut, sizeof(unsigned char), 1, wskaznikPlikuOut);
                licznikBajtowKodu++;
                kursorOut = 0;
                bajtOut = 0;
           }
         }
         licznikBajtowIn += 1;
       }
    }
     
    licznikBajtowKodu += 1;
    printf("Ostatni (niepelny) bajt strumienia kompresji\n");
	printf("Numer bajtu %d, kod hexdec bajtu %x \n", licznikBajtowKodu, bajtOut);
    fwrite(&bajtOut,sizeof(unsigned char),1,wskaznikPlikuOut);                     
    printf("Liczba obsluzonych bajtow pliku wejsciowego: %d\n", licznikBajtowIn);
    printf("Liczba bajtow kodu w pliku skompresowanym: %d \n", licznikBajtowKodu);
    printf("Liczba bitow kodu w pliku skompresowanym: %d \n", licznikBitowKodu);
    printf("Wskaznik upakowania: %5.1f  procent\n", 100*(float)(licznikBajtowKodu)/(float)licznikBajtowIn);
    
	fclose(wskaznikPlikuIn); 
	
	printf("Zapis binarny liczby bajtow i liczby bitow do pliku wynikowego\n"); 
 	printf( "Liczba bajtow %d, liczba bitow %d \n", licznikBajtowKodu, licznikBitowKodu); 
  	fseek(wskaznikPlikuOut,0*sizeof(unsigned int),0);
	fwrite(&licznikBajtowKodu,sizeof(unsigned int),1,wskaznikPlikuOut);
	printf("Zapisano do pliku wynikowego liczbe bajtow kodu kompresji %d \n", licznikBajtowKodu);
	fwrite(&licznikBitowKodu,sizeof(unsigned int),1,wskaznikPlikuOut);
	printf("Zapisano do pliku wynikowego liczbe bitow kodu kompresji %d \n", licznikBitowKodu);
	
	fclose(wskaznikPlikuOut); 

}

// Funkcje do dekompresji =========================================================

void bazaNazwDeKomp(char *nazwa)
{
	char rozPlikuRecovery[] = "recovery";
    
   	rewriteName(nazwa, fileIn);
    printf("bazaNazw:  %s \n", fileIn);
    
    changeExt(nazwa,rozPlikuRecovery, recoveryFile);     
    printf("bazaNazw:  %s \n", recoveryFile);
 	
}
void dekompresjaZapisDK()
{

 unsigned int liczbaBajtowOryginal, liczbaBajtowKodu, liczbaBitowKodu;
 unsigned int licznikBajtowZdekodowanych, licznikBajtowWczytanych, licznikBitowDekodowanych;
 int liczbaGaleziDrzewa, indeksDrzewa;
 int n; 
 int odczytD[3];
 int pater, syn1, syn0;

 int i,m,k;
 unsigned char  bajtIn, bajtOut, jakiBit;
 unsigned char maska = 128;

    printf("Odczytana nazwa pliku skompresowanego: %s  \n", fileIn);
    
    FILE *fileptr = NULL;
	fileptr = fopen(fileIn,"rb"); 
	   	    
    if (fileptr == NULL)
	{
		printf("Nie mozna otworzyc pliku: %s  \n", fileIn);
		exit(EXIT_FAILURE);
	}

	fread(&liczbaBajtowKodu,sizeof(unsigned int),1, fileptr);
	printf("Plik skompresowany zawiera %d  bajtow kodu\n",liczbaBajtowKodu);
	fread(&liczbaBitowKodu,sizeof(unsigned int),1, fileptr);
	printf("Plik skompresowany zawiera %d  bitow kodu\n",liczbaBitowKodu);
	fread(&liczbaBajtowOryginal,sizeof(unsigned int),1, fileptr);
	printf("Plik oryginalny zawiera %d  bajtow\n",liczbaBajtowOryginal); 
	fread(&liczbaGaleziDrzewa,sizeof(int),1, fileptr);
	printf("Plik skompresowany zawiera tabele drzewa o %d rozgalezien\n",liczbaGaleziDrzewa );
	
    printf("Odczyt tabeli drzewa\n");
	for (n = 0;n < liczbaGaleziDrzewa; n++)
	  { 
	    fread(&odczytD,sizeof(int), 3, fileptr);	    
        drzewoKodowania[n].ojciec = odczytD[0];
        drzewoKodowania[n].potomek1 = odczytD[1];
        drzewoKodowania[n].potomek2 = odczytD[2];
        printf("%d %d %d %d\n", n, odczytD[0], odczytD[1], odczytD[2]);
       }

	
    printf( "Czytanie pliku skompresowanego %s po jednym bajcie. \n", fileIn); 
    printf( "Sukcesywnie zapis zdekodowanych symboli do pliku wynikowego %s. \n", recoveryFile); 
    FILE *recovfileptr = NULL;
	recovfileptr = fopen(recoveryFile,"wb"); 
        
    licznikBajtowWczytanych = 0;
    licznikBitowDekodowanych = 0;
    licznikBajtowZdekodowanych = 0;
    indeksDrzewa = liczbaGaleziDrzewa-1;
    pater = drzewoKodowania[indeksDrzewa].ojciec;
    syn1 = drzewoKodowania[indeksDrzewa].potomek1;
    syn0 = drzewoKodowania[indeksDrzewa].potomek2;
    
    while(licznikBajtowWczytanych < liczbaBajtowKodu) 
     {
                
        n = fread(&bajtIn, sizeof(unsigned char), 1, fileptr);             
        if(n == 1)
      {
        licznikBajtowWczytanych++;
		for(k = 0; k < 8; k++)
        {
            jakiBit = bajtIn&maska;
            bajtIn = bajtIn<<1;
            licznikBitowDekodowanych++;
            if(jakiBit)
              pater = syn1;
            else
              pater = syn0;
            
            if(pater < 256)
            {
               bajtOut = pater;
               
               fwrite(&bajtOut,sizeof(unsigned char),1,recovfileptr);
               licznikBajtowZdekodowanych++;
               indeksDrzewa = liczbaGaleziDrzewa-1;
               pater = drzewoKodowania[indeksDrzewa].ojciec;
               syn1 = drzewoKodowania[indeksDrzewa].potomek1;
               syn0 = drzewoKodowania[indeksDrzewa].potomek2; 
               if(licznikBajtowZdekodowanych == liczbaBajtowOryginal)
               break;         
            }
            else
            {
            m = liczbaGaleziDrzewa-1;
            while(m >= 0)
            {
               if(drzewoKodowania[m].ojciec == pater)
               {
                 indeksDrzewa=m;
                 m =- 1;                                   
               } 
               m = m - 1;
            }        
           
            syn1 = drzewoKodowania[indeksDrzewa].potomek1;
            syn0 = drzewoKodowania[indeksDrzewa].potomek2;
            }
          }
        }
    } 

    printf("Tyle ma byc bajtow po zdekodowaniu:  %d a tyle zdekodowano: %d\n", liczbaBajtowOryginal, licznikBajtowZdekodowanych); 
	
	fclose(fileptr); 
    fclose(recovfileptr); 

}