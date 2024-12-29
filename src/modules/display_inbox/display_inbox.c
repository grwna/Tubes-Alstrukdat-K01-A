#include <stdio.h>
#include "display_inbox.h"

void createID (String id, int i) {
    assignString(id, (size_t) 256, "EMAIL");
    id[5] = (i / 100) + '0';
    id[6] = ((i / 10) % 10) + '0';
    id[7] = (i % 10) + '0';
    id[8] = '\0';  
}

void printAsRed (char *str) {
    int i = 0;
    while (str[i] != '\0') {
        printf("\033[31m%c", str[i]);
        i++;
    }
    printf("\033[0m\n");
}

void displayInbox() {

    if (EOP) {
        getInbox();

        int kosong = 0;
        if (NEFF_EmailList(inbox) == 0) {
            kosong = 1;
        }
        
        int paginasi;
        if (!kosong) {
            paginasi = NEFF_EmailList(inbox) / paginationLimit;
            if (NEFF_EmailList(inbox) % paginationLimit == 0) {
                paginasi--;
            }
        } else {
            paginasi = 0;
        }

        int longestSubject[paginasi + 1];
        int longestSender[paginasi + 1];
        Email currentEmail;
        String currentSender;

        for (int i = 0; i < paginasi + 1; i++) {
            longestSubject[i] = 7;
            longestSender[i] = 8;

            for (int j = i * paginationLimit; j < (i + 1) * paginationLimit; j++) {
                if (j == NEFF_EmailList(inbox)) {
                    break;
                }

                currentEmail = ELMT_EmailList(inbox, j);

                if (stringLength(SUBJECT_Email(currentEmail)) > longestSubject[i]) {
                    longestSubject[i] = stringLength(SUBJECT_Email(currentEmail));
                }
            
                int senderId = FROM_Email(currentEmail);
                assignString(currentSender, SIZE(currentSender), ELMT_UserList(users, senderId-1).userEmail);

                if (stringLength(currentSender) > longestSender[i]) {
                    longestSender[i] = stringLength(currentSender);
                }
            }
        }

        int listEmailtoOpen[paginationLimit];
        for (int j = 0; j < paginationLimit; j++) {
            listEmailtoOpen[j] = 0;
        }
        assignString(currentWord.TabWord, SIZE(currentWord.TabWord), "SEBELUM");
        int currentPage = 1;
        while (true) {
            if (isStringEqual(currentWord.TabWord, "SEBELUM")) {
                if (EOP) {
                    currentPage--;
                    system("clear");
                } else {
                    while (!EOP) {
                        ADVWORD();
                    }
                    printAsRed("Setelah SEBELUM jangan ada kata-kata lagi yaa\n!");
                    waitForEnter();
                }
            } else if (isStringEqual(currentWord.TabWord, "LANJUT")) {
                if (EOP) {
                    currentPage++;
                    system("clear");
                } else {
                    while (!EOP) {
                        ADVWORD();
                    }
                    printAsRed("Setelah LANJUT jangan ada kata-kata lagi yaa\n!");
                    waitForEnter();
                }
            } else if (isStringEqual(currentWord.TabWord, "BACA_PESAN")) {
                
                /* skema baca_pesan */
                boolean validEmailID = true;
                ADVWORD();
                if (currentWord.Length != 8) {
                    printAsRed("bukan email ID yang valid untuk dibaca.\n");
                    validEmailID = false;
                    waitForEnter();
                } else {
                    String EMAIL;
                    assignString(EMAIL, SIZE(EMAIL), "EMAIL");
                    for (int i = 0; i < 5; i++) {
                        if (currentWord.TabWord[i] != EMAIL[i]) {
                            printAsRed("bukan email ID yang valid untuk dibaca.\n");
                            waitForEnter();
                            validEmailID = false;
                            break;
                        }  
                    }
                }

                if (validEmailID) {
                    for (int i = 5; i < 8; i++) {
                        if (!((0 <= currentWord.TabWord[i] - '0') && (currentWord.TabWord[i] - '0' <= 9))) {
                            printAsRed("bukan email ID yang valid untuk dibaca.\n");
                            waitForEnter();
                            validEmailID = false;
                            break;  
                        } 
                    }
                }

                if (validEmailID) {
                    int temp = ((currentWord.TabWord[5] - '0') * 100) + ((currentWord.TabWord[6] - '0') * 10) + (currentWord.TabWord[7] - '0');

                    int check;
                    for (check = 0; check < paginationLimit; check++) {
                        if (listEmailtoOpen[check] == temp) {
                            break;
                        }
                    }

                    if ((check == paginationLimit) || (temp == 0)) {
                        printAsRed("Tidak ada email tersebut pada page inbox saat ini.\n");
                        waitForEnter();
                    } else {
                        bacaPesan(temp, true, false);
                    }
                }
            } else if (isStringEqual(currentWord.TabWord, "KELUAR")) {
                if (EOP) {
                    printf("Anda telah keluar dari Inbox.\n");
                    break;      
                } else {
                    while (!EOP) {
                        ADVWORD();
                    }
                    printAsRed("Setelah KELUAR jangan ada kata-kata lagi yaa\n!");
                    waitForEnter();
                }      
            } else if (isStringEqual(currentWord.TabWord, "STAR")) {
                
                /* skema star */
                boolean validEmailID = true;
                ADVWORD();
                if (currentWord.Length != 8) {
                    printAsRed("bukan email ID yang valid untuk di-star.\n");
                    waitForEnter();
                    validEmailID = false;
                } else {
                    String EMAIL;
                    assignString(EMAIL, SIZE(EMAIL), "EMAIL");
                    for (int i = 0; i < 5; i++) {
                        if (currentWord.TabWord[i] != EMAIL[i]) {
                            printAsRed("bukan email ID yang valid untuk di-star.\n");
                            waitForEnter();
                            validEmailID = false;
                            break;
                        }  
                    }
                }

                if (validEmailID) {
                    for (int i = 5; i < 8; i++) {
                        if (!((0 <= currentWord.TabWord[i] - '0') && (currentWord.TabWord[i] - '0' <= 9))) {
                            printAsRed("bukan email ID yang valid untuk di-star.\n");
                            waitForEnter();
                            validEmailID = false;
                            break;  
                        } 
                    }
                }

                if (validEmailID) {
                    int temp = ((currentWord.TabWord[5] - '0') * 100) + ((currentWord.TabWord[6] - '0') * 10) + (currentWord.TabWord[7] - '0');

                    int check;
                    for (check = 0; check < listLength_EmailList(inbox); check++) {
                        if (ID_Email(ELMT_EmailList(inbox, check)) == temp) {
                            break;
                        }
                    }

                    if (check == listLength_EmailList(inbox)) {
                        printAsRed("User tidak memiliki email dengan ID tersebut untuk di-star.\n");
                        waitForEnter();
                    } else {
                        setAsStarred(temp);
                    }
                }
            } else if (isStringEqual(currentWord.TabWord, "UNSTAR")) {
                
                /* skema star */
                boolean validEmailID = true;
                ADVWORD();
                if (currentWord.Length != 8) {
                    printAsRed("bukan email ID yang valid untuk di-unstar.\n");
                    waitForEnter();
                    validEmailID = false;
                } else {
                    String EMAIL;
                    assignString(EMAIL, SIZE(EMAIL), "EMAIL");
                    for (int i = 0; i < 5; i++) {
                        if (currentWord.TabWord[i] != EMAIL[i]) {
                            printAsRed("bukan email ID yang valid untuk di-unstar.\n");
                            waitForEnter();
                            validEmailID = false;
                            break;
                        }  
                    }
                }

                if (validEmailID) {
                    for (int i = 5; i < 8; i++) {
                        if (!((0 <= currentWord.TabWord[i] - '0') && (currentWord.TabWord[i] - '0' <= 9))) {
                            printAsRed("bukan email ID yang valid untuk di-unstar.\n");
                            waitForEnter();
                            validEmailID = false;
                            break;  
                        } 
                    }
                }

                if (validEmailID) {
                    int temp = ((currentWord.TabWord[5] - '0') * 100) + ((currentWord.TabWord[6] - '0') * 10) + (currentWord.TabWord[7] - '0');

                    int check;
                    for (check = 0; check < listLength_EmailList(inbox); check++) {
                        if (ID_Email(ELMT_EmailList(inbox, check)) == temp) {
                            break;
                        }
                    }

                    if (check == listLength_EmailList(inbox)) {
                        printAsRed("User tidak memiliki email dengan ID tersebut untuk di-unstar.\n");
                        waitForEnter();
                    } else {
                        setAsUnstarred(temp);
                    }
                }
            } else if (isStringEqual(currentWord.TabWord, "BALAS_PESAN")) {
                
                /* skema balas_pesan */
                boolean validEmailID = true;
                ADVWORD();
                if (currentWord.Length != 8) {
                    printAsRed("bukan email ID yang valid untuk dibaca.\n");
                    waitForEnter();
                    validEmailID = false;
                } else {
                    String EMAIL;
                    assignString(EMAIL, SIZE(EMAIL), "EMAIL");
                    for (int i = 0; i < 5; i++) {
                        if (currentWord.TabWord[i] != EMAIL[i]) {
                            printAsRed("bukan email ID yang valid untuk dibaca.\n");
                            waitForEnter();
                            validEmailID = false;
                            break;
                        }  
                    }
                }

                if (validEmailID) {
                    for (int i = 5; i < 8; i++) {
                        if (!((0 <= currentWord.TabWord[i] - '0') && (currentWord.TabWord[i] - '0' <= 9))) {
                            printAsRed("bukan email ID yang valid untuk dibaca.\n");
                            waitForEnter();
                            validEmailID = false;
                            break;  
                        } 
                    }
                }

                if (validEmailID) {
                    int temp = ((currentWord.TabWord[5] - '0') * 100) + ((currentWord.TabWord[6] - '0') * 10) + (currentWord.TabWord[7] - '0');

                    int check;
                    for (check = 0; check < paginationLimit; check++) {
                        if (listEmailtoOpen[check] == temp) {
                            break;
                        }
                    }

                    if ((check == paginationLimit) || (temp == 0)) {
                        printAsRed("Tidak ada email tersebut pada page inbox saat ini.\n");
                        waitForEnter();
                    } else {
                        Email email = ELMT_EmailList(AllEmails, temp-1);
                        EmailDraft emailDraft;
                        createReplyEmail(email, &emailDraft);
                        if (error_code != 0) {
                            assignString(currentWord.TabWord, SIZE(currentWord.TabWord), "SEBELUM");
                            error_code = 0;
                            currentPage++;
                            system("clear");
                            continue;
                        }
                        while(true){
                            printf("Enkripsi email ini? (y/n)\n>> ");
                            STARTWORD();
                            HANDLE_EOP_ERROR();
                            if(error_code != 0){
                                continue;
                            }
                            if(isStringEqual(currentWord.TabWord, "y") || isStringEqual(currentWord.TabWord, "Y") || isStringEqual(currentWord.TabWord, "n") || isStringEqual(currentWord.TabWord, "N")){
                                if (isStringEqual(currentWord.TabWord, "y") || isStringEqual(currentWord.TabWord, "Y")) {
                                    encrypt(emailDraft.bodyDraft);
                                }
                                waitForEnter();
                                break;
                            } else{
                                printAsRed("bukan input yang valid!\n");
                                waitForEnter();
                                continue;
                            }
                        }
                        kirimDraftEmail(&AllEmails, &emailDraft);
                    }
                }
            } else {
                while (!EOP) {
                    ADVWORD();
                }
                printAsRed("input bukan input yang valid brow\n");
                waitForEnter();
            }
            
            getInbox();

            if (currentPage < 0) {
                if (!kosong) {
                    printAsRed("udah page awal jangan mundur lgi brow\n");
                    waitForEnter();
                } else {
                    printAsRed("inbox kamu kosong :(, gabisa pencet prev yaa\n");
                    waitForEnter();
                }
                currentPage = 0;
                system("clear");
            }

            if (currentPage > paginasi) {
                if (!kosong) {
                    printAsRed("udah page terakhir jangan maju lagi brow\n");
                    waitForEnter();
                } else {
                    printAsRed("inbox kamu kosong :(, gabisa pencet next yaa\n");
                    waitForEnter();
                }
                currentPage = paginasi;
                system("clear");
            }

            boolean cutSubject = false;
            if (longestSubject[currentPage] > 17) {
                longestSubject[currentPage] = 20;
                cutSubject = true;
            }

            boolean cutSender = false;
            if (longestSender[currentPage] > 17) {
                longestSender[currentPage] = 20;
                cutSender = true;
            }

            int panjangBaris = 59 + longestSubject[currentPage] + longestSender[currentPage];
            int banyakAngka = 0;
            int temp = NEFF_EmailList(inbox);

            while (temp > 0) {
                temp /= 10;
                banyakAngka++;
            }

            /* jumlah pesan pada list */
            if (!kosong) {        
                printf("\n[");
                for (int p = 0; p < (panjangBaris - (33 + banyakAngka)) / 2; p++) {
                    printf("-");
                }

                printf(" Anda memiliki %d pesan pada Inbox ", NEFF_EmailList(inbox));

                for (int p = 0; p < panjangBaris - (((panjangBaris - (33 + banyakAngka)) / 2) + (33 + banyakAngka)); p++) {
                    printf("-");
                }
                printf("]\n");
            }

            /* titel [Daftar list]*/
            printf("[");
            for (int p = 0; p < (panjangBaris - 16) / 2; p++) {
                printf("-");
            }

            printf("[ Daftar Inbox ]");

            for(int p = 0; p < panjangBaris - (((panjangBaris - 16) / 2) + 16); p++) {
                printf("-");
            }
            printf("]\n");

            /* garis */
            printf("[");
            for (int p = 0; p < panjangBaris; p++) {
                printf("-");
            }
            printf("]\n");
            
            if (kosong) {
                printf("|");
                for (int i = 0; i < (panjangBaris - 23) / 2; i++) {
                    printf(" ");
                }
            
                printf("Inbox anda masih kosong");

                for (int i = 0; i < panjangBaris - (((panjangBaris - 23) / 2) + 23); i++) {
                    printf(" ");
                }
                printf("|\n");
            } else {

                /* header tabel */
                printf("| Email ID");
                
                printf(" | Subject");
                for (int k = longestSubject[currentPage]; k > 7; k--) {
                    printf(" ");
                }

                printf(" | Pengirim");
                for (int k = longestSender[currentPage]; k > 8; k--) {
                    printf(" ");
                }

                printf(" | Status | Timestamp             | Starred |\n");

                /* body list */
                for (int j = 0; j < paginationLimit; j++) {
                    listEmailtoOpen[j] = 0;
                }

                for (int j = currentPage * paginationLimit; j < (currentPage + 1) * paginationLimit; j++) {
                    if (j == NEFF_EmailList(inbox)) {
                        break;
                    }

                    currentEmail = ELMT_EmailList(inbox, j);

                    int emailToOpenCounter = paginationLimit - ((currentPage + 1) * paginationLimit - j);
                    listEmailtoOpen[emailToOpenCounter] = ID_Email(currentEmail);

                    /* email id */
                    printf("| ");
                    String id;
                    createID(id, ID_Email(currentEmail));
                    printString(id);

                    /* subject */
                    printf(" | ");
                    if (cutSubject && stringLength(SUBJECT_Email(currentEmail)) > 17) {
                        for (int k = 0; k < 17; k ++) {
                            printf("%c", SUBJECT_Email(currentEmail)[k]);
                        }
                        printf("...");
                    } else {
                        printString(SUBJECT_Email(currentEmail));
                        for (int k = longestSubject[currentPage]; k > stringLength(SUBJECT_Email(currentEmail)); k--) {
                            printf(" ");
                        }
                    }

                    /* pengirim */
                    printf(" | ");
                    String currentSender;
                    assignString(currentSender, SIZE(currentSender), ELMT_UserList(users, FROM_Email(currentEmail)-1).userEmail);

                    if (cutSender && stringLength(currentSender) > 17) {
                        for (int k = 0; k < 17; k++) {
                            printf("%c", currentSender[k]);
                        }
                        printf("...");
                    } else {
                        printString(currentSender);
                        for (int k = longestSender[currentPage]; k > stringLength(currentSender); k--) {
                            printf(" ");
                        }
                    }

                    /* status */
                    printf(" | ");
                    String status;
                    if (ISREAD_Email(currentEmail)) {
                        assignString(status, SIZE(status), "READ");
                        printString(status);
                        printf("  ");
                    } else {
                        assignString(status, SIZE(status), "UNREAD");
                        printString(status);
                    }

                    /* timestamp */
                    printf(" | ");
                    displayDateTime(TIMESTAMP_Email(currentEmail));
                    printf(" | ");

                    /* starred */
                    String star;
                    User currentUser = ELMT_UserList(users, currentUserId - 1);

                    boolean starred = false;
                    for (int i = 0; i < NEFF_StarredList(STARREDLIST_User(currentUser)); i++) {
                        if (ID_Email(currentEmail) == ELMT_StarredList(STARREDLIST_User(currentUser), i)) {
                            starred = true;
                            break;
                        }
                    }

                    if (starred) {
                        assignString(star, SIZE(star), "Yes");
                        printString(star);
                        printf("     ");
                    } else {
                        assignString(star, SIZE(star), "No");
                        printString(star);
                        printf("      ");
                    }
                    printf("|\n");
                }
            }

            /* garis */
            printf("[");
            for (int p = 0; p < panjangBaris; p++) {
                printf("-");
            }
            printf("]\n");

            if (!kosong) {
                /* paginasi */
                printf("[");
                for (int p = 0; p < (panjangBaris - (30)) / 2; p++) {
                    printf("-");
                }
                
                int banyakAngkaKiri = 0;
                int banyakAngkaKanan = 0;

                temp = currentPage + 1;
                while (temp > 0) {
                    temp /= 10;
                    banyakAngkaKiri++;
                }

                temp = paginasi + 1;
                while (temp > 0) {
                    temp /= 10;
                    banyakAngkaKanan++;
                }

                for (int p = 0; p < (30 - (10 + banyakAngkaKiri + banyakAngkaKanan)) / 2; p++) {
                    printf(" ");
                }

                printf("Page [%d]/[%d]", currentPage + 1, paginasi + 1);

                for (int p = 0; p < 30 - (((30 - (10 + banyakAngkaKiri + banyakAngkaKanan)) / 2) + (10 + banyakAngkaKiri + banyakAngkaKanan)); p++) {
                    printf(" ");
                }

                for (int p = 0; p < panjangBaris - ((panjangBaris - 30)  / 2) - 30; p++) {
                    printf("-");
                }
                printf("]\n");

                /* garis */
                printf("[");
                for (int p = 0; p < panjangBaris; p++) {
                    printf("-");
                }
                printf("]\n");
            }
            printf("\npilihan input: LANJUT, SEBELUM, BACA_PESAN {EMAILID}, BALAS_PESAN {EMAILID}, STAR {EMAILID}, UNSTAR {EMAILID}, atau KELUAR\n");
            printf(">> ");
            STARTWORD();
        }
    } else {
        while (!EOP) {
            ADVWORD();
        }
        printAsRed("Setelah DAFTAR_INBOX jangan ada kata-kata lagi yaa!\n");
        waitForEnter();
    }
}

