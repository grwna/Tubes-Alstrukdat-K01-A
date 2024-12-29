#include <stdio.h>
#include <stdlib.h>
#include "search.h"

void printTrie(Trie root, int level) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < 26; i++) {
        if (root->children[i] != NULL) {
            for (int j = 0; j < level; j++) {
                printf(" ");
            }
            printf("level %d: ", level + 1);
            printf("%c\n", root->children[i]->c);
            printTrie(root->children[i], level + 1);
        }
    }
}

int main() {
    currentTrieRoot = NULL;
    initTrie(&currentTrieRoot);
    // for(int i = 0; i < 26; i++){
    //     printf("%d\n", i);
    //     if(currentTrieRoot->children[i] == NULL){
    //         printf("NULL\n");
    //     }
    // }
    insertWord(&currentTrieRoot, "HelloWorld!", 1);
    insertWord(&currentTrieRoot, "Help", 1);
    insertWord(&currentTrieRoot, "Heller", 2);
    insertWord(&currentTrieRoot, "World", 2);
    insertWord(&currentTrieRoot, "Hell", 3);
    insertWord(&currentTrieRoot, "Worl", 4);
    insertWord(&currentTrieRoot, "Subjek", 5);
    insertWord(&currentTrieRoot, "Subjekt", 6);
    // printf("Bollocks\n");
    emailIdList *results = getSearchResult(currentTrieRoot, "Subjek");
    for (int i = 0; i < NEFF_IDLIST(*results); i++) {
        printf("%d ", ELMT_IDLIST(*results, i));
    }
    printf("\n");
    // printTrie(currentTrieRoot, 0);
    return 0;
}