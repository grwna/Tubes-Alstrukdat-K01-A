#include "user.h"
#include <stdio.h>
#include "../mesin_kata/mesinkata.h"

int main(){
    initUserList();
    String email;
    String password;
    StarredList starredList;
    createStarredList(&starredList, 5);
    NEFF_StarredList(starredList) = 1;
    ELMT_StarredList(starredList, 0) = 1;

    assignString(password, SIZE(password), "password");
    for (int i = 0; i < 10; i++){
        email[0] = i + '0';
        email[1] = '@';
        email[2] = 'g';
        email[3] = '.';
        email[4] = 'c';
        email[5] = 'o';
        email[6] = 'm';
        email[7] = '\0';
        addUser(email, password, StarredList);
        printf("User %d registered\n", 1);
    }
    printUserList(users);
    while(true){
        int exit;
        printf("Exit? (1/0): ");
        scanf("%d", &exit);
        if(exit){
            break;
        }
        int logout;
        if(currentUserId != -1){
            printf("Logout? (1/0): ");
            scanf("%d", &logout);
            if(logout){
                userLogout();
                printf("Logged out\n");
            }
        }
        char c;
        printf("Masukkan email: ");
        STARTWORD();
        printf("Current word Length: %d\n", currentWord.Length);
        assignString(email, SIZE(email), currentWord.TabWord);
        if(isUserEmailValid(email)){
            printf("Email Valid\n");
        } else {
            printf("Email Tidak Valid\n");
            continue;
        }
        int userId = findUserIdByEmail(email);
        if(userId == -1){
            printf("Email not found!\n");
            continue;
        }
        if(currentUserId != -1){
            printf("User %d is currently logged in, please logout first\n", currentUserId);
            continue;
        }
        printf("Enter password: ");
        STARTWORD();
        assignString(password, SIZE(password), currentWord.TabWord);
        if(isLoginValid(userId, password)){
            printf("Login Success!!\n");
            userLogin(userId);
            printf("Logged in as %d\n", currentUserId);
        } else {
            printf("Login Failed\n");
            continue;
        }
        printf("Logout? (1/0): ");
        scanf("%d", &logout);
        if(logout){
            userLogout();
            printf("Logged out\n");
        }
    }
    return 0;
}
