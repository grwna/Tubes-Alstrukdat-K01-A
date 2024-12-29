#include "mesinkarakter.h"
#include <stdio.h>
#include <stdlib.h>

char currentChar;
boolean EOP;
boolean EOP_FILE;
boolean first = true;

static FILE *pita;
static int retval;

void START()
{   
    pita = stdin;
    ADV();
}

void STARTFILE(char *dir)
{
    pita = fopen(dir,"r");
    if(pita == NULL){
        error_code = 303;
        return;
    }
    ADV();
}

void ADV() {
    retval = fscanf(pita,"%c",&currentChar);
    EOP = (currentChar == MARK);
    EOP_FILE = (retval != 1);
    if (EOP || EOP_FILE) {
        CLOSE();
    }
    // pita = NULL;
}

void CLOSE(){
    if(pita != NULL){
        if(pita != stdin){
            fclose(pita);
        }
        pita = NULL;
    }
}

void FINALCLOSE(){
    if(pita != NULL){
        fclose(pita);
    }
    pita = NULL;
}

void ADV_ENTER(){
    retval = fscanf(pita,"%c",&currentChar);
    EOP = (currentChar == '\n');
    EOP_FILE = (retval != 1);
    if (EOP || EOP_FILE) {
        CLOSE();
    }
}

void START_ENTER(){
    if(first){
        first = false;
    }
    pita = stdin;
    ADV_ENTER();
}

void waitForEnter(){
    if(!first){
        START();
        CLOSE();   
    }
    printf("\nPress enter to continue...");
    START_ENTER();
    while(!EOP){
        ADV_ENTER();
    }
    system("clear");
}