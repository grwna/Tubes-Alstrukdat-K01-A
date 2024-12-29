#include "prioqueue.h"
#include <stdio.h>
#include "../utility/boolean.h"
#include <stdlib.h> 

void CreatePrioQueue(PrioQueue *Q){
    IDX_HEAD(*Q) = IDX_UNDEF;
    IDX_TAIL(*Q) = IDX_UNDEF;
}
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dengan kondisi sbb: */
/* - Index head bernilai IDX_UNDEF */
/* - Index tail bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */

/* ********* Prototype ********* */
boolean isEmptyPrio(PrioQueue Q){
        return IDX_HEAD(Q) == IDX_UNDEF;

}
/* Mengirim true jika Q kosong: lihat definisi di atas */
boolean isFullPrio(PrioQueue Q){
    return (IDX_TAIL(Q) + 1) % CAPACITY == IDX_HEAD(Q);
}
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu IDX_TAIL akan selalu di belakang IDX_HEAD dalam buffer melingkar*/

int lengthPrio(PrioQueue Q){
    if(isEmptyPrio(Q)){
        return 0;
    }
    else{
        return (IDX_TAIL(Q) - IDX_HEAD(Q) + CAPACITY) % CAPACITY + 1;
    }
}
/* Mengirimkan banyaknya elemen prioqueue. Mengirimkan 0 jika Q kosong. */

/* *** Primitif Add/Delete *** */
void enqueuePrio(PrioQueue *Q, Notif val){
    if(isEmptyPrio(*Q)){
        IDX_HEAD(*Q) = 0;
        IDX_TAIL(*Q) = 0;
    }
    else{
        IDX_TAIL(*Q) = (IDX_TAIL(*Q) + 1) % CAPACITY;
    }
    TAIL(*Q) = val;
    sortPrio(Q);
}
/* Proses: Menambahkan val pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. val disisipkan pada posisi yang sesuai, IDX_TAIL "mundur" dalam buffer melingkar.,
        Q terurut mengecil */

void dequeuePrio(PrioQueue *Q, Notif *val){
    *val = HEAD(*Q);
    if(IDX_HEAD(*Q) == IDX_TAIL(*Q)){
        IDX_HEAD(*Q) = IDX_UNDEF;
        IDX_TAIL(*Q) = IDX_UNDEF;
    }
    else{
        IDX_HEAD(*Q) = (IDX_HEAD(*Q) + 1) % CAPACITY;
    }
}
/* Proses: Menghapus val pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. val = nilai elemen HEAD pd I.S., IDX_HEAD "mundur";
        Q mungkin kosong */

/* *** Display Queue *** */
// void displayPrioQueue(PrioQueue Q){
//     if(isEmptyPrio(Q)){
//         printf("[]\n");
//     }
//     else{
//         printf("[");
//         Notif val;
//         do{
//             dequeuePrio(&Q, &val);
//             printf("%d", val);
//             if(!isEmptyPrio(Q)){
//                 printf(",");
//             }
//         }while(!isEmptyPrio(Q));
//         printf("]\n");
//     }
// }

void dealokasiPrio(PrioQueue * Q){
    IDX_HEAD(*Q) = IDX_UNDEF;
    IDX_TAIL(*Q) = IDX_UNDEF;
    free((*Q).buffer);
}
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi */

void createNotif (Notif *notifikasi, datetime waktu, boolean importance, String subject){
    WAKTU(*notifikasi) = waktu;
    IMPORTANCE(*notifikasi) = importance;
    assignString (SUBJECT(*notifikasi), SIZE(SUBJECT(*notifikasi)), subject);
}

boolean isImportant (StatusImportance *S, int fromUserId, int toUserId, int importantLimit){
    return ((*S).matrix.mem[fromUserId-1][toUserId-1] >= importantLimit);

}

boolean isAfter(datetime t1, datetime t2) {
    if (YEARS(t1) != YEARS(t2)) {
        return YEARS(t1) > YEARS(t2);
    }
    if (MONTHS(t1) != MONTHS(t2)) {
        return MONTHS(t1) > MONTHS(t2);
    }
    if (DAYS(t1) != DAYS(t2)) {
        return DAYS(t1) > DAYS(t2);
    }
    if (HOURS(t1) != HOURS(t2)) {
        return HOURS(t1) > HOURS(t2);
    }
    if (MINUTES(t1) != MINUTES(t2)) {
        return MINUTES(t1) > MINUTES(t2);
    }
    return SECONDS(t1) > SECONDS(t2);
}

void sortPrio(PrioQueue *Q) {
    int n = (IDX_TAIL(*Q) >= IDX_HEAD(*Q)) 
            ? (IDX_TAIL(*Q) - IDX_HEAD(*Q) + 1) 
            : (CAPACITY - IDX_HEAD(*Q) + IDX_TAIL(*Q) + 1);

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            int idx1 = (IDX_HEAD(*Q) + j) % CAPACITY;
            int idx2 = (IDX_HEAD(*Q) + j + 1) % CAPACITY;

            // Bandingkan berdasarkan kepentingan
            if (Q->buffer[idx1].importance < Q->buffer[idx2].importance ||
                // Jika kepentingan sama, bandingkan berdasarkan waktu
                (Q->buffer[idx1].importance == Q->buffer[idx2].importance &&
                 isAfter(Q->buffer[idx1].waktu, Q->buffer[idx2].waktu))) {

                // Tukar elemen
                Notif temp = Q->buffer[idx1];
                Q->buffer[idx1] = Q->buffer[idx2];
                Q->buffer[idx2] = temp;
            }
        }
    }
}

