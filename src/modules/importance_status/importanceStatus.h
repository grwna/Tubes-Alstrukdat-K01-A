#ifndef STATUS_IMPORTANCE_H
#define STATUS_IMPORTANCE_H

#include "../matrix/matrix.h" 
#include "../mesin_kata/mesinkata.h"
#include "../inisiasi/inisiasi.h"

typedef struct {
    Matrix matrix;
} StatusImportance;

extern StatusImportance AllStatusImportance;

/* Selektor */
#define IMPORTANCE_MATRIX(S, i, j) (S).matrix.contents[(i)][(j)]

// Fungsi untuk menginisiasi matriks kepentingan
void initStatusImportance(StatusImportance *S, int userCount);
/* Membuat matriks kepentingan dengan ukuran userCount x userCount dan menginisialisasi semua elemen dengan 0. */

// Fungsi untuk mengupdate ukuran matriks kepentingan jika terdapat penambahan user
void updateSizeStatusImportance(StatusImportance *S, int userCount);
/* Menamabahkan ukuran matriks status kepentingan sesuai jumlah user terbaru dan menginisiasi nilai matriks 0 */

// Fungsi untuk mengupdate matriks kepentingan berdasarkan email yang dikirim
void updateImportance(StatusImportance *S, int fromUserId, int toUserId, int ccUserId);
/* Updates the importance matrix based on an email sent:
   - Increment S.matrix[fromUserId][toUserId] by 1 if toUserId is valid.
   - Increment S.matrix[fromUserId][ccUserId] by 1 if ccUserId is valid. */

/* Mengecek apakah tingkat kepentingan antar pengguna telah mencapai batas tertentu */
boolean isEmailImportanceReached(StatusImportance S, int fromUserId, int toUserId);
/* Mengembalikan true jika tingkat kepentingan antara fromUserId dan toUserId mencapai atau melebihi threshold. */

// Fungsi untuk mencetak garis horizontal sesuai ukuran matriks
void printGridLine(int size);
/* Prints a horizontal line based on the size of the matrix. */

// Fungsi untuk mencetak matriks kepentingan
void displayStatus(StatusImportance S);
/* Prints the importance matrix in a readable format. */

#endif
