##include "gauss.h"
#include <stdio.h>
#include <math.h>

/*
 tu robimy funkcje pomocnicza: 
 Wybor elementu diagonalnego (pivot)
 */
void pivot_selection(Matrix *mat, Matrix *b, int k) {
    int max_row = k;
    double max_val = fabs(mat->data[k][k]);

    /* 1. Szukamy wiersza z najwiekszym elementem w kolumnie k */
    for (int i = k + 1; i < mat->r; i++) {
        if (fabs(mat->data[i][k]) > max_val) {
            max_val = fabs(mat->data[i][k]);
            max_row = i;
        }
    }

    /* 2. jesli znaleziono lepszy to zamiana wierszy */
    if (max_row != k) {
        /* zamiana wskaznikow w macierzy A */
        double *tmp_row = mat->data[k];
        mat->data[k] = mat->data[max_row];
        mat->data[max_row] = tmp_row;

        /* zamiana wartosci w wektorze b (tutaj zamieniamy liczby) */
        double tmp_b = b->data[k][0];
        b->data[k][0] = b->data[max_row][0];
        b->data[max_row][0] = tmp_b;
    }
}

/**
 * wynik intepretacja
 * 0 - eliminacja gaussa zakonczona sukcesem
 * 1 - macierz osobliwa czyli wystepuje dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){
    /* Polaczylam zmienne */
    int i, j, k;
    double factor;

    /* Sprawdzenie czy podane dane sa popawne */
    if (!mat || !b || mat->r != mat->c || mat->r != b->r) {
        fprintf(stderr, "Blad: Nieprawidlowe rozmiary macierzy lub brak danych!\n");
        return 1;
    }

    /* Glowna petla eliminacji */
    for(i = 0; i < mat->r - 1; i++){
        
        /* wywolanie funkcji pivota */
        pivot_selection(mat, b, i);

        /* czy element na diagonali nie jest 0 */
        if(fabs(mat->data[i][i]) < 1e-12){
            return 1; // Macierz osobliwa
        }

        /* zwykla eliminacja */
        for(j = i + 1; j < mat->r; j++){
            factor = mat->data[j][i] / mat->data[i][i];
            
            for(k = i; k < mat->c; k++){
                mat->data[j][k] -= factor * mat->data[i][k];
            }
            b->data[j][0] -= factor * b->data[i][0];
        }
    }

    /* spr. ostatniego elementu na diagonalnej */
    if(fabs(mat->data[mat->r - 1][mat->r - 1]) < 1e-12) return 1;

    return 0;
}