void displayStarred() {

    assignString(currentWord.TabWord, SIZE(currentWord.TabWord), "SEBELUM");
    if (EOP) {
        int listEmailtoOpen[paginationLimit];
        for (int j = 0; j < paginationLimit; j++) {
            listEmailtoOpen[j] = 0;
        }

        int currentPage = 1;
        while (true) {
            waitForEnter();

            getStarred();

            if (isStringEqual(currentWord.TabWord, "SEBELUM")) {
                if (EOP) {
                    currentPage--;
                } else {
                    while (!EOP) {
                        ADVWORD();
                    }
                    printAsRed("Setelah SEBELUM jangan ada kata-kata lagi yaa!\n");
                    waitForEnter();
                }
            } else if (isStringEqual(currentWord.TabWord, "LANJUT")) {
                if (EOP) {
                    currentPage++;
                } else {
                    while (!EOP) {
                        ADVWORD();
                    }
                    printAsRed("Setelah LANJUT jangan ada kata-kata lagi yaa!\n\n");
                    waitForEnter();
                }
            } else if (isStringEqual(currentWord.TabWord, "BACA_PESAN")) {
                
            /* skema baca_pesan */
                boolean validEmailID = true;
                ADVWORD();
                if (currentWord.Length != 8) {
                    printAsRed("bukan email ID yang valid untuk dibaca.\n");
                    waitForEnter();
                    validEmailID = false;
                } else {
                    String EMAIL;
                    assignString(EMAIL, SIZE(EMAIL), "EMAIL");
                    for (int i = 0; i < 5; i++) {
                        if (currentWord.TabWord[i] != EMAIL[i]) {
                            printAsRed("bukan email ID yang valid untuk dibaca.\n");
                            waitForEnter();
                            validEmailID = false;
                            break;
                        }  
                    }
                }

                if (validEmailID) {
                    for (int i = 5; i < 8; i++) {
                        if (!((0 <= currentWord.TabWord[i] - '0') && (currentWord.TabWord[i] - '0' <= 9))) {
                            printAsRed("bukan email ID yang valid untuk dibaca.\n");
                            waitForEnter();
                            validEmailID = false;
                            break;  
                        } 
                    }
                }

                if (validEmailID) {
                    int temp = ((currentWord.TabWord[5] - '0') * 100) + ((currentWord.TabWord[6] - '0') * 10) + (currentWord.TabWord[7] - '0');

                    int check;
                    for (check = 0; check < paginationLimit; check++) {
                        if (listEmailtoOpen[check] == temp) {
                            break;
                        }
                    }

                    if ((check == paginationLimit) || (temp == 0)) {
                        printAsRed("Tidak ada email tersebut pada page inbox saat ini.\n");
                        waitForEnter();
                    } else {
                        bacaPesan(temp, true, false);
                    }
                }
            } else if (isStringEqual(currentWord.TabWord, "KELUAR")) {
                if (EOP) {
                    printf("Anda telah keluar dari Starred.\n");
                    break;    
                } else {
                    while (!EOP) {
                        ADVWORD();
                    }
                    printAsRed("Setelah KELUAR jangan ada kata-kata lagi yaa!\n\n");
                    waitForEnter();
                }
            } else if (isStringEqual(currentWord.TabWord, "UNSTAR")) {
                
                /* skema star */
                boolean validEmailID = true;
                ADVWORD();
                if (currentWord.Length != 8) {
                    printAsRed("bukan email ID yang valid untuk di-unstar.\n");
                    waitForEnter();
                    validEmailID = false;
                } else {
                    String EMAIL;
                    assignString(EMAIL, SIZE(EMAIL), "EMAIL");
                    for (int i = 0; i < 5; i++) {
                        if (currentWord.TabWord[i] != EMAIL[i]) {
                            printAsRed("bukan email ID yang valid untuk di-unstar.\n");
                            waitForEnter();
                            validEmailID = false;
                            break;
                        }  
                    }
                }

                if (validEmailID) {
                    for (int i = 5; i < 8; i++) {
                        if (!((0 <= currentWord.TabWord[i] - '0') && (currentWord.TabWord[i] - '0' <= 9))) {
                            printAsRed("bukan email ID yang valid untuk di-unstar.\n");
                            waitForEnter();
                            validEmailID = false;
                            break;  
                        } 
                    }
                }

                if (validEmailID) {
                    int temp = ((currentWord.TabWord[5] - '0') * 100) + ((currentWord.TabWord[6] - '0') * 10) + (currentWord.TabWord[7] - '0');

                    int check;
                    for (check = 0; check < listLength_EmailList(starred); check++) {
                        if (ID_Email(ELMT_EmailList(starred, check)) == temp) {
                            break;
                        }
                    }

                    if (check == listLength_EmailList(starred)) {
                        printAsRed("User tidak memiliki email dengan ID tersebut untuk di-unstar.\n");
                        waitForEnter();
                    } else {
                        setAsUnstarred(temp);
                    }
                }
            } else if (isStringEqual(currentWord.TabWord, "BALAS_PESAN")) {
                
                /* skema balas_pesan */
                boolean validEmailID = true;
                ADVWORD();
                if (currentWord.Length != 8) {
                    printAsRed("bukan email ID yang valid untuk dibaca.\n");
                    waitForEnter();
                    validEmailID = false;
                } else {
                    String EMAIL;
                    assignString(EMAIL, SIZE(EMAIL), "EMAIL");
                    for (int i = 0; i < 5; i++) {
                        if (currentWord.TabWord[i] != EMAIL[i]) {
                            printAsRed("bukan email ID yang valid untuk dibaca.\n");
                            waitForEnter();
                            validEmailID = false;
                            break;
                        }  
                    }
                }

                if (validEmailID) {
                    for (int i = 5; i < 8; i++) {
                        if (!((0 <= currentWord.TabWord[i] - '0') && (currentWord.TabWord[i] - '0' <= 9))) {
                            printAsRed("bukan email ID yang valid untuk dibaca.\n");
                            waitForEnter();
                            validEmailID = false;
                            break;  
                        } 
                    }
                }

                if (validEmailID) {
                    int temp = ((currentWord.TabWord[5] - '0') * 100) + ((currentWord.TabWord[6] - '0') * 10) + (currentWord.TabWord[7] - '0');

                    int check;
                    for (check = 0; check < paginationLimit; check++) {
                        if (listEmailtoOpen[check] == temp) {
                            break;
                        }
                    }

                    if ((check == paginationLimit) || (temp == 0)) {
                        printAsRed("Tidak ada email tersebut pada page inbox saat ini.\n");
                        waitForEnter();
                    } else {
                        Email email = ELMT_EmailList(AllEmails, temp-1);
                        EmailDraft emailDraft;
                        createReplyEmail(email, &emailDraft);
                        if (error_code != 0) {
                            assignString(currentWord.TabWord, SIZE(currentWord.TabWord), "SEBELUM");
                            error_code = 0;
                            currentPage++;
                            continue;
                        }
                        kirimDraftEmail(&AllEmails, &emailDraft);
                    }
                }
    
            } else {
                while (!EOP) {
                    ADVWORD();
                }
                printAsRed("input bukan input yang valid brow\n");
                waitForEnter();
            }

            getStarred();

            int kosong = 0;
            if (NEFF_EmailList(starred) == 0) {
                kosong = 1;
            }
            
            int paginasi;
            if (!kosong) {
                paginasi = NEFF_EmailList(starred) / paginationLimit;
                if (NEFF_EmailList(starred) % paginationLimit == 0) {
                    paginasi--;
                }
            } else {
                paginasi = 0;
            }

            int longestSubject[paginasi + 1];
            int longestSender[paginasi + 1];
            Email currentEmail;
            String currentSender;

            for (int i = 0; i < paginasi + 1; i++) {
                longestSubject[i] = 7;
                longestSender[i] = 8;

                for (int j = i * paginationLimit; j < (i + 1) * paginationLimit; j++) {
                    if (j == NEFF_EmailList(starred)) {
                        break;
                    }

                    currentEmail = ELMT_EmailList(starred, j);

                    if (stringLength(SUBJECT_Email(currentEmail)) > longestSubject[i]) {
                        longestSubject[i] = stringLength(SUBJECT_Email(currentEmail));
                    }

                    int senderId = FROM_Email(currentEmail);
                    assignString(currentSender, SIZE(currentSender), ELMT_UserList(users, senderId-1).userEmail);

                    if (stringLength(currentSender) > longestSender[i]) {
                        longestSender[i] = stringLength(currentSender);
                    }
                }
            }

            if (currentPage < 0) {
                if (!kosong) {
                    printAsRed("udah page awal jangan mundur lgi brow\n");
                    waitForEnter();
                } else {
                    printAsRed("starred kamu kosong :(, gabisa pencet prev yaa\n");
                    waitForEnter();
                }
                currentPage = 0;
                system("clear");
            }

            if (currentPage > paginasi) {
                if (!kosong) {
                    printAsRed("udah page terakhir jangan maju lagi brow\n");
                    waitForEnter();
                } else {
                    printAsRed("starred kamu kosong :(, gabisa pencet next yaa\n");
                    waitForEnter();
                }
                currentPage = paginasi;
                system("clear");
            }

            boolean cutSubject = false;
            if (longestSubject[currentPage] > 17) {
                longestSubject[currentPage] = 20;
                cutSubject = true;
            }

            boolean cutSender = false;
            if (longestSender[currentPage] > 17) {
                longestSender[currentPage] = 20;
                cutSender = true;
            }

            int panjangBaris = 49 + longestSubject[currentPage] + longestSender[currentPage];
            int banyakAngka = 0;
            int temp = NEFF_EmailList(starred);

            while (temp > 0) {
                temp /= 10;
                banyakAngka++;
            }

            /* jumlah pesan pada list */
            if (!kosong) {        
                printf("\n[");
                for (int p = 0; p < (panjangBaris - (35 + banyakAngka)) / 2; p++) {
                    printf("-");
                }

                printf(" Anda memiliki %d pesan pada Starred ", NEFF_EmailList(starred));

                for (int p = 0; p < panjangBaris - (((panjangBaris - (35 + banyakAngka)) / 2) + (35 + banyakAngka)); p++) {
                    printf("-");
                }
                printf("]\n");
            }

            /* titel [Daftar list]*/
            printf("[");
            for (int p = 0; p < (panjangBaris - 18) / 2; p++) {
                printf("-");
            }

            printf("[ Daftar Starred ]");

            for(int p = 0; p < panjangBaris - (((panjangBaris - 18) / 2) + 18); p++) {
                printf("-");
            }
            printf("]\n");

            /* garis */
            printf("[");
            for (int p = 0; p < panjangBaris; p++) {
                printf("-");
            }
            printf("]\n");
            
            if (kosong) {
                printf("|");
                for (int i = 0; i < (panjangBaris - 25) / 2; i++) {
                    printf(" ");
                }
            
                printf("Starred anda masih kosong");

                for (int i = 0; i < panjangBaris - (((panjangBaris - 25) / 2) + 25); i++) {
                    printf(" ");
                }
                printf("|\n");
            } else {

                /* header tabel */
                printf("| Email ID");
                
                printf(" | Subject");
                for (int k = longestSubject[currentPage]; k > 7; k--) {
                    printf(" ");
                }

                printf(" | Pengirim");
                for (int k = longestSender[currentPage]; k > 8; k--) {
                    printf(" ");
                }

                printf(" | Status | Timestamp             |\n");

                /* body list */
                for (int j = 0; j < paginationLimit; j++) {
                    listEmailtoOpen[j] = 0;
                }

                for (int j = currentPage * paginationLimit; j < (currentPage + 1) * paginationLimit; j++) {
                    if (j == NEFF_EmailList(starred)) {
                        break;
                    }

                    currentEmail = ELMT_EmailList(starred, j);

                    int emailToOpenCounter = paginationLimit - ((currentPage + 1) * paginationLimit - j);
                    listEmailtoOpen[emailToOpenCounter] = ID_Email(currentEmail);

                    /* email id */
                    printf("| ");
                    String id;
                    createID(id, ID_Email(currentEmail));
                    printString(id);

                    /* subject */
                    printf(" | ");
                    if (cutSubject && stringLength(SUBJECT_Email(currentEmail)) > 17) {
                        for (int k = 0; k < 17; k ++) {
                            printf("%c", SUBJECT_Email(currentEmail)[k]);
                        }
                        printf("...");
                    } else {
                        printString(SUBJECT_Email(currentEmail));
                        for (int k = longestSubject[currentPage]; k > stringLength(SUBJECT_Email(currentEmail)); k--) {
                            printf(" ");
                        }
                    }
                    
                    /* pengirim */
                    printf(" | ");

                    String currentSender;
                    assignString(currentSender, SIZE(currentSender), ELMT_UserList(users, FROM_Email(currentEmail)-1).userEmail);

                    if (cutSender && stringLength(currentSender) > 17) {
                        for (int k = 0; k < 17; k++) {
                            printf("%c", currentSender[k]);
                        }
                        printf("...");
                    } else {
                        printString(currentSender);
                        for (int k = longestSender[currentPage]; k > stringLength(currentSender); k--) {
                            printf(" ");
                        }
                    }

                    /* status */
                    printf(" | ");
                    if (ISREAD_Email(currentEmail)) {
                        printString("READ");
                        printf("  ");
                    } else {
                        printString("UNREAD");
                    }

                    /* timestamp */
                    printf(" | ");
                    displayDateTime(TIMESTAMP_Email(currentEmail));
                    printf(" |\n");
                }
            }

            /* garis */
            printf("[");
            for (int p = 0; p < panjangBaris; p++) {
                printf("-");
            }
            printf("]\n");

            if (!kosong) {
                /* paginasi */
                printf("[");
                for (int p = 0; p < (panjangBaris - (30)) / 2; p++) {
                    printf("-");
                }
                
                int banyakAngkaKiri = 0;
                int banyakAngkaKanan = 0;

                temp = currentPage + 1;
                while (temp > 0) {
                    temp /= 10;
                    banyakAngkaKiri++;
                }

                temp = paginasi + 1;
                while (temp > 0) {
                    temp /= 10;
                    banyakAngkaKanan++;
                }

                for (int p = 0; p < (30 - (10 + banyakAngkaKiri + banyakAngkaKanan)) / 2; p++) {
                    printf(" ");
                }

                printf("Page [%d]/[%d]", currentPage + 1, paginasi + 1);

                for (int p = 0; p < 30 - (((30 - (10 + banyakAngkaKiri + banyakAngkaKanan)) / 2) + (10 + banyakAngkaKiri + banyakAngkaKanan)); p++) {
                    printf(" ");
                }

                for (int p = 0; p < panjangBaris - ((panjangBaris - 30)  / 2) - 30; p++) {
                    printf("-");
                }
                printf("]\n");

                /* garis */
                printf("[");
                for (int p = 0; p < panjangBaris; p++) {
                    printf("-");
                }
                printf("]\n");
            }

            printf("\npilihan input: LANJUT, SEBELUM, BACA_PESAN {EMAILID}, BALAS_PESAN {EMAILID}, UNSTAR {EMAILID}, atau KELUAR\n");
            printf(">> ");
            STARTWORD();
        }
    } else {
        while (!EOP) {
            ADVWORD();
        }
        printAsRed("Setelah DAFTAR_STARRED jangan ada kata-kata lagi yaa!\n");
        waitForEnter();
    }
}

