#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define WIDTH 80
#define HEIGHT 23

int main(void) {
    int x, y;
    char rain[HEIGHT][WIDTH];

    srand(time(NULL)); // Inicjalizacja generatora liczb losowych

    // Wypełnienie tablicy znakami " " (odstęp)
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            rain[y][x] = ' ';
        }
    }

    while (1) {
        // Generowanie nowych kropek deszczu
        for (x = 0; x < WIDTH; x++) {
            if (rand() % 100 < 5) { // 5% szans na wygenerowanie nowej kropki
                rain[0][x] = '.';
            }
        }

        // Przesuwanie kropek deszczu w dół
        for (y = HEIGHT - 1; y > 0; y--) {
            for (x = 0; x < WIDTH; x++) {
                rain[y][x] = rain[y-1][x];
            }
        }

        // Wypisanie tablicy na ekranie
        for (y = 0; y < HEIGHT; y++) {
            for (x = 0; x < WIDTH; x++) {
                printf("%c", rain[y][x]);
            }
            printf("\n");
        }

        // Uspanie programu na 100ms, aby dać odczuć ruch deszczu
        #include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 80
#define HEIGHT 23

int main(void){
    int x, y;
    char rain[HEIGHT][WIDTH];

    srand(time(NULL)); // Inicjalizacja generatora liczb losowych

    // Wypełnienie tablicy znakami " " (odstęp)
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            rain[y][x] = ' ';
        }
    }

    while (1) {
        // Generowanie nowych kropek deszczu
        for (x = 0; x < WIDTH; x++) {
            if (rand() % 100 < 5) { // 5% szans na wygenerowanie nowej kropki
                rain[0][x] = '.';
            }
        }

        // Przesuwanie kropek deszczu w dół
        for (y = HEIGHT - 1; y > 0; y--) {
            for (x = 0; x < WIDTH; x++) {
                rain[y][x] = rain[y-1][x];
            }
        }

        // Wypisanie tablicy na ekranie
        for (y = 0; y < HEIGHT; y++) {
            for (x = 0; x < WIDTH; x++) {
                printf("%c", rain[y][x]);
            }
            printf("\n");
        }

        // Uspanie programu na 100ms, aby dać odczuć ruch deszczu
        Sleep(100000);
    }

    return 0;
}