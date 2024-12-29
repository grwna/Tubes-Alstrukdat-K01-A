#include "search.h"

Trie currentTrieRoot;

void createEmailIdList(emailIdList* result, int size){
    BUFFER_IDLIST(*result) = (int *) malloc(size * sizeof(int));
    if(BUFFER_IDLIST(*result) == NULL){
        CAPACITY_IDLIST(*result) = 0;
    } else {
        CAPACITY_IDLIST(*result) = size;
    }
    NEFF_IDLIST(*result) = 0;
}

boolean isFull_EmailIdList(emailIdList result){
    return NEFF_IDLIST(result) == CAPACITY_IDLIST(result);
}

boolean hasElmt(emailIdList result, int emailId){
    for(int i = 0; i < NEFF_IDLIST(result); i++){
        if(ELMT_IDLIST(result, i) == emailId){
            return true;
        }
    }
    return false;
}

void insertEmailIdList(emailIdList* result, int emailId){
    if(NEFF_IDLIST(*result) == CAPACITY_IDLIST(*result)){
        expandEmailIdList(result, 10);
    }
    ELMT_IDLIST(*result, NEFF_IDLIST(*result)) = emailId;
    NEFF_IDLIST(*result)++;
}

void expandEmailIdList(emailIdList* result, int num){
    CAPACITY_IDLIST(*result) += num;
    int *newBuffer = (int *) malloc(CAPACITY_IDLIST(*result) * sizeof(int));
    for(int i = 0; i < NEFF_IDLIST(*result); i++){
        newBuffer[i] = ELMT_IDLIST(*result, i);
    }
    free(BUFFER_IDLIST(*result));
    BUFFER_IDLIST(*result) = newBuffer;
}

void freeEmailIdList(emailIdList* result){
    if(BUFFER_IDLIST(*result) != NULL){
        free(BUFFER_IDLIST(*result));
    }
    BUFFER_IDLIST(*result) = NULL;
    CAPACITY_IDLIST(*result) = 0;
    NEFF_IDLIST(*result) = 0;
}

Trie createTrieNode(char c){
    Trie newNode = (Trie) malloc(sizeof(TrieNode));
    if(newNode != NULL){
        newNode->c = c;
        for(int i = 0; i < 26; i++){
            newNode->children[i] = NULL;
        }
        createEmailIdList(&(IDLIST_Trie(newNode)), 10);
    }
    return newNode;
}

void insertChildTrie(Trie* parent, Trie child){
    (*parent)->children[child->c - 'a'] = child;
}

void initTrie(Trie* root){
    *root = createTrieNode('\0');
}

void lowercase(char* word){
    for(int i = 0; word[i] != '\0'; i++){
        if(word[i] >= 'A' && word[i] <= 'Z'){
            word[i] += 32;
        }
    }
}

/* mengembalikan index terakhir dari kata yang valid */
int wordValidUntil(int start, char* word){
    int i = start;
    for(; word[i] != '\0'; i++){
        if((word[i] < 'a' || word[i] > 'z')){
            return i-1;
        }
    }
    return i-1;
}

void insertWord(Trie* root, char* word, int emailId){
    String temp;
    assignString(temp, SIZE(temp), word);
    lowercase(temp);
    int length = stringLength(temp), i = 0;
    Trie current = *root;
    while(i < length){
        int start = i;
        int end = wordValidUntil(start, temp);
        for(; i < end-start+1; i++){
            if(current->children[temp[i] - 'a'] == NULL){
                Trie newNode = createTrieNode(temp[i]);
                insertChildTrie(&current, newNode);
            }
            current = current->children[temp[i] - 'a'];
            if(hasElmt(IDLIST_Trie(current), emailId)){
                continue;
            }
            if(isFull_EmailIdList(IDLIST_Trie(current))){
                expandEmailIdList(&(IDLIST_Trie(current)), 10);
            }
            insertEmailIdList(&(IDLIST_Trie(current)), emailId);
        }
        do{
            i++;
        }while(i < length && (temp[i] < 'a' || temp[i] > 'z'));
    }
}

void fillTrieFromInbox(Trie* root, EmailList inbox){
    for(int i = 0; i < listLength_EmailList(inbox); i++){
        LargeString word;
        assignString(word, SIZE(word), "");
        int length = stringLength(SUBJECT_Email(ELMT_EmailList(inbox, i)));
        for(int j = 0; j < length; j++){
            if(SUBJECT_Email(ELMT_EmailList(inbox, i))[j] == ' ' || j == length-1){
                insertWord(root, word, ID_Email(ELMT_EmailList(inbox, i)));
                assignString(word, SIZE(word), "");
                continue;
            }
            appendChar(word, SIZE(word), SUBJECT_Email(ELMT_EmailList(inbox, i))[j]);
        }
        length = stringLength(BODY_Email(ELMT_EmailList(inbox, i)));
        assignString(word, SIZE(word), "");
        for(int j = 0; j < length; j++){
            if(BODY_Email(ELMT_EmailList(inbox, i))[j] == ' ' || BODY_Email(ELMT_EmailList(inbox, i))[j] == '\n' || j == length-1){
                insertWord(root, word, ID_Email(ELMT_EmailList(inbox, i)));
                assignString(word, SIZE(word), "");
                continue;
            }
            appendChar(word, SIZE(word), BODY_Email(ELMT_EmailList(inbox, i))[j]);
        }
    }
}

boolean isWordValid(char* word){
    for(int i = 0; word[i] != '\0'; i++){
        if(word[i] < 'a' || word[i] > 'z'){
            return false;
        }
    }
    return true;
}

emailIdList* getSearchResult(Trie root, char* word){
    String temp;
    assignString(temp, SIZE(temp), word);
    lowercase(temp);
    if(!isWordValid(temp)){
        return NULL;
    }
    Trie current = root;
    for(int i = 0; i < stringLength(temp); i++){
        if(current->children[temp[i] - 'a'] == NULL){
            return NULL;
        }
        current = current->children[temp[i] - 'a'];
    }
    return &(IDLIST_Trie(current)); 
}

void getSearchEmails(char* keyword){
    emailIdList *result = getSearchResult(currentTrieRoot, keyword);
    if(result == NULL){
        deallocateList(&searchResult);
        createEmailList(&searchResult, 5);
        return;
    }
    int count = result->nEff;
    deallocateList(&searchResult);
    createEmailList(&searchResult, count+5);
    for (int i = 0; i < listLength_EmailList(AllEmails) && count > 0; i++){
        for (int j = 0; j < result->nEff; j++){
            if (ID_Email(ELMT_EmailList(AllEmails, i)) == result->buffer[j])
            {
                insertLast_EmailList(&searchResult, ELMT_EmailList(AllEmails, i));
                // printf("Email %d\n", ID_Email(ELMT_EmailList(AllEmails, i)));
                count--;
            }
        }
    }
    result = NULL;
    // sortEmailListbyTime(&searchResult);
}


void freeTrie(Trie *root){
    if(*root == NULL){
        return;
    }
    for(int i = 0; i < 26; i++){
        freeTrie(&((*root)->children[i]));
    }
    freeEmailIdList(&(IDLIST_Trie(*root)));
    free(*root);
}
