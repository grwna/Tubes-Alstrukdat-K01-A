#include <stdio.h>
#include "display_inbox.h"

int main() {

    loadConfigEmail("config/config1/email.config");
    // printEmailList(AllEmails);

    loadConfigPengguna("config/config1/pengguna.config");    
    // printUserList(users);

    loadConfigUmum("config/config1/umum.config");

    STARTFILE("config/key.txt");

    while (true) {
        int temp;
        printf("\nMasukkan ID user (0 untuk keluar): ");
        scanf("%d", &temp);
        if (temp != 0) {
            userLogin(temp);
        } else {
            break;
        }

        printf("pilihan input: KELUAR, DAFTAR_INBOX, DAFTAR_STARRED\n");
        printf(">> ");
        STARTWORD();
        // printf("kata yang dimasukkan: ");
        // printString(wordToString(currentWord));

        while (true) {
        
            if (isStringEqual(currentWord.TabWord, "DAFTAR_INBOX")) {
                printf("\n");
                displayInbox();
            } else if (isStringEqual(currentWord.TabWord, "DAFTAR_STARRED")) {
                printf("\n");
                displayStarred();
            } else if (isStringEqual(currentWord.TabWord, "KELUAR")) {
                break;
            } else {
                printAsRed("bukan input valid brow.\n");
            }

            printf("\npilihan input: KELUAR, DAFTAR_INBOX, DAFTAR_STARRED\n");
            printf(">> ");
            STARTWORD();
        }
    }
    return 0;
}