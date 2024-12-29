#include <stdio.h>
#include "mesinkarakter.h"
#include "mesinkata.h"

int main() {
    // // Initialize the character machine
    // START();
    // printf("Reading characters:\n");
    // while (!EOP) {
    //     printf("%c", GetCC());
    //     ADV();
    // }
    // printf("\nEnd of character reading.\n");

    // Initialize the word machine
    printf("Reading words: ");
    STARTWORD();
    while (!EOP) {
        printCurrentWord();
        ADVWORD();
    }
    printCurrentWord();
    printf("End of word reading.\n");
    printf("New session:\n");
    printf("Reading words: ");
    STARTWORD();
    while (!EOP) {
        printCurrentWord();
        ADVWORD();
    }
    printCurrentWord();
    printf("End of word reading.\n");
    return 0;
}

