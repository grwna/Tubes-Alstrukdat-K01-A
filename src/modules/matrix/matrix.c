#include <stdio.h>
#include "matrix.h"

void createMatrix(int nRows, int nCols, Matrix *m) {
    ROW_EFF(*m) = nRows;
    COL_EFF(*m) = nCols;
}

boolean isMatrixIdxValid(int i, int j) {
    return (i >= 0 && i < ROW_CAP) && (j >= 0 && j < COL_CAP);
}

IdxType getLastIdxRow(Matrix m) {
    return ROW_EFF(m) - 1;
}

IdxType getLastIdxCol(Matrix m) {
    return COL_EFF(m) - 1;
}

boolean isIdxEff(Matrix m, IdxType i, IdxType j) {
    return (i >= 0 && i < ROW_EFF(m)) && (j >= 0 && j < COL_EFF(m));
}

Num getElmtDiagonal(Matrix m, IdxType i) {
    return ELMT(m, i, i);
}

Num getElmt(Matrix m, IdxType i, IdxType j) {
    return ELMT(m, i, j);
}

void setElmt(Matrix *m, IdxType i, IdxType j, Num x) {
    ELMT(*m, i, j) = x;
}

void copyMatrix(Matrix mIn, Matrix *mOut) {
    ROW_EFF(*mOut) = ROW_EFF(mIn);
    COL_EFF(*mOut) = COL_EFF(mIn);
    int i,j;
    for (i = 0; i <ROW_EFF(mIn); i++) {
        for (j = 0; j < COL_EFF(mIn); j++) {
            ELMT(*mOut, i, j) = ELMT(mIn, i, j);
        }
    }
}

void readMatrix(Matrix *m, int nRow, int nCol) {
    createMatrix(nRow, nCol, m);
    int i,j;
    for (i = 0; i < nRow; i++) {
        for (j = 0; j < nCol; j++) {
            scanf("%d", &ELMT(*m, i, j));
        }
    }
}

void displayMatrix(Matrix m) {
    int i,j;
    for (i = 0; i <ROW_EFF(m); i++) {
        for (j = 0; j < COL_EFF(m); j++) {
            printf("%d", ELMT(m, i, j));
            if (j < ROW_EFF(m) - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }    
}