#include <stdio.h>
#include "mesinkata.h"

boolean EndWord;
Word currentWord;

void IgnoreBlanks() {
    while (currentChar == BLANK || currentChar == BLANK_FILE || currentChar == BLANK_FILE2) {
        ADV(); 
    }
}

void STARTBLOCK() {
    START();
    IgnoreBlanks();
    if (currentChar == MARK) {
        currentWord.Length = 0;
        currentWord.TabWord[0] = '\0';
        EndWord = true;
    } else {
        EndWord = false;
        CopyBlock();
    }
}

void STARTWORD() {
    START();
    IgnoreBlanks();
    if (currentChar == MARK) {
        currentWord.Length = 0;
        currentWord.TabWord[0] = '\0';
        EndWord = true;
    } else {
        EndWord = false;
        CopyWord();
    }
}

void STARTFILELINE(char *dir) {
    STARTFILE(dir);
    IgnoreBlanks();
    if (EOP_FILE) {
        currentWord.Length = 0;
        currentWord.TabWord[0] = '\0';
        EndWord = true;
    } else {
        EndWord = false;
        CopyLine();
    }
}

void ADVWORD() {
    IgnoreBlanks();
    if (EOP) {
        currentWord.Length = 0;
        currentWord.TabWord[0] = '\0';
        EndWord = true;
    } else {
        EndWord = false;
        CopyWord();
        IgnoreBlanks();
    }
}

void ADVLINE(){
    IgnoreBlanks();
    if(EOP_FILE){
        currentWord.Length = 0;
        currentWord.TabWord[0] = '\0';
        EndWord = true;
    } else {
        EndWord = false;
        CopyLine();
        IgnoreBlanks();
    }
}

void CopyBlock(){
    int i = 0;
    while(!EOP && currentChar != MARK && i < NMax){
        currentWord.TabWord[i] = currentChar;
        ADV();
        i++;
    }
    if(i == NMax && !EOP){
        error_code = 401;
        currentWord.TabWord[0] = '\0';
        currentWord.Length = 0;
        return;
    }
    currentWord.TabWord[i] = '\0';
    currentWord.Length = i;
}

void CopyWord() {
    int i = 0;
    while (!EOP && currentChar != MARK && currentChar != BLANK && i < NMax) {
        currentWord.TabWord[i] = currentChar;
        ADV();
        i++;
    }
    if(i == NMax && !EOP){
        error_code = 401;
        currentWord.TabWord[0] = '\0';
        currentWord.Length = 0;
        return;
    }
    
    currentWord.TabWord[i] = '\0';
    currentWord.Length = i;
}

void CopyLine(){
    int i = 0;
    while(!EOP_FILE && currentChar != BLANK_FILE && currentChar != BLANK_FILE2 && i < NMax){

        currentWord.TabWord[i] = currentChar;
        ADV();
        i++;
    }
    if(currentWord.TabWord[i-1] == '\\'){
        currentWord.TabWord[i-1] = '\n';
    }
    currentWord.TabWord[i] = '\0';
    currentWord.Length = i;
}

int convertCurrentWordToInt(){
    int res = 0, neg_mult = 1;
    int i = 0;
    if(currentWord.TabWord[i] == '-'){
        neg_mult = -1;
        i++;
    }
    for(; i < currentWord.Length; i++){
        if(!(currentWord.TabWord[i] - '0' <= 9 && currentWord.TabWord[i] - '0' >= 0)){
            error_code = 201;
            return -1;
        }
        res = res*10 + (currentWord.TabWord[i] - '0');
    }
    return res*neg_mult;
}

void printCurrentWord(){
    printString(currentWord.TabWord);
    printf("\n");
}