
#include "busy_schedule.h"
#include <stdio.h>

// Membuat jadwal kosong untuk pengguna
void createBusySchedule(User *user, int days, int hours) {
    createMatrix(hours, days, &SCHEDULE_User(*user));

    for (int i = 0; i < ROW_EFF(SCHEDULE_User(*user)); i++) {
        for (int j = 0; j < COL_EFF(SCHEDULE_User(*user)); j++) {
            setElmt(&SCHEDULE_User(*user), i, j, 1);
        }
    }
}

// Menandai waktu tertentu sebagai sibuk
void setBusy(User *user, int day, int hour) {
    if (day < 0 || day >= 7 || hour < 0 || hour >= 24) {
        printf("Error: Indeks tidak valid.\n");
        return;
    }
    setElmt(&SCHEDULE_User(*user), hour, day, 1);
}

// Menandai waktu tertentu sebagai kosong
void setFree(User *user, int day, int hour) {
    if (day < 0 || day >= 7 || hour < 0 || hour >= 24) {
        printf("Error: Indeks tidak valid.\n");
        return;
    }
    setElmt(&SCHEDULE_User(*user), hour, day, 0);
}

// Mengecek apakah waktu tertentu sibuk
boolean isBusy(User user, int day, int hour) {
    if (day < 0 || day >= 7 || hour < 0 || hour >= 24) {
        printf("Error: Indeks tidak valid.\n");
        return false;
    }
    return getElmt(SCHEDULE_User(user), hour, day) == 1;
}

// Melihat jadwal pengguna
void viewOwnSchedule() {
    printf("Berikut jadwal kesibukanmu.\n");
    printSchedule(ELMT_UserList(users, currentUserId-1));
}

// Melihat jadwal pengguna lain
void viewOtherUserSchedule() {
    String input;
    boolean inputValid = true;;
    int countUser = 0;

    ADVWORD();
    HANDLE_EOP_ERROR();
    if(error_code != 0){
        return;
    }
    
    assignString(input, SIZE(input), currentWord.TabWord);
    countUser++;

    while (!EOP) {
        countUser++;
        ADVWORD();
    }

    if (countUser > 1) {
        printf("Masukan tidak valid! Masukkan satu alamat pengguna saja!\n");
    }

    if (findUserIdByEmail(input) == IDX_UNDEF && countUser == 1) {
        printf("Tidak ditemukan pengguna dengan alamat ");
        printString(input);
        printf(" atau input tidak valid.\n");
        inputValid = false;
    } 


    if (inputValid && countUser == 1) {
        int userId = findUserIdByEmail(input);

        printf("Berikut jadwal kesibukan ");
        printString(input);
        printf(".\n");

        printSchedule(ELMT_UserList(users, userId-1));
    }
}

// Menampilkan jadwal pengguna
void printSchedule(User user) {
    printf("      S   S   R   K   J   S   M\n");
    printf("---------------------------------\n");

    for (int hour = 0; hour < 24; hour++) {
        printf("%02d |", hour);

        for (int day = 0; day < 7; day++) {
            printf("  %c ", getElmt(SCHEDULE_User(user), hour, day) == 1 ? '*' : '.');
        }

        printf("|\n");
    }

    printf("---------------------------------\n");
}

// Mengubah jadwal pengguna berdasarkan input menggunakan mesin kata
void updateSchedule(User *user) {
    if (EOP) {
        Matrix tempMatrix;
        createMatrix(24, 7, &tempMatrix);
        for (int i = 0; i < 24; i++) {
            for (int j = 0; j < 7; j++) {
                setElmt(&tempMatrix, i, j, 1);
            }
        }
        int hour = 0, day = 0;
        int totalElmt = 0;
        boolean isValid = true;

        printf("Gunakan '*' untuk menandai sibuk dan '.' untuk menandai kosong.\n");
        printf("Format jadwal: 24 baris x 7 kolom\n");
        printf("Masukkan jadwal kesibukan baru:\n");


        START();

        while(currentChar == ' ' || currentChar == '\n') {
            ADV();
        }

        while (!EOP) {
            day = 0;

            while (!EOP && day < 7) {
                while (currentChar == ' ') {
                    ADV();
                }

                // Validasi karakter input
                if (currentChar == '*') {
                    setElmt(&tempMatrix, hour, day, 1);
                } else if (currentChar == '.') {
                    setElmt(&tempMatrix, hour, day, 0); 
                } else if (currentChar == '\n') {
                    break;
                } else {
                    isValid = false;
                }

                totalElmt++;
                day++;
                ADV();
            }

            if (day != 7) {
                isValid = false;
            }

            // Abaikan karakter newline untuk baris berikutnya
            while (currentChar == ' ' || currentChar == '\n') {
                ADV();
            }

            if (hour > 23) {
                isValid = false;
            }

            hour++;
        }

        if (totalElmt != 168) {
            isValid = false;
        }

        // Jika input tidak valid, keluarkan pesan kesalahan dan hentikan fungsi
        if (!isValid) {
            printf("\nJadwal kesibukan tidak valid!\n\n");
            return;
        }

        // Salin matriks sementara ke jadwal pengguna jika valid
        copyMatrix(tempMatrix, &SCHEDULE_User(*user));
        printf("\nJadwal kesibukan berhasil diubah.\n");
    } else {
        while (!EOP) {
            ADVWORD();
        }
        printf("Setelah perintah UBAH_JADWAL, jangan ada input lain ya, langsung kasih ';' aja :).\n");
    }
}