void displaySearchResult(char* keyword) {

    if (EOP) {
        String tempKeyword;
        assignString(tempKeyword, SIZE(tempKeyword), keyword);
        getSearchEmails(tempKeyword);
        printf("Search result for keyword: %s\n", tempKeyword);

        int kosong = 0;
        if (NEFF_EmailList(searchResult) == 0) {
            kosong = 1;
        }
        
        int paginasi;
        if (!kosong) {
            paginasi = NEFF_EmailList(searchResult) / paginationLimit;
            if (NEFF_EmailList(searchResult) % paginationLimit == 0) {
                paginasi--;
            }
        } else {
            paginasi = 0;
        }

        int longestSubject[paginasi + 1];
        int longestSender[paginasi + 1];
        Email currentEmail;
        String currentSender;
        for (int i = 0; i < paginasi + 1; i++) {
            longestSubject[i] = 7;
            longestSender[i] = 8;

            for (int j = i * paginationLimit; j < (i + 1) * paginationLimit; j++) {
                if (j == NEFF_EmailList(searchResult)) {
                    break;
                }

                currentEmail = ELMT_EmailList(searchResult, j);

                if (stringLength(SUBJECT_Email(currentEmail)) > longestSubject[i]) {
                    longestSubject[i] = stringLength(SUBJECT_Email(currentEmail));
                }
            
                int senderId = FROM_Email(currentEmail);
                assignString(currentSender, SIZE(currentSender), ELMT_UserList(users, senderId-1).userEmail);

                if (stringLength(currentSender) > longestSender[i]) {
                    longestSender[i] = stringLength(currentSender);
                }
            }
        }

        int listEmailtoOpen[paginationLimit];
        for (int j = 0; j < paginationLimit; j++) {
            listEmailtoOpen[j] = 0;
        }
        assignString(currentWord.TabWord, SIZE(currentWord.TabWord), "SEBELUM");
        int currentPage = 1;
        system("clear");
        while (true) {
            if (isStringEqual(currentWord.TabWord, "SEBELUM")) {
                if (EOP) {
                    currentPage--;
                } else {
                    while (!EOP) {
                        ADVWORD();
                    }
                    printAsRed("Setelah SEBELUM jangan ada kata-kata lagi yaa\n!");
                    waitForEnter();
                }
            } else if (isStringEqual(currentWord.TabWord, "LANJUT")) {
                if (EOP) {
                    currentPage++;
                } else {
                    while (!EOP) {
                        ADVWORD();
                    }
                    printAsRed("Setelah LANJUT jangan ada kata-kata lagi yaa\n!");
                    waitForEnter();
                }
            } else if (isStringEqual(currentWord.TabWord, "BACA_PESAN")) {
                
                /* skema baca_pesan */
                boolean validEmailID = true;
                ADVWORD();
                if (currentWord.Length != 8) {
                    printAsRed("bukan email ID yang valid untuk dibaca.\n");
                    waitForEnter();
                    validEmailID = false;
                } else {
                    String EMAIL;
                    assignString(EMAIL, SIZE(EMAIL), "EMAIL");
                    for (int i = 0; i < 5; i++) {
                        if (currentWord.TabWord[i] != EMAIL[i]) {
                            printAsRed("bukan email ID yang valid untuk dibaca.\n");
                            waitForEnter();
                            validEmailID = false;
                            break;
                        }  
                    }
                }

                if (validEmailID) {
                    for (int i = 5; i < 8; i++) {
                        if (!((0 <= currentWord.TabWord[i] - '0') && (currentWord.TabWord[i] - '0' <= 9))) {
                            printAsRed("bukan email ID yang valid untuk dibaca.\n");
                            waitForEnter();
                            validEmailID = false;
                            break;  
                        } 
                    }
                }

                if (validEmailID) {
                    int temp = ((currentWord.TabWord[5] - '0') * 100) + ((currentWord.TabWord[6] - '0') * 10) + (currentWord.TabWord[7] - '0');

                    int check;
                    for (check = 0; check < paginationLimit; check++) {
                        if (listEmailtoOpen[check] == temp) {
                            break;
                        }
                    }

                    if ((check == paginationLimit) || (temp == 0)) {
                        printAsRed("Tidak ada email tersebut pada page inbox saat ini.\n");
                        waitForEnter();
                    } else {
                        bacaPesan(temp, true, false);
                    }
                }
            } else if (isStringEqual(currentWord.TabWord, "KELUAR")) {
                if (EOP) {
                    printf("Anda telah keluar dari pencarian.\n");
                    break;      
                } else {
                    while (!EOP) {
                        ADVWORD();
                    }
                    printAsRed("Setelah KELUAR jangan ada kata-kata lagi yaa\n!");
                    waitForEnter();
                }      
            } else if (isStringEqual(currentWord.TabWord, "STAR")) {
                
                /* skema star */
                boolean validEmailID = true;
                ADVWORD();
                if (currentWord.Length != 8) {
                    printAsRed("bukan email ID yang valid untuk di-star.\n");
                    waitForEnter();
                    validEmailID = false;
                } else {
                    String EMAIL;
                    assignString(EMAIL, SIZE(EMAIL), "EMAIL");
                    for (int i = 0; i < 5; i++) {
                        if (currentWord.TabWord[i] != EMAIL[i]) {
                            printAsRed("bukan email ID yang valid untuk di-star.\n");
                            waitForEnter();
                            validEmailID = false;
                            break;
                        }  
                    }
                }

                if (validEmailID) {
                    for (int i = 5; i < 8; i++) {
                        if (!((0 <= currentWord.TabWord[i] - '0') && (currentWord.TabWord[i] - '0' <= 9))) {
                            printAsRed("bukan email ID yang valid untuk di-star.\n");
                            waitForEnter();
                            validEmailID = false;
                            break;  
                        } 
                    }
                }

                if (validEmailID) {
                    int temp = ((currentWord.TabWord[5] - '0') * 100) + ((currentWord.TabWord[6] - '0') * 10) + (currentWord.TabWord[7] - '0');

                    int check;
                    for (check = 0; check < listLength_EmailList(searchResult); check++) {
                        if (ID_Email(ELMT_EmailList(searchResult, check)) == temp) {
                            break;
                        }
                    }

                    if (check == listLength_EmailList(searchResult)) {
                        printAsRed("User tidak memiliki email dengan ID tersebut untuk di-star.\n");
                        waitForEnter();
                    } else {
                        setAsStarred(temp);
                    }
                }
            } else if (isStringEqual(currentWord.TabWord, "UNSTAR")) {
                
                /* skema star */
                boolean validEmailID = true;
                ADVWORD();
                if (currentWord.Length != 8) {
                    printAsRed("bukan email ID yang valid untuk di-unstar.\n");
                    waitForEnter();
                    validEmailID = false;
                } else {
                    String EMAIL;
                    assignString(EMAIL, SIZE(EMAIL), "EMAIL");
                    for (int i = 0; i < 5; i++) {
                        if (currentWord.TabWord[i] != EMAIL[i]) {
                            printAsRed("bukan email ID yang valid untuk di-unstar.\n");
                            waitForEnter();
                            validEmailID = false;
                            break;
                        }  
                    }
                }

                if (validEmailID) {
                    for (int i = 5; i < 8; i++) {
                        if (!((0 <= currentWord.TabWord[i] - '0') && (currentWord.TabWord[i] - '0' <= 9))) {
                            printAsRed("bukan email ID yang valid untuk di-unstar.\n");
                            waitForEnter();
                            validEmailID = false;
                            break;  
                        } 
                    }
                }

                if (validEmailID) {
                    int temp = ((currentWord.TabWord[5] - '0') * 100) + ((currentWord.TabWord[6] - '0') * 10) + (currentWord.TabWord[7] - '0');

                    int check;
                    for (check = 0; check < listLength_EmailList(searchResult); check++) {
                        if (ID_Email(ELMT_EmailList(searchResult, check)) == temp) {
                            break;
                        }
                    }

                    if (check == listLength_EmailList(searchResult)) {
                        printAsRed("User tidak memiliki email dengan ID tersebut untuk di-unstar.\n");
                        waitForEnter();
                    } else {
                        setAsUnstarred(temp);
                    }
                }
            } else if (isStringEqual(currentWord.TabWord, "BALAS_PESAN")) {
                
                /* skema balas_pesan */
                boolean validEmailID = true;
                ADVWORD();
                if (currentWord.Length != 8) {
                    printAsRed("bukan email ID yang valid untuk dibaca.\n");
                    waitForEnter();
                    validEmailID = false;
                } else {
                    String EMAIL;
                    assignString(EMAIL, SIZE(EMAIL), "EMAIL");
                    for (int i = 0; i < 5; i++) {
                        if (currentWord.TabWord[i] != EMAIL[i]) {
                            printAsRed("bukan email ID yang valid untuk dibaca.\n");
                            waitForEnter();
                            validEmailID = false;
                            break;
                        }  
                    }
                }

                if (validEmailID) {
                    for (int i = 5; i < 8; i++) {
                        if (!((0 <= currentWord.TabWord[i] - '0') && (currentWord.TabWord[i] - '0' <= 9))) {
                            printAsRed("bukan email ID yang valid untuk dibaca.\n");
                            waitForEnter();
                            validEmailID = false;
                            break;  
                        } 
                    }
                }

                if (validEmailID) {
                    int temp = ((currentWord.TabWord[5] - '0') * 100) + ((currentWord.TabWord[6] - '0') * 10) + (currentWord.TabWord[7] - '0');

                    int check;
                    for (check = 0; check < paginationLimit; check++) {
                        if (listEmailtoOpen[check] == temp) {
                            break;
                        }
                    }

                    if ((check == paginationLimit) || (temp == 0)) {
                        printAsRed("Tidak ada email tersebut pada page inbox saat ini.\n");
                        waitForEnter();
                    } else {
                        Email email = ELMT_EmailList(AllEmails, temp-1);
                        EmailDraft emailDraft;
                        createReplyEmail(email, &emailDraft);
                        if (error_code != 0) {
                            assignString(currentWord.TabWord, SIZE(currentWord.TabWord), "SEBELUM");
                            error_code = 0;
                            currentPage++;
                            continue;
                        }
                        while(true){
                            printf("Enkripsi email ini? (y/n)\n>> ");
                            STARTWORD();
                            HANDLE_EOP_ERROR();
                            if(error_code != 0){
                                continue;
                            }
                            if(isStringEqual(currentWord.TabWord, "y") || isStringEqual(currentWord.TabWord, "Y") || isStringEqual(currentWord.TabWord, "n") || isStringEqual(currentWord.TabWord, "N")){
                                if (isStringEqual(currentWord.TabWord, "y") || isStringEqual(currentWord.TabWord, "Y")) {
                                    encrypt(emailDraft.bodyDraft);
                                    break;
                                } else break;
                            } else{
                                printAsRed("bukan input yang valid!\n");
                                waitForEnter();
                                continue;
                            }
                        }
                        kirimDraftEmail(&AllEmails, &emailDraft);
                    }
                }
            } else {
                while (!EOP) {
                    ADVWORD();
                }
                printAsRed("input bukan input yang valid brow\n");
                waitForEnter();
            }
            
            
            getSearchEmails(tempKeyword);

            if (currentPage < 0) {
                if (!kosong) {
                    printAsRed("udah page awal jangan mundur lgi brow\n");
                    waitForEnter();
                } else {
                    printAsRed("Hasil pencarian kamu kosong :(, gabisa pencet prev yaa\n");
                    waitForEnter();
                }
                currentPage = 0;
                system("clear");
            }

            if (currentPage > paginasi) {
                if (!kosong) {
                    printAsRed("udah page terakhir jangan maju lagi brow\n");
                    waitForEnter();
                } else {
                    printAsRed("Hasil pencarian kamu kosong :(, gabisa pencet next yaa\n");
                    waitForEnter();
                }
                currentPage = paginasi;
                system("clear");
            }

            boolean cutSubject = false;
            if (longestSubject[currentPage] > 17) {
                longestSubject[currentPage] = 20;
                cutSubject = true;
            }

            boolean cutSender = false;
            if (longestSender[currentPage] > 17) {
                longestSender[currentPage] = 20;
                cutSender = true;
            }

            int panjangBaris = 59 + longestSubject[currentPage] + longestSender[currentPage];
            int banyakAngka = 0;
            int temp = NEFF_EmailList(searchResult);

            while (temp > 0) {
                temp /= 10;
                banyakAngka++;
            }
            if(banyakAngka == 0) {
                banyakAngka = 1;
            }
            int banyakHuruf = stringLength(tempKeyword);

            /* jumlah pesan pada list */
             
            printf("\n[");
            for (int p = 0; p < (panjangBaris - (35 + banyakAngka + banyakHuruf)) / 2; p++) {
                printf("-");
            }

            printf(" Anda memiliki %d pesan dengan kata %s ", NEFF_EmailList(searchResult), tempKeyword);

            for (int p = 0; p < panjangBaris - (((panjangBaris - (35 + banyakAngka + banyakHuruf)) / 2) + (35 + banyakAngka + banyakHuruf)); p++) {
                printf("-");
            }
            printf("]\n");
        

            /* titel [Daftar list]*/
            printf("[");
            for (int p = 0; p < (panjangBaris - 16) / 2; p++) {
                printf("-");
            }

            printf("[ Daftar Pesan ]");

            for(int p = 0; p < panjangBaris - (((panjangBaris - 16) / 2) + 16); p++) {
                printf("-");
            }
            printf("]\n");

            /* garis */
            printf("[");
            for (int p = 0; p < panjangBaris; p++) {
                printf("-");
            }
            printf("]\n");
            
            if (kosong) {
                printf("|");
                for (int i = 0; i < (panjangBaris - 27) / 2; i++) {
                    printf(" ");
                }
            
                printf("Tidak ada pesan yang sesuai");

                for (int i = 0; i < panjangBaris - (((panjangBaris - 27) / 2) + 27); i++) {
                    printf(" ");
                }
                printf("|\n");
            } else {

                /* header tabel */
                printf("| Email ID");
                
                printf(" | Subject");
                for (int k = longestSubject[currentPage]; k > 7; k--) {
                    printf(" ");
                }

                printf(" | Pengirim");
                for (int k = longestSender[currentPage]; k > 8; k--) {
                    printf(" ");
                }

                printf(" | Status | Timestamp             | Starred |\n");

                /* body list */
                for (int j = 0; j < paginationLimit; j++) {
                    listEmailtoOpen[j] = 0;
                }

                for (int j = currentPage * paginationLimit; j < (currentPage + 1) * paginationLimit; j++) {
                    if (j == NEFF_EmailList(searchResult)) {
                        break;
                    }

                    currentEmail = ELMT_EmailList(searchResult, j);

                    int emailToOpenCounter = paginationLimit - ((currentPage + 1) * paginationLimit - j);
                    listEmailtoOpen[emailToOpenCounter] = ID_Email(currentEmail);

                    /* email id */
                    printf("| ");
                    String id;
                    createID(id, ID_Email(currentEmail));
                    printString(id);

                    /* subject */
                    printf(" | ");
                    if (cutSubject && stringLength(SUBJECT_Email(currentEmail)) > 17) {
                        for (int k = 0; k < 17; k ++) {
                            printf("%c", SUBJECT_Email(currentEmail)[k]);
                        }
                        printf("...");
                    } else {
                        printString(SUBJECT_Email(currentEmail));
                        for (int k = longestSubject[currentPage]; k > stringLength(SUBJECT_Email(currentEmail)); k--) {
                            printf(" ");
                        }
                    }

                    /* pengirim */
                    printf(" | ");
                    String currentSender;
                    assignString(currentSender, SIZE(currentSender), ELMT_UserList(users, FROM_Email(currentEmail)-1).userEmail);

                    if (cutSender && stringLength(currentSender) > 17) {
                        for (int k = 0; k < 17; k++) {
                            printf("%c", currentSender[k]);
                        }
                        printf("...");
                    } else {
                        printString(currentSender);
                        for (int k = longestSender[currentPage]; k > stringLength(currentSender); k--) {
                            printf(" ");
                        }
                    }

                    /* status */
                    printf(" | ");
                    String status;
                    if (ISREAD_Email(currentEmail)) {
                        assignString(status, SIZE(status), "READ");
                        printString(status);
                        printf("  ");
                    } else {
                        assignString(status, SIZE(status), "UNREAD");
                        printString(status);
                    }

                    /* timestamp */
                    printf(" | ");
                    displayDateTime(TIMESTAMP_Email(currentEmail));
                    printf(" | ");

                    /* starred */
                    String star;
                    User currentUser = ELMT_UserList(users, currentUserId - 1);

                    boolean starred = false;
                    for (int i = 0; i < NEFF_StarredList(STARREDLIST_User(currentUser)); i++) {
                        if (ID_Email(currentEmail) == ELMT_StarredList(STARREDLIST_User(currentUser), i)) {
                            starred = true;
                            break;
                        }
                    }

                    if (starred) {
                        assignString(star, SIZE(star), "Yes");
                        printString(star);
                        printf("     ");
                    } else {
                        assignString(star, SIZE(star), "No");
                        printString(star);
                        printf("      ");
                    }
                    printf("|\n");
                }
            }

            /* garis */
            printf("[");
            for (int p = 0; p < panjangBaris; p++) {
                printf("-");
            }
            printf("]\n");

            if (!kosong) {
                /* paginasi */
                printf("[");
                for (int p = 0; p < (panjangBaris - (30)) / 2; p++) {
                    printf("-");
                }
                
                int banyakAngkaKiri = 0;
                int banyakAngkaKanan = 0;

                temp = currentPage + 1;
                while (temp > 0) {
                    temp /= 10;
                    banyakAngkaKiri++;
                }

                temp = paginasi + 1;
                while (temp > 0) {
                    temp /= 10;
                    banyakAngkaKanan++;
                }

                for (int p = 0; p < (30 - (10 + banyakAngkaKiri + banyakAngkaKanan)) / 2; p++) {
                    printf(" ");
                }

                printf("Page [%d]/[%d]", currentPage + 1, paginasi + 1);

                for (int p = 0; p < 30 - (((30 - (10 + banyakAngkaKiri + banyakAngkaKanan)) / 2) + (10 + banyakAngkaKiri + banyakAngkaKanan)); p++) {
                    printf(" ");
                }

                for (int p = 0; p < panjangBaris - ((panjangBaris - 30)  / 2) - 30; p++) {
                    printf("-");
                }
                printf("]\n");

                /* garis */
                printf("[");
                for (int p = 0; p < panjangBaris; p++) {
                    printf("-");
                }
                printf("]\n");
            }
            printf("\npilihan input: LANJUT, SEBELUM, BACA_PESAN {EMAILID}, BALAS_PESAN {EMAILID}, STAR {EMAILID}, UNSTAR {EMAILID}, atau KELUAR\n");
            printf(">> ");
            STARTWORD();
        }
    } else {
        while (!EOP) {
            ADVWORD();
        }
        printAsRed("Setelah CARI_PESAN [subkata] jangan ada kata-kata lagi yaa!\n");
        waitForEnter();
    }
}

void bacaPesan(int id, boolean header, boolean dekripsi) {

    if (EOP) {
        int panjangBaris = 69;
        Email email = ELMT_EmailList(AllEmails, id-1);
        int parent = REPLY_Email(email);
        String stringDekripsi;
        if (dekripsi) {
            assignString(stringDekripsi, SIZE(stringDekripsi), "DEKRIPSI");
        } else {
            assignString(stringDekripsi, SIZE(stringDekripsi), "-");
        }
        boolean validEmailID;


        int k;
        for (k = 0; k < listLength_EmailList(AllEmails); k++) {
            if (id == ID_Email(ELMT_EmailList(AllEmails, k))) {
                break;
            }
        }

        if (header) {
            if (TO_Email(ELMT_EmailList(AllEmails, k)) == currentUserId) {
                ISREAD_Email(ELMT_EmailList(AllEmails, k)) = true;
            }

            if (CC_Email(ELMT_EmailList(AllEmails, k)) == currentUserId) {
                CCREAD_Email(ELMT_EmailList(AllEmails, k)) = true;
            }

            validEmailID = true;
            while (!isStringEqual(currentWord.TabWord, "KEMBALI")) {

                if (error_code != 0) {
                    print_error();
                    error_code = 0;
                }
                waitForEnter();

                if (dekripsi && isStringEqual(stringDekripsi, "DEKRIPSI") && validEmailID) {
                    decrypt(BODY_Email(email));
                    EOP = true;
                    if (error_code != 0) {
                        continue;
                    }
                }

                /* judul [ Baca Pesan ]*/
                printf("\n[");
                for (int i = 0; i < (panjangBaris - 14) / 2; i++) {
                    printf("-");
                }
                printf("[ Baca Pesan ]");
                for (int i = 0; i < panjangBaris - (((panjangBaris - 14) / 2) + 14); i++) {
                    printf("-");
                }
                printf("]\n");

                /* inbox id */
                printf("| Inbox ID: ");

                String idStr;
                createID(idStr, ID_Email(email));
                printString(idStr);
                for (int i = 0; i < (panjangBaris - 11 - stringLength(idStr)); i++) {
                    printf(" ");
                }
                printf("|\n");

                /* subject */
                printf("| Subject: ");
                printString(SUBJECT_Email(email));
                for (int i = 0; i < (panjangBaris - 10 - stringLength(SUBJECT_Email(email))); i++) {
                    printf(" ");
                }
                printf("|\n");

                /* pengirim */
                printf("| Pengirim: ");
                printString(ELMT_UserList(users, FROM_Email(email)-1).userEmail);
                for (int i = 0; i < (panjangBaris - 11 - stringLength(ELMT_UserList(users, FROM_Email(email)-1).userEmail)); i++) {
                    printf(" ");
                }
                printf("|\n");

                /* CC */
                if (CC_Email(email) != -1) {
                    printf("| Cc: ");
                    String ccEmail;
                    if (CC_Email(email) != -1) {
                        assignString(ccEmail, SIZE(ccEmail), "-");
                    } else {
                        assignString(ccEmail, SIZE(ccEmail), ELMT_UserList(users, CC_Email(email)-1).userEmail);
                    }
                    printString(ccEmail);

                    for (int i = 0; i < (panjangBaris - 5 - stringLength(ccEmail)); i++) {
                        printf(" ");
                    }
                    printf("|\n");
                }

                /* timestamp */
                printf("| Timestamp: ");
                displayDateTime(TIMESTAMP_Email(email));
                String timestamper;
                setDateTimeasStringInbox(timestamper, TIMESTAMP_Email(email));
                for (int i = 0; i < (panjangBaris - 12 - stringLength(timestamper)); i++) {
                    printf(" ");
                }
                printf("|\n");

                /* garis penutup */
                printf("[");
                for (int i = 0; i < panjangBaris; i++) {
                    printf("-");
                }
                printf("]\n\n");
                
                if (parent != -1) {
                    EOP = true;
                    bacaPesan(parent, false, false);
                }
        
                /* garis pembuka */
                printf("[");
                for (int i = 0; i < panjangBaris; i++) {
                    printf("-");
                }
                printf("]\n");

                /* body */
                int panjangBody = stringLength(BODY_Email(email));
                int startLetter = 0;
                int currentLetter = 69;
                
                boolean under = true;
                while (under) {
                    int offset = 0;
                    if (currentLetter < panjangBody) {
                        while (BODY_Email(email)[currentLetter] != ' ') {
                            currentLetter--;
                            offset++;
                        }
                    } else {
                        currentLetter = panjangBody;
                        under = false;
                    }

                    boolean cut = false;
                    printf(" ");
                    for (int i = startLetter; i < currentLetter; i++) {
                        if (BODY_Email(email)[i] == '\\') {
                            cut = true;
                            startLetter = i + 1;
                            break;
                        }
                        printf("%c", BODY_Email(email)[i]);
                    }
                    printf(" \n");

                    if (!cut) {
                        startLetter = currentLetter + 1;
                    }

                    currentLetter = startLetter + 69;
                }

                /* garis penutup */
                printf("[");
                for (int i = 0; i < panjangBaris; i++) {
                    printf("-");
                }
                printf("]\n\n");

                printf("pilihan input: KEMBALI, DEKRIPSI {EMAILID}\n");
                printf(">> ");
                STARTWORD();
                
                if (isStringEqual(currentWord.TabWord, "DEKRIPSI")) {
                    /* skema star */
                    validEmailID = true;
                    // printf("isi stringDekripsi: ");
                    // printString(stringDekripsi);
                    // printf("\n");

                    if (validEmailID) {
                        ADVWORD();
                        if (currentWord.Length != 8) {
                            printAsRed("bukan email ID yang valid untuk didekripsi.\n");
                            waitForEnter();
                            validEmailID = false;
                        } else {
                            String EMAIL;
                            assignString(EMAIL, SIZE(EMAIL), "EMAIL");
                            for (int i = 0; i < 5; i++) {
                                if (currentWord.TabWord[i] != EMAIL[i]) {
                                    printAsRed("bukan email ID yang valid untuk didekripsi.\n");
                                    waitForEnter();
                                    validEmailID = false;
                                    break;
                                }  
                            }
                        }
                    }

                    if (validEmailID) {
                        for (int i = 5; i < 8; i++) {
                            if (!((0 <= currentWord.TabWord[i] - '0') && (currentWord.TabWord[i] - '0' <= 9))) {
                                printAsRed("bukan email ID yang valid untuk dekripsi.\n");
                                waitForEnter();
                                validEmailID = false;
                                break;  
                            } 
                        }
                    }

                    if (validEmailID) {
                        int temp = ((currentWord.TabWord[5] - '0') * 100) + ((currentWord.TabWord[6] - '0') * 10) + (currentWord.TabWord[7] - '0');
                        if (temp != id) {
                            printAsRed("User sedang tidak membaca email dengan id tersebut, dekripsi hanya dapat dilakukan pada email yang sedang dibaca.\n");
                            waitForEnter();
                            validEmailID = false;
                        } else {
                            if (isStringEqual(stringDekripsi, "DEKRIPSI")) {
                                printAsRed("Anda sedang membuka email ini dan isi email telah di-dekripsi.\n");
                                waitForEnter();
                                while (!EOP) {
                                    ADVWORD();
                                }
                                validEmailID = false;
                            }
                        }

                    if (validEmailID) {
                        if (isStringEqual(stringDekripsi, "-")) {
                            assignString(stringDekripsi, SIZE(stringDekripsi), "DEKRIPSI");
                        }
                        bacaPesan(id, true, true);
                        }
                    } 
                } else if (!isStringEqual(currentWord.TabWord, "KEMBALI")) {
                    while (!EOP) {
                        ADVWORD();
                    }
                    printAsRed("Bukan input yang valid brow.\n");
                    waitForEnter();
                }
                else if(isStringEqual(currentWord.TabWord, "KEMBALI")){
                    HANDLE_EOP_ERROR();
                    if(error_code != 0){
                        continue;
                    }
                    system("clear");
                }
            }
        } else {
            if (parent != -1) {
                bacaPesan(parent, false, false);
            }

            /* judul subject */
            printf("[");
            printString(SUBJECT_Email(email));
            printf("]");
            for (int i = 0; i < (panjangBaris - 2 - stringLength(SUBJECT_Email(email))); i++) {
                printf(" ");
            }
            printf("\n");
            
            /* garis pembuka */
            printf("[");
            for (int i = 0; i < panjangBaris; i++) {
                printf("-");
            }
            printf("]\n");

            /* body */
                int panjangBody = stringLength(BODY_Email(email));
                int startLetter = 0;
                int currentLetter = 69;
                
                boolean under = true;
                while (under) {
                    int offset = 0;
                    if (currentLetter < panjangBody) {
                        while (BODY_Email(email)[currentLetter] != ' ') {
                            currentLetter--;
                            offset++;
                        }
                    } else {
                        currentLetter = panjangBody;
                        under = false;
                    }

                    boolean cut = false;
                    printf(" ");
                    for (int i = startLetter; i < currentLetter; i++) {
                        if (BODY_Email(email)[i] == '\\') {
                            cut = true;
                            startLetter = i + 1;
                            break;
                        }
                        printf("%c", BODY_Email(email)[i]);
                    }
                    printf(" \n");

                    if (!cut) {
                        startLetter = currentLetter + 1;
                    }

                    currentLetter = startLetter + 69;
                }

            /* garis penutup */
            printf("[");
            for (int i = 0; i < panjangBaris; i++) {
                printf("-");
            }
            printf("]\n\n");
        }
    } else {
        while (!EOP) {
            ADVWORD();
        }
        printAsRed("Setelah id email jangan ada kata-kata lagi yaa!\n");
        waitForEnter();
    }
}

void setAsStarred(int id) {

    if (EOP) {
        int pointer;
        for (pointer = 0; pointer < listLength_UserList(users); pointer++) {
            if (ID_User(ELMT_UserList(users, pointer)) == currentUserId) {
                break;
            }
        }
        
        int idx;
        for (idx = 0; idx < NEFF_StarredList(STARREDLIST_User(ELMT_UserList(users, pointer))); idx++) {
            if (ELMT_StarredList(STARREDLIST_User(ELMT_UserList(users, pointer)), idx) == id) {
                break;
            }
        }

        // printf("sebelum: ");
        // for (int i = 0; i < NEFF_StarredList(STARREDLIST_User(ELMT_UserList(users, pointer))); i++) {
        //     printf("%d,", ELMT_StarredList(STARREDLIST_User(ELMT_UserList(users, pointer)), i));
        // }
        // printf("\n");

        if (idx == NEFF_StarredList(STARREDLIST_User(ELMT_UserList(users, pointer)))) {
            StarredList temp;
            createStarredList(&temp, NEFF_StarredList(STARREDLIST_User(ELMT_UserList(users, pointer))) + 1);
            NEFF_StarredList(temp) = CAPACITY_StarredList(temp);

            for (int i = 0; i < NEFF_StarredList(STARREDLIST_User(ELMT_UserList(users, pointer))); i++) {
                ELMT_StarredList(temp, i) = ELMT_StarredList(STARREDLIST_User(ELMT_UserList(users, pointer)), i);
            }
            ELMT_StarredList(temp, idx) = id;
            STARREDLIST_User(ELMT_UserList(users, pointer)) = temp;

            printf("email dengan ID %d berhasil dipindahkan ke STARRED\n\n", id);
            waitForEnter();
        } else {
            printf("email dengan ID %d telah berada di STARRED\n\n", id);
            waitForEnter();
        }

        // printf("setelah: ");
        // for (int i = 0; i < NEFF_StarredList(STARREDLIST_User(ELMT_UserList(users, pointer))); i++) {
        //     printf("%d,", ELMT_StarredList(STARREDLIST_User(ELMT_UserList(users, pointer)), i));
        // }
        // printf("\n");
    } else {
        while (!EOP) {
            ADVWORD();
        }
        printAsRed("Setelah id email jangan ada kata-kata lagi yaa!\n");
        waitForEnter();
    }
}

void setAsUnstarred(int id) {

    if (EOP) {
        int pointer;
        for (pointer = 0; pointer < listLength_UserList(users); pointer++) {
            if (ID_User(ELMT_UserList(users, pointer)) == currentUserId) {
                break;
            }
        }

        int idx;
        for (idx = 0; idx < NEFF_StarredList(STARREDLIST_User(ELMT_UserList(users, pointer))); idx++) {
            if (ELMT_StarredList(STARREDLIST_User(ELMT_UserList(users, pointer)), idx) == id) {
                break;
            }
        }

        // printf("sebelum: ");
        // for (int i = 0; i < NEFF_StarredList(STARREDLIST_User(ELMT_UserList(users, pointer))); i++) {
        //     printf("%d,", ELMT_StarredList(STARREDLIST_User(ELMT_UserList(users, pointer)), i));
        // }
        // printf("\n");

        if (idx < NEFF_StarredList(STARREDLIST_User(ELMT_UserList(users, pointer)))) {
            StarredList temp;
            createStarredList(&temp, NEFF_StarredList(STARREDLIST_User(ELMT_UserList(users, pointer))) - 1);
            NEFF_StarredList(temp) = CAPACITY_StarredList(temp);

            int counter = 0, counter_temp = 0;
            while (counter_temp < NEFF_StarredList(temp)) {
                if (ELMT_StarredList(STARREDLIST_User(ELMT_UserList(users, pointer)), counter) == id) {
                    counter++;
                }
                ELMT_StarredList(temp, counter_temp) = ELMT_StarredList(STARREDLIST_User(ELMT_UserList(users, pointer)), counter);
                counter_temp++; counter++;
            }
            STARREDLIST_User(ELMT_UserList(users, pointer)) = temp;

            printf("email dengan ID %d berhasil dihapus dari daftar STARRED\n\n", id);
            waitForEnter();
        } else {
            printf("email dengan ID %d tidak berada di daftar STARRED\n\n", id);
            waitForEnter();
        }

        // printf("setelah: ");
        // for (int i = 0; i < NEFF_StarredList(STARREDLIST_User(ELMT_UserList(users, pointer))); i++) {
        //     printf("%d,", ELMT_StarredList(STARREDLIST_User(ELMT_UserList(users, pointer)), i));
        // }
        // printf("\n");
    } else {
        while (!EOP) {
            ADVWORD();
        }
        printAsRed("Setelah id email jangan ada kata-kata lagi yaa!\n");
        waitForEnter();
    }
}