/*Sort notifikasi berdasarkan tingkat kepentingan, lalu berdasarkan waktu*/

void printNotif(PrioQueue Q) {
    int MAX_WIDTH = 140;
    if (isEmptyPrio(Q)) {
        // Header untuk kondisi kosong
        printf("\n+");
        for (int i = 0; i < MAX_WIDTH - 2; i++) printf("-");
        printf("+\n");
        printf("|%-*s|\n", MAX_WIDTH - 2, " \033[1mSantai aja, gaada notifikasi kok!\033[0m");
        printf("+");
        for (int i = 0; i < MAX_WIDTH - 2; i++) printf("-");
        printf("+\n\n");
    } else {
        // Header untuk kondisi ada notifikasi
        printf("\n+");
        for (int i = 0; i < MAX_WIDTH - 2; i++) printf("-");
        printf("+\n");

        // Menempatkan "NOTIFIKASI KAMU" di tengah
        int len = stringLength("NOTIFIKASI KAMU");
        int padding = (MAX_WIDTH - 2 - len) / 2;
        printf("|");
        for (int i = 0; i < padding; i++) printf(" ");
        printf("\033[1mNOTIFIKASI KAMU\033[0m");
        for (int i = 0; i < MAX_WIDTH - 2 - padding - len; i++) printf(" ");
        printf("|\n");

        printf("+");
        for (int i = 0; i < MAX_WIDTH - 2; i++) printf("-");
        printf("+\n");

        int i = IDX_HEAD(Q);
        while (true) {
            printf("| "); // Batas kiri kotak

            // Format waktu
            String waktu;
            setDateTimeasStringConfig(waktu, WAKTU(Q.buffer[i]));
            printString(waktu);

            // Penting atau tidak
            if (IMPORTANCE(Q.buffer[i])) {
                printf(" \033[1m\033[31m[IMPORTANT]\033[0m ");
            } else {
                printf("              ");
            }

            // Subjek notifikasi
            String subject;
            assignString(subject, 256, SUBJECT(Q.buffer[i]));
            int total_len = stringLength(waktu) + stringLength(subject) + 14; // 14 = panjang " [IMPORTANT] "

            if (total_len > (MAX_WIDTH - 4)) { // Jika terlalu panjang, potong teks
                for (int j = 0; j < (MAX_WIDTH - 4 - stringLength(waktu) - 14); j++) {
                    printf("%c", subject[j]);
                }
                printf("..."); // Tambahkan tanda potong
            } else {
                printString(subject); // Tampilkan subjek penuh
                for (int j = total_len; j < (MAX_WIDTH - 4); j++) { // Isi sisa ruang
                    printf(" ");
                }
            }
            printf(" |\n"); // Batas kanan kotak

            if (i == IDX_TAIL(Q)) {
                break;
            }
            // Separator antar notifikasi
            printf("+");
            for (int j = 0; j < MAX_WIDTH - 2; j++) printf("-");
            printf("+\n");
            i = (i + 1) % CAPACITY;
        }

        // Footer
        printf("+");
        for (int i = 0; i < MAX_WIDTH - 2; i++) printf("-");
        printf("+\n");
    }
}

/* Melakukan print notifikasi */

void tampilkan_notif(int currentUserId){
    Notif notifikasi;
    PrioQueue Q;
    String subjectNotif;
    datetime waktuNotif;
    boolean importantNotif;

    CreatePrioQueue(&Q);
    int i;

    for (i = 0; i < listLength_EmailList(AllEmails); i++){
        if (!(ISREAD_Email(AllEmails.buffer[i])) && TO_Email(AllEmails.buffer[i]) == currentUserId){
            importantNotif = isEmailImportanceReached(AllStatusImportance, FROM_Email(AllEmails.buffer[i]), TO_Email(AllEmails.buffer[i]));

            assignString (subjectNotif, SIZE(subjectNotif), (SUBJECT_Email(AllEmails.buffer[i])));
            waktuNotif = TIMESTAMP_Email(AllEmails.buffer[i]);

            createNotif(&notifikasi, waktuNotif, importantNotif, subjectNotif);
            enqueuePrio(&Q, notifikasi);
        }

        else if (!(CCREAD_Email(AllEmails.buffer[i])) && CC_Email(AllEmails.buffer[i]) == currentUserId){
            importantNotif = isEmailImportanceReached(AllStatusImportance, FROM_Email(AllEmails.buffer[i]), CC_Email(AllEmails.buffer[i]));

            assignString (subjectNotif, SIZE(subjectNotif), (SUBJECT_Email(AllEmails.buffer[i])));
            waktuNotif = TIMESTAMP_Email(AllEmails.buffer[i]);

            createNotif(&notifikasi, waktuNotif, importantNotif, subjectNotif);
            enqueuePrio(&Q, notifikasi);
        }
    }
    printNotif(Q);
    printf("\n\n");
}