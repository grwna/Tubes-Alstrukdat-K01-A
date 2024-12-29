#ifndef STRING_H
#define STRING_H

#include "boolean.h"
#include "../mesin_kata/mesinkata.h"

typedef char String[256];
typedef char LargeString[1001];

#define SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

/*  I.S. s tidak terdefinisi 
    F.S. s kosong terbuat, length 0*/
void createString(char *s);

/*  mengembalikan panjang efektif string.*/
int stringLength(char *s);

/*  mengembalikan true jika string kosong.*/
boolean isEmpty_String(char *s);

/*  mengembalikan true jika string penuh.*/
boolean isFull_String(char *s, size_t size);

/*  mengembalikan true jika kedua string sama.*/
boolean isStringEqual(char *str1, char* str2);

/*  I.S. s bebas
    F.S. s terisi dengan str.
         Jika gagal, error_code 302, s kosong. */
void assignString(char *s, size_t size, char *str);

/*  I.S. s terdefinisi, currentWord terdefinisi
    F.S. s disambungkan dengan str.
         Jika gagal, error_code 302, s kosong. */
void appendString(char *s, size_t size, char *str);

/*  I.S. s terdefinisi, c terdefinisi
    F.S. s disambungkan dengan c.
         Jika gagal, error_code 302, s kosong. */
void appendChar(char *s, size_t size, char c);

/*  I.S. str terdefinisi
    F.S. print char *str TANPA newline.*/
void printString(char* str);

/*  mengubah char *menjadi integer.
    Jika s bukan angka, error_code 303, s tetap.*/
int stringToInteger (char *s);

#endif