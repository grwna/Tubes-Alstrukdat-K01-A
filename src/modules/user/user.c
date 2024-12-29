#include "user.h"
#include "../busy_schedule/busy_schedule.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

int currentUserId = IDX_UNDEF;
UserList users;

void copyStarredList(StarredList *dst, StarredList src){
    createStarredList(dst, src.capacity);
    for(int i = 0; i < src.nEff; i++){
        ELMT_StarredList(*dst, i) = ELMT_StarredList(src, i);
    }
    NEFF_StarredList(*dst) = NEFF_StarredList(src);
}

void createUser(User *user, String userEmail, String password, StarredList starredList){
    ID_User(*user) = listLength_UserList(users) + 1;
    assignString(EMAIL_User(*user), SIZE(EMAIL_User(*user)), userEmail);
    assignString(PASSWORD_User(*user), SIZE(PASSWORD_User(*user)), password);
    copyStarredList(&STARREDLIST_User(*user), starredList);
    createBusySchedule(user, 7, 24);
}

int listLength_UserList(UserList l){
    return NEFF_UserList(l);
}

void CreateUserList(UserList *l){
    NEFF_UserList(*l) = 0;
}

boolean isEmpty_UserList(UserList l){
    return !NEFF_UserList(l);
}

boolean isFull_UserList(UserList l){
    return NEFF_UserList(l) == CAPACITY_User;
}

int indexOf_UserList(UserList l, String userEmail){
    for(int i = 0; i < listLength_UserList(l); i++){
        if(isStringEqual(EMAIL_User(ELMT_UserList(l, i)), userEmail)){
            return i;
        }
    }
    return IDX_UNDEF;
}

void insertLast_UserList(UserList *l, User newUser){
    int index = listLength_UserList(*l);
    createUser(&ELMT_UserList(*l, index), newUser.userEmail, newUser.password, STARREDLIST_User(newUser));
    NEFF_UserList(*l)++;
}

boolean isUsernameCharValid(char c){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '.' || c == '_' || c == '%' || c == '+' || c == '-';
}

boolean isDomainCharValid(char c){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '.' || c == '-';
}

boolean isTLDCharValid(char c){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

boolean isUserEmailValid(String userEmail){
    int i = 0;
    int atIdx = IDX_UNDEF;
    while(userEmail[i] != '\0' && userEmail[i] != '@'){
        if(!isUsernameCharValid(userEmail[i])){
            return false;
        }
        i++;
    }
    if(i == 0 || userEmail[i] != '@'){ // no username or no @
        return false;
    }
    atIdx = i;
    int lastDotIdx = IDX_UNDEF;
    i++;

    while(userEmail[i] != '\0'){
        if(!isDomainCharValid(userEmail[i])){
            return false;
        }
        if(userEmail[i] == '.'){
            lastDotIdx = i;
        }
        i++;
    }
    if(i - lastDotIdx <= 2 || lastDotIdx == IDX_UNDEF || lastDotIdx == atIdx + 1){ // less than 2 tld chars, or not dots, or no domain chars 
        return false;
    }
    i--;
    while(i > lastDotIdx){
        if(!isTLDCharValid(userEmail[i])){
            return false;
        }
        i--;
    }
    return true;
}

boolean isPasswordValid(String pw){
    return !(isEmpty_String(pw) || stringLength(pw) >= 20);
}

void initUserList(){
    CreateUserList(&users);
}

void addUser(String userEmail, String password, StarredList starredList){
    User newUser;
    createUser(&newUser, userEmail, password, starredList);
    insertLast_UserList(&users, newUser);
}

void createStarredList(StarredList *l, int capacity) {
    CAPACITY_StarredList(*l) = capacity;
    NEFF_StarredList(*l) = 0;
    BUFFER_StarredList(*l) = (int *) malloc(capacity * (sizeof(int)));
    if(BUFFER_StarredList(*l) == NULL){
        CAPACITY_StarredList(*l) = 0;
    }
}

void deallocateStarredList(StarredList *l){
    if(BUFFER_StarredList(*l) != NULL){
        free(BUFFER_StarredList(*l));
    }
    BUFFER_StarredList(*l) = NULL;
    CAPACITY_StarredList(*l) = 0;
    NEFF_StarredList(*l) = 0;
}

void expandStarredList(StarredList *l, int num){
    CAPACITY_StarredList(*l) += num;
    BUFFER_StarredList(*l) = realloc(BUFFER_StarredList(*l), CAPACITY_StarredList(*l) * sizeof(int));
}

void shrinkStarredList(StarredList *l, int num){
    CAPACITY_StarredList(*l) -= num;
    BUFFER_StarredList(*l) = realloc(BUFFER_StarredList(*l), CAPACITY_StarredList(*l) * sizeof(int));
}

void compressStarredList(StarredList *l){
    CAPACITY_StarredList(*l) = NEFF_StarredList(*l);
    BUFFER_StarredList(*l) = realloc(BUFFER_StarredList(*l), CAPACITY_StarredList(*l) * sizeof(int));
}

int findUserIdByEmail(String userEmail){
    int userId = indexOf_UserList(users, userEmail); 
    if(userId == IDX_UNDEF){
        return IDX_UNDEF;
    }
    return userId + 1;
}

User findUserByID(int id) {
    for(int i = 0; i < listLength_UserList(users); i++){
        if (ID_User(ELMT_UserList(users, i)) == id) {
            return ELMT_UserList(users, i);
        }
    }

    User bodong;
    ID_User(bodong) = 0;
    assignString(EMAIL_User(bodong), SIZE(EMAIL_User(bodong)), "");
    assignString(PASSWORD_User(bodong), SIZE(PASSWORD_User(bodong)), "");
    Matrix kosongMat;
    createMatrix(0, 0, &kosongMat);

    StarredList kosong;
    createStarredList(&kosong, 0);
    NEFF_StarredList(kosong) = 0;
    STARREDLIST_User(bodong) = kosong;
    return bodong;
}

boolean isLoginValid(int id, String password){
    return isStringEqual(PASSWORD_User(ELMT_UserList(users, id-1)), password);
}

void userLogin(int id){
    currentUserId = id;
}

void userLogout(){
    currentUserId = IDX_UNDEF;
}

void printUserList(UserList l){
    for (int i = 0; i < listLength_UserList(l); i++){
        printf("User %d\n", ID_User(ELMT_UserList(l, i)));
        printf("Email: ");
        printString(EMAIL_User(ELMT_UserList(l, i)));
        printf("\n");
        printf("Password: ");
        printString(PASSWORD_User(ELMT_UserList(l, i)));    
        printf("\n");
        displayMatrix(SCHEDULE_User(ELMT_UserList(l, i)));
        printf("Jumlah starred email: %d\n", NEFF_StarredList(STARREDLIST_User(ELMT_UserList(l, i))));
        for (int j = 0; j < NEFF_StarredList(STARREDLIST_User(ELMT_UserList(l, i))); j++) {
            printf("%d,", ELMT_StarredList(STARREDLIST_User(ELMT_UserList(l, i)), j));
        }
        printf("\n\n");
    }
}