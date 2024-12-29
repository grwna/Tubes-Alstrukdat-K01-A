#include <stdio.h>
#include "importanceStatus.h"

// Global variable for importance matrix
StatusImportance AllStatusImportance;

void initStatusImportance(StatusImportance *S, int userCount) {
    createMatrix(userCount, userCount, &S->matrix);
    for (int i = 0; i < userCount; i++) {
        for (int j = 0; j < userCount; j++) {
            ELMT(S->matrix, i, j) = 0; 
        }
    }
}

void updateSizeStatusImportance(StatusImportance *S, int userCount) {
    Matrix newMatrix;
    createMatrix(userCount, userCount, &newMatrix);
    for (int i = 0; i < userCount; i++) {
        for (int j = 0; j < userCount; j++) {
            if (i < S->matrix.rowEff && j < S->matrix.colEff) {
                ELMT(newMatrix, i, j) = ELMT(S->matrix, i, j);
            } else {
                ELMT(newMatrix, i, j) = 0;
            }
        }
    }
    S->matrix = newMatrix;
}

void updateImportance(StatusImportance *S, int fromUserId, int toUserId, int ccUserId) {
    if (toUserId != -1) { 
        ELMT(S->matrix, fromUserId-1, toUserId-1)++;
    }
    if (ccUserId != -1) { 
        ELMT(S->matrix, fromUserId-1, ccUserId-1)++;
    }
}

boolean isEmailImportanceReached(StatusImportance status, int fromUserId, int toUserId) {
    return ELMT(status.matrix, fromUserId-1, toUserId-1) >= importantLimit;
}

void printGridLine(int size) {
    // Menghitung panjang garis berdasarkan ukuran matriks
    int lineLength = 6 + (size * 5); 
    printf("[");
    for (int i = 0; i < lineLength - 2; i++) { 
        printf("-");
    }
    printf("]\n");
}

void displayStatus(StatusImportance status) {
    if (EOP) {
        int i, j;
        int size = status.matrix.rowEff;

        // Header atas tabel
        printGridLine(size);
        printf("| ID |");
        for (i = 0; i < size; i++) {
            printf(" %02d |", i + 1); 
        }
        printf("\n");
        printGridLine(size);

        // Baris matriks
        for (i = 0; i < size; i++) {
            printf("| %02d |", i + 1); 
            for (j = 0; j < size; j++) {
                printf(" %02d |", ELMT(status.matrix, i, j)); 
            }
            printf("\n");
        }
        printGridLine(size);
        printf("\n");
    } else {
        while (!EOP) {
            ADVWORD();
        }
        printf("Setelah perintah STATUS_KEPENTINGAN, jangan ada input lain ya, langsung kasih ';' aja :).\n");
        printf("\n");
    }  
}
