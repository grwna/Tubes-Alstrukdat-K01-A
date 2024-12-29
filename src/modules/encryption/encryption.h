#ifndef ENCRYPTION_H
#define ENCRYPTION_H

# include "../utility/string.h"
# include "../inisiasi/inisiasi.h"

# define A 1664525      // Multiplier
# define C 1013904223   // Increment
# define M 4294967296   // Modulus

typedef struct Key{   
    int upper[26];
    int lower[26];
} Key;
;

extern Key plain; // Plaintext "key"

void encrypt(LargeString body);
/* Enkripsi sebuah string menggunakan case-sensitive substitution cipher*/

void decrypt(LargeString body);
/* Dekripsi sebuah string menggunakan key yang telah disimpan*/

void printSuccessMessage(Key K);

/* ========= IO ===============*/
void saveKey_encryption(Key K);
/* Menyimpan key ke dalam file*/

int loadKey_encryption();
/* Mengambil key dari file*/

/* ======= UTILITY =========*/
int rng();
/* Generate random number menggunakan LCG */

Key generateKey();
/* I.S key kosong
   F.S assign alphabet berupa ascii value ke dalam key dengan
       urutan random
   */

int indexOf_encryption(Key K, int val);

#endif // ENCRYPTION_H
