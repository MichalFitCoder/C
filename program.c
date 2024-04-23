#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<windows.h>


int main()
{
   srand(time(0));
   int random = rand()%10 +1;
   int guess = 0;
   printf("Zgadnij liczbe od 1 do 100\n");
   printf("Take a guess\n");

   while(random!=guess){
      scanf("%d",&guess);
      if(guess>random) printf("Too much\n");
      if(guess<random) printf("Too Low\n");
   }
   printf("*******************\n");
   printf("Gratulacje zgadles\n");
   printf("*******************\n");

   return 0;
}