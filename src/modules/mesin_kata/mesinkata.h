/* File: mesinkata.h */
/* Definisi Mesin Word: Model Akuisisi Versi I */

#ifndef __MESINKATA_H__
#define __MESINKATA_H__

#include "mesinkarakter.h"
#include "../utility/string.h"

#define NMax 1000
#define BLANK ' '
#define BLANK_FILE '\n'
#define BLANK_FILE2 '\r'

#define HANDLE_EOP_ERROR() do { \
    if (!EOP) { \
        while (!EOP) { \
            ADVWORD(); \
        } \
        error_code = 399; \
    } \
} while (0)

typedef struct
{
   char TabWord[NMax+1]; /* container penyimpan kata, indeks yang dipakai [0..NMax-1] */
   int Length;
} Word;

/* State Mesin Word */
extern boolean EndWord;
extern Word currentWord;

void IgnoreBlanks();
/* Mengabaikan satu atau beberapa BLANK
   I.S. : currentChar sembarang
   F.S. : currentChar ≠ BLANK atau currentChar = MARK */

void STARTBLOCK();
/* I.S. : currentChar sembarang
   F.S. : EndWord = true, dan currentChar = MARK;
          atau EndWord = false, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */

void STARTWORD();
/* I.S. : currentChar sembarang
   F.S. : EndWord = true, dan currentChar = MARK;
          atau EndWord = false, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */

void STARTFILELINE(char *dir);
/* I.S. : currentChar sembarang
   F.S. : EndWord = true, dan currentChar = MARK;
          atau EndWord = false, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */

void ADVWORD();
/* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
   F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
          currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika currentChar = MARK, EndWord = true.
   Proses : Akuisisi kata menggunakan procedure SalinWord */

void ADVLINE();
/* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
   F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
          currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika currentChar = MARK, EndWord = true.
   Proses : Akuisisi kata menggunakan procedure SalinWord */

void CopyBlock();
/* Mengakuisisi blok, menyimpan dalam currentWord
   I.S. : currentChar adalah karakter pertama dari blok
   F.S. : currentWord berisi blok yang sudah diakuisisi;
          currentChar = MARK;
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang blok melebihi NMax, maka sisa blok "dipotong" */

void CopyLine();
/* Mengakuisisi baris, menyimpan dalam currentWord
   I.S. : currentChar adalah karakter pertama dari baris
   F.S. : currentWord berisi baris yang sudah diakuisisi;
          currentChar = BLANK atau currentChar = MARK;
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang baris melebihi NMax, maka sisa baris "dipotong" */

void CopyWord();
/* Mengakuisisi kata, menyimpan dalam currentWord
   I.S. : currentChar adalah karakter pertama dari kata
   F.S. : currentWord berisi kata yang sudah diakuisisi;
          currentChar = BLANK atau currentChar = MARK;
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */

int convertCurrentWordToInt();
// mengubah currentWord menjadi integer

int wordToInteger(Word w);
// mengubah Word yang sudah terdefinisi menjadi integer

void printCurrentWord();
// menampilkan currentWord ke terminal

#endif