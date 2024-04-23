#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void losuj (float *tab, int n, int m);
float *f1(float *tab, float *tabD, int n, int m);
float *f2(float *tab, float *tabU, int n, int m);
void wyswietl (float *tab, int k);
int main() {
	int n,m,i,j;
	float *k;
	srand(0);
	printf("podaj wymiary tablicy: ");
	scanf("%d x %d", &n, &m);
	float tab2[n][m];
	losuj((float *)tab2, n, m);
	
	float *tabD = (float *)malloc(sizeof(float));
	float *tabU = (float *)malloc(sizeof(float));
	
	printf("\n\ntablica wartosci dodatnich: ");
	f1((float *)tab2, (float *)tabD, n, m);
	printf("\n\ntablica wartosci ujemnych: ");
	f2((float *)tab2, (float *)tabU, n, m);
	//wyswietl((float *)tabD, k);
	//printf("%.2f", *k);
	system("pause");
	return 0;
}

void losuj (float *tab, int n, int m){
	int i, j;
	printf("cala tablica: ");
	for(i=0;i<n;i++){
		for (j=0;j<m;j++){
			*(tab + m*i + j) = (rand()%2000 - 1000)/3.;
			printf("%.2f  ", *(tab + m*i + j));
		}
		
	}
}
float *f1(float *tab, float *tabD, int n, int m){
	int i, k = 0;
	for(i=0;i<n*m;i++){
		if (*(tab + i) >= 0){
			*(tabD + k) = *(tab + i);
			tabD = realloc(tabD, sizeof(float)*(k + 2));
			printf("%.2f ", *(tabD + k));
			k++;		
		}
	}
	return tabD;
}

void wyswietl (float *tab, int k){
	int i;
	for(i=0;i<k;i++){
		printf("%.2f  ", *(tab + i));	
	}
}

float *f2(float *tab, float *tabU, int n, int m){
	int i, k = 0;
	for(i=0;i<n*m;i++){
		if (*(tab + i) <= 0){
			*(tabU + k) = *(tab + i);
			tabU = realloc(tabU, sizeof(float)*(k + 2));
			printf("%f ", *(tabU + k));
			k++;		
		}
	}
	return tabU;
}