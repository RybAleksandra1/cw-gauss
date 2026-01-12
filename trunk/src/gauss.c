#include "gauss.h"
#include <math.h>  // Może się przydać do abs() w przyszłości, warto dodać

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){
    //Algorytm wyboru elementu diagonalnego - Ola
    int n = mat->r;
    int k, i, j;
    double factor;

    // Sprawdzamy czy macierze w ogole istnieja i czy maja dobre wymiary 
    if (!mat || !b || mat->r != mat->c || mat->r != b->r) {
        return 1; // Błąd błędnych danych
    }

    // TRYWIALNA ELIMINACJA GAUSSA 

    // petla po kolumnach (krokach eliminacji)
    for(k = 0; k < n - 1; k++) {
        
        // selekcja elementu diagonalnego
        int max_row = k;
        double max_val = fabs(mat->data[k][k]);
        
        // Szukamy wiersza z największą wartością bezwzględną w kolumnie k
        for (i = k + 1; i < n; i++) {
            if (fabs(mat->data[i][k]) > max_val) {
                max_val = fabs(mat->data[i][k]);
                max_row = i;
            }
        }

        // Sprawdzenie osobliwości (jeśli największy element to 0, kolumna jest zerowa)
        if (max_val < 1e-12) { // tolerancja
            return 1;
        }

        // Zamiana wierszy, jeśli znaleziono lepszy pivot
        if (max_row != k) {
            // Zamiana wierszy w macierzy A
            double *temp_row = mat->data[k];
            mat->data[k] = mat->data[max_row];
            mat->data[max_row] = temp_row;

            // Zamiana wierszy w wektorze b
            double *temp_b = b->data[k];
            b->data[k] = b->data[max_row];
            b->data[max_row] = temp_b;
        }

        // petla po wierszach 
	for(i = k + 1; i < n; i++) {
            
            // Obliczenie wspolczynnika, przez ktory mnozymy wiersz k
            factor = mat->data[i][k] / mat->data[k][k];

            // Odejmowanie wiersza k od wiersza i w macierzy A
            // Zaczynamy od j=k, bo elementy wczesniej sa juz wyzerowane
            for(j = k; j < n; j++) {
                mat->data[i][j] -= factor * mat->data[k][j];
            }

            // To samo odejmowanie dla wektora wynikow b
            b->data[i][0] -= factor * b->data[k][0];
        }
    }

    // Ostatnie sprawdzenie elementu na samym dole przekątnej
    if (fabs(mat->data[n-1][n-1]) < 1e-12) {
        return 1;
    }

    return 0; // Sukces
}
