#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// ta funkcja robi kopie macierzy
Matrix * cloneMatrix(Matrix * s) {
    int i, j;
    Matrix * d = createMatrix(s->r, s->c);
    if (d != NULL) {
        for(i = 0; i < s->r; i++)
            for(j = 0; j < s->c; j++)
                d->data[i][j] = s->data[i][j];
    }
    return d;
}

// ta funkcja weryfikuje wynik: sprawdza czy Ax - b jest bliskie 0 
void verify(Matrix * A, Matrix * b, Matrix * x) {
    int r, c;
    double sum, diff, max_diff = 0.0;
    
    printf("\n    Weryfikacja (Ax = b)    \n");
    for(r = 0; r < A->r; r++) {
        sum = 0.0;
        for(c = 0; c < A->c; c++)
            sum += A->data[r][c] * x->data[c][0];
        
        diff = fabs(sum - b->data[r][0]);
        if(diff > max_diff) max_diff = diff;
    }

    if(max_diff < 1e-10)
        printf("TEST OK! (Maksymalny blad: %g)\n", max_diff);
    else
        printf("BLAD! Wynik zly. (Blad: %g)\n", max_diff);
}

int main(int argc, char ** argv) {
    int res;
    Matrix * A = readFromFile(argv[1]);
    Matrix * b = readFromFile(argv[2]);
    Matrix * x;

    if (A == NULL) return -1;
    if (b == NULL) return -2;

    // robie kopie do weryfikacji, bo funkcja eliminate niszczy  macierz A 
    Matrix * Acopy = cloneMatrix(A);
    Matrix * bcopy = cloneMatrix(b);

    printToScreen(A);
    printToScreen(b);

    res = eliminate(A,b);
    
    if (res == 1) {
        printf("Macierz osobliwa - wykryto dobrze.\n");
    } else {
        x = createMatrix(b->r, 1);
        if (x != NULL) {
            res = backsubst(x,A,b);
            printToScreen(x);
            
            // Automatycznie weryfikuje jak dalo sie policzyc
            if (Acopy && bcopy) verify(Acopy, bcopy, x);
            
            freeMatrix(x);
        } else {
            fprintf(stderr,"Blad! Nie mozna utworzyc wektora wynikowego x.\n");
        }
    }

    freeMatrix(A);
    freeMatrix(b);
    if (Acopy) freeMatrix(Acopy);
    if (bcopy) freeMatrix(bcopy);

    return 0;
}