// Menggabungkan jadwal pengguna
void scheduleUsers() {
    STARTWORD();
    
    // Array untuk menyimpan email
    String emails[20];
    int emailCount = 0;

    while (!EndWord) {
        if (currentWord.TabWord[currentWord.Length - 1] == ';') {
            currentWord.TabWord[currentWord.Length - 1] = '\0';
            currentWord.Length--;
        }
        
        assignString(emails[emailCount], SIZE(emails[emailCount]), currentWord.TabWord);
        emailCount++;

        if (emailCount >= 20) {
            printf("Agen yang ditambahkan melebihi batas maksimal jumlah agen.\n");
            return;
        }
        ADVWORD();
    }

    if (emailCount < 1) {
        printf("SCHEDULE minimal dilakukan dengan satu agen lain.\n");
        return;
    }

    if (currentUserId == IDX_UNDEF) {
        printf("Tidak ada agen yang login\n");
        return;
    }

    while (!EOP) {
        ADVWORD();
    }

    // Validasi dan deteksi email tidak valid
    boolean allEmailsValid = true;
    boolean isEmailCurrentUserId = false;
    String invalidEmails[20];
    int invalidCount = 0;
    int validUserIds[20];
    int validUserCount = 0;

    for (int i = 0; i < emailCount; i++) {
        int userId = findUserIdByEmail(emails[i]);

        if (userId == IDX_UNDEF) {
            assignString(invalidEmails[invalidCount], SIZE(invalidEmails[invalidCount]), emails[i]);
            invalidCount++;
            allEmailsValid = false;
        } else if (userId == currentUserId) {
            isEmailCurrentUserId = true; 
        } else {
            validUserIds[validUserCount++] = userId;
        }
    }

    if (!allEmailsValid) {
        printf("Tidak ditemukan pengguna dengan alamat berikut:\n");
        for (int i = 0; i < invalidCount; i++) {
            printString(invalidEmails[i]);
            printf("%s", (i < invalidCount - 1) ? ", " : ".\n");
        }
        printf("\n");
        return;
    }

    if (validUserCount == 0 || isEmailCurrentUserId) {
        printf("SCHEDULE harus dilakukan dengan agen selain kamu.\n");
        return;
    }

    // Inisisalisasi matriks gabungan
    Matrix mergedSchedule;
    createMatrix(24, 7, &mergedSchedule);
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 7; j++) {
            setElmt(&mergedSchedule, i, j, 0);
        }
    }

    // Tambahkan jadwal pengguna yang login
    User currentUser = ELMT_UserList(users, currentUserId - 1);
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 7; j++) {
            if (getElmt(SCHEDULE_User(currentUser), i, j) == 1) {
                setElmt(&mergedSchedule, i, j, 1);
            }
        }
    }

    // Tambahkan jadwal dari email valid
    for (int i = 0; i < validUserCount; i++) {
        User user = ELMT_UserList(users, validUserIds[i] - 1);
        for (int j = 0; j < 24; j++) {
            for (int k = 0; k < 7; k++) {
                if (getElmt(SCHEDULE_User(user), j, k) == 1) {
                    setElmt(&mergedSchedule, j, k, 1);
                }
            }
        }
    }

    // Tampilkan jadwal gabungan
    printf("Berikut jadwal kesibukan gabungan antara kamu");
    if (validUserCount == 1) {
        printf(" dan ");
        printString(emails[0]);
    } else {
        for (int i = 0; i < emailCount; i++) {
            if (i == 0) printf(", ");
            else if (i == emailCount - 1) printf(", dan ");
            else printf(", ");
            printf("%s", emails[i]);
        }
    }
    
    printf(".\n");

    printf("      S   S   R   K   J   S   M\n");
    printf("---------------------------------\n");
    for (int hour = 0; hour < 24; hour++) {
        printf("%02d |", hour);
        for (int day = 0; day < 7; day++) {
            printf("  %c ", getElmt(mergedSchedule, hour, day) == 1 ? '*' : '.');
        }
        printf("|\n");
    }
    printf("---------------------------------\n");

    // Rangkuman waktu kosong
    printf("\nSebagai rangkuman, kamu dapat memilih waktu berikut untuk pertemuan:\n\n");
    const char *days[] = {"Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu", "Minggu"};
    for (int j = 0; j < 7; j++) {
        printf("%s:\n", days[j]);
        int start = -1;
        boolean hasFreeTime = false;

        for (int i = 0; i < 24; i++) {
            if (getElmt(mergedSchedule, i, j) == 0) {
                if (start == -1) start = i;
                hasFreeTime = true;
            } else if (start != -1) {
                printf("- %02d:00 - %02d:00\n", start, i);
                start = -1;
            }
        }

        if (start != -1) printf("- %02d:00 - 24:00\n", start);
        if (!hasFreeTime) printf("-\n");
    }
    printf("\n");
}   