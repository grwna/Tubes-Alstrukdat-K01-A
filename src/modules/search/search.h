#ifndef SEARCH_H
#define SEARCH_H

#include "../utility/boolean.h"
#include "../utility/string.h"
#include "../email_list/email_list.h"
#include <stdlib.h>

typedef struct {
    int *buffer;    /* buffer of all email ids that matches the search result. */
    int nEff;       /* effective length of the buffer. */
    int capacity;   /* capacity of the buffer. */
} emailIdList;

#define BUFFER_IDLIST(result) (result).buffer
#define NEFF_IDLIST(result) (result).nEff
#define CAPACITY_IDLIST(result) (result).capacity
#define ELMT_IDLIST(result, i) (result).buffer[i]

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create search result */
/* I.S. result sembarang */
/* F.S. result berisi buffer kosong dengan size 0 */
void createEmailIdList(emailIdList* result, int size);

/*  I.S. result terdefinisi, result tidak penuh 
    F.S. result berisi emailId di akhir buffer */
void insertEmailIdList(emailIdList* result, int emailId);

/*  I.S. result terdefinisi
    F.S. mengembalikan true jika result penuh */
boolean isFull_EmailIdList(emailIdList result);

/*  I.S. result terdefinisi, emailId terdefinisi
    F.S. mengembalikan true jika emailId ada di result */
boolean hasElmt(emailIdList result, int emailId);

/*  I.S. result terdefinisi 
    F.S. result memiliki capacity baru, sebanyak size+num */
void expandEmailIdList(emailIdList* result, int num);

/*  I.S. result terdefinisi
    F.S. result di dealokasikan. */
void freeEmailIdList(emailIdList* result);

typedef struct trieNode* Trie;
typedef struct trieNode { 
    char c;
    Trie children[26];
    emailIdList occurrences;        /* List of emailId that contains the word. */
} TrieNode;

#define IDLIST_Trie(T) (T)->occurrences

extern Trie currentTrieRoot; // Global variable to store the current trie, filled with all words in inbox emails.

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create trie node */
/* I.S. c dan isEnd terdefinisi */
/* F.S. menghasilkan trie node baru */
Trie createTrieNode(char c);

/*  I.S. parent dan child terdefinisi
    F.S. child diinsert ke parent */
void insertChildTrie(Trie* parent, Trie child);

/*  I.S. root sembarang
    F.S. root diisikan '\0', sebagai awal kata. */
void initTrie(Trie* root);

/*  I.S. root terdefinisi, word terdefinisi
    F.S. word diinsert ke trie */
void insertWord(Trie* root, char* word, int emailId);

/*  I.S. root terdefinisi
    F.S. trie diisi dengan semua kata yang ada di inbox */
void fillTrieFromInbox(Trie* root, EmailList inbox);

/*  root terdefinisi, word terdefinisi
    mengembalikan pointer ke emailIdList yang berisi semua emailId memiliki prefix word. 
    RESULT JANGAN DI DEALLOCATE!!, selesai pakai ubah ke NULL. */
emailIdList* getSearchResult(Trie root, char* word);

/*  I.S. keyword terdefinisi
    F.S. searchResult berisi email yang memiliki keyword di subject atau body */
void getSearchEmails(char* keyword);

/*  I.S. root terdefinisi
    F.S. tree dari root ke bawah di dealokasikan */
void freeTrie(Trie* root);

#endif