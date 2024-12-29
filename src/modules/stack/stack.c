#include "stack.h"
#include <stdio.h>

/* *** Konstruktor/Kreator *** */
void CreateEmptyStack(Stack *S){
     Top(*S) = Nil;
}
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 0.. MaxEl */
/* Ciri stack kosong : TOP bernilai Nil */

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyStack(Stack S){
    return (Top(S) == Nil);
}
/* Mengirim true jika Stack kosong: lihat definisi di atas */
boolean IsFullStack(Stack S){
    return (Top(S) == MaxEl-1);
}
/* Mengirim true jika tabel penampung nilai elemen stack penuh */

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void PushStack(Stack * S, EmailDraft X){
    Top(*S) ++;
    InfoTop(*S) = X;
}
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */

/* ************ Menghapus sebuah elemen Stack ************ */
void PopStack(Stack * S, EmailDraft* X){
    *X = InfoTop(*S);
    Top(*S) --;
}
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */


void Undo(Stack *S, Stack *redoStack) {
    if (Top(*S) == 0) { // Jika hanya tersisa draft awal
        printf("Belum ada perubahan yang dapat di-undo\n\n");
    } 
    else {
        EmailDraft temp;
        PopStack(S, &temp);
        PushStack(redoStack, temp);
        printf("Perubahan berhasil di-undo\n\n");
    }
}
/*Fungsi kasar Undo*/

void Redo(Stack *redoStack, Stack *S2) { //S2 = Draft sekarang
    if (IsEmptyStack(*redoStack)) {
        printf("Belum ada perubahan yang dapat di-redo\n\n");
    } else {
        EmailDraft redo;
        PopStack(redoStack, &redo);
        PushStack(S2, redo);
        printf("Perubahan berhasil di-redo\n\n");
    }
}
/*Fungsi kasar Redo*/

void PrintDraft(EmailDraft D) {
    printf("Email Penerima: ");
    printString(Receiver(D));
    printf("\n");
    printf("Penerima CC: ");
    if (isEmpty_String(CC(D))){
        printf("<Tidak Ada>");
    }
    else{
        printString(CC(D));
    }
    printf("\n");
    printf("Waktu : ");
    displayDateTime (TimeStamp(D));
    printf("\n");
    printf("Subjek: ");
    printString(Subject(D));
    printf("\n");
    printf("Body: \n");
    printString(Body(D));
    printf("\n");
    printf("\n");
}
/*Print draft sementara*/

void createDraft(EmailDraft *newDraft, String sender, String receiver, String cc, datetime timestamp, String subject, String body, int isAreplyto) {
    assignString(newDraft->senderDraft, SIZE(newDraft->senderDraft), sender);
    assignString(newDraft->receiverDraft, SIZE(newDraft->receiverDraft), receiver);
    assignString(newDraft->ccDraft, SIZE(newDraft->ccDraft), cc);
    assignString(newDraft->subjectDraft, SIZE(newDraft->subjectDraft), subject);
    assignString(newDraft->bodyDraft, SIZE(newDraft->bodyDraft), body);
    newDraft->isAreplyDraft = isAreplyto;
    newDraft->timestampDraft = timestamp;
}

boolean isEmptyDraft (EmailDraft newDraft){
    return ( 
        isEmpty_String(newDraft.senderDraft) &&   
        isEmpty_String(newDraft.receiverDraft) && 
        isEmpty_String(newDraft.subjectDraft) &&  
        isEmpty_String(newDraft.bodyDraft)        
    );
}

//Buat draft sementara secara kasar
void BuatDraft(EmailDraft *newDraft, int *kelar, String sender) {
    String currentReceiver, currentCC, subject, body;
    datetime timestamp;
    boolean firstTry;

    // assignString(currentReceiver, SIZE(currentReceiver), currentWord.TabWord);
    // if (!isUserEmailValid(currentReceiver)){
    //     printf("Input tidak valid!\n\n\n");
    //     printf("Keluar dari menu pembuatan draft!\n\n");
    //     return;
    // }
    // else if (findUserIdByEmail(currentReceiver) == IDX_UNDEF){
    //     printf("Pengguna email dengan alamat ");
    //     printString(currentReceiver);
    //         printf(" tidak ditemukan\n\n\n");
    //         printf("Keluar dari menu pembuatan draft!\n\n");
    //     return;
    // }
    // else{
    //     printf("Masukkan Penerima CC: ");
    //     STARTWORD();
    //     assignString(currentCC, SIZE(currentCC), currentWord.TabWord);
    //     if (findUserIdByEmail (currentCC) == IDX_UNDEF && !isUserEmailValid(currentCC) && !isEmpty_String(currentCC)){
    //         printf("Pengguna email dengan alamat ");
    //         printString(currentCC);
    //         printf(" tidak ditemukan\n\n\n");
    //         printf("Keluar dari menu pembuatan draft!\n\n");
    //         return;
    //     }
    //     else{
    //         printf("Masukkan Subjek: ");
    //         STARTWORD();
    //         assignString(subject, SIZE(subject), currentWord.TabWord);
    //         while(!EOP){
    //             ADVWORD();
    //             appendString(subject, SIZE(subject), currentWord.TabWord);
    //         }
    //         if (isEmpty_String(subject)){
    //             printf("Input tidak valid!\n\n\n");
    //             printf("Keluar dari menu pembuatan draft!\n\n");
    //             return;
    //         }
    //         else {
    //             printf("Masukkan Body: \n");
    //             STARTBLOCK();
    //             assignString(body, SIZE(body), currentWord.TabWord);

    //             if (isEmpty_String(body)){
    //                 printf("Input tidak valid!\n\n\n");
    //                 printf("Keluar dari menu pembuatan draft!\n\n");
    //                 return;
    //             }
    //             else{
    //                 readDateTime(&timestamp);
    //                 createDraft (newDraft, sender, currentReceiver, currentCC, timestamp, subject, body, -1);
    //                 *kelar = 1;
    //             }
    //         }
    //     }
    // }

    firstTry = true;
    while (true) {
        if (!firstTry) {
            if (isStringEqual(currentWord.TabWord, "KEMBALI")) {
                printf("Keluar dari pembentukan draft.\n\n");
                error_code = 399;
                break;
            }
        }

        /* masukan email penerima */
        firstTry = true;
        while (true) {
            
            if (!firstTry) {
                printf("(Anda dapat memasukkan KEMBALI untuk membatalkan pembentukan draft)\n");
            }
            printf("Masukkan Email Penerima: ");
            STARTWORD();

            if (EOP) {
                if (!firstTry) {
                    if (isStringEqual(currentWord.TabWord, "KEMBALI")) {
                        printf("Membatalkan pembentukan draft!\n");
                        break;
                    }
                }
                if (!isUserEmailValid(currentWord.TabWord)) {
                    printf("Bukan email yang valid!\n\n");
                    firstTry = false;
                    continue;
                }

                if (findUserIdByEmail(currentWord.TabWord) == IDX_UNDEF) {
                    printf("email ");
                    printString(currentWord.TabWord);
                    printf(" tidak terdaftar dalam PurryMail.\n\n");
                    firstTry = false;
                } else {
                    assignString(currentReceiver, SIZE(currentReceiver), currentWord.TabWord);
                    break;
                }
            } else {
                while (!EOP) {
                    ADVWORD();
                }
                printf("Masukkan hanya 1 kata yaa!\n\n");
                firstTry = true;
            }        
        }

        if (isStringEqual(currentWord.TabWord, "KEMBALI")) {
            continue;
        }

        /* masukan penerima cc */
        firstTry = true;
        while (true) {
            
            if (!firstTry) {
                printf("(Anda dapat memasukkan KEMBALI untuk membatalkan pembentukan draft)\n");
            }
            printf("Masukkan Penerima Cc: ");
            STARTWORD();

            if (EOP) {
                if (!firstTry) {
                    if (isStringEqual(currentWord.TabWord, "KEMBALI")) {
                        printf("Membatalkan pembentukan draft!\n");
                        break;
                    }
                }

                if (!isUserEmailValid(currentWord.TabWord) && !isEmpty_String(currentWord.TabWord)) {
                    printf("Bukan email yang valid!\n\n");
                    firstTry = false;
                    continue;
                }

                if (isStringEqual(currentWord.TabWord, currentReceiver)) {
                    printf("Alamat email penerima CC tidak dapat sama dengan alamat email penerima utama!\n\n");
                    firstTry = false;
                    continue;
                }

                if (!isEmpty_String(currentWord.TabWord)) {
                    if (findUserIdByEmail(currentWord.TabWord) == IDX_UNDEF) {
                        printf("email ");
                        printString(currentWord.TabWord);
                        printf(" tidak terdaftar dalam PurryMail.\n\n");
                        firstTry = false;
                        continue;
                    } 
                }
                
                assignString(currentCC, SIZE(currentCC), currentWord.TabWord);
                break;
            } else {
                while (!EOP) {
                    ADVWORD();
                }
                printf("Masukkan hanya 1 kata yaa!\n\n");
                firstTry = true;
            }        
        }

        if (isStringEqual(currentWord.TabWord, "KEMBALI")) {
            continue;
        }

        /* masukan subjek */
        firstTry = true;
        while (true) {

            if (!firstTry) {
                printf("(Anda dapat memasukkan KEMBALI untuk membatalkan pembentukan draft)\n");
            }
            printf("Masukkan Subjek: ");
            STARTWORD();

            if (!firstTry) {
                if (EOP) {
                    if (isStringEqual(currentWord.TabWord, "KEMBALI")) {
                        printf("Membatalkan pembentukan draft!\n");
                        break;
                    }
                }
            }

            if (isEmpty_String(currentWord.TabWord)) {
                printf("Bukan subjek yang valid!\n\n");
                firstTry = false;
                continue;
            }

            assignString(subject, SIZE(subject), currentWord.TabWord);
            while (!EOP) {
                ADVWORD();
                appendString(subject, SIZE(subject), " ");
                appendString(subject, SIZE(subject), currentWord.TabWord);
            }
            break;
        }

        if (isStringEqual(currentWord.TabWord, "KEMBALI")) {
            continue;
        }

        /* masukan body */
        firstTry = true;
        while (true) {

            if (!firstTry) {
                printf("(Anda dapat memasukkan KEMBALI untuk membatalkan pembentukan draft)\n");
            }
            printf("Masukkan Body:\n");
            STARTBLOCK();

            if (EOP) {
                if (!firstTry) {
                    if (isStringEqual(currentWord.TabWord, "KEMBALI")) {
                        printf("Membatalkan pembentukan draft!\n");
                        break;
                    }
                }

                if (isEmpty_String(currentWord.TabWord)) {
                    printf("Bukan body yang valid!\n\n");
                    firstTry = false;
                    continue;
                }
                
                assignString(body, SIZE(body), currentWord.TabWord);
                break;
            }  
        }

        if (isStringEqual(currentWord.TabWord, "KEMBALI")) {
            continue;
        }

        break;
    }

    readDateTime(&timestamp);
    createDraft (newDraft, sender, currentReceiver, currentCC, timestamp, subject, body, -1);
    *kelar = 1;
}

void createReplyEmail(Email parentEmail, EmailDraft *replyDraft){

    if (EOP) {
        // printf("MasterTree saat ini:\n");
        // printTree(MasterTree, 0);
        
        SubTree parent = getSubtreeByID(ID_Email(parentEmail));
        SubTree highesParent = parent;
        while(INFOTREE(PARENT(highesParent)) != -1){
            highesParent = PARENT(highesParent);
        }

        // printf("nilai infotree parent: %d\n", INFOTREE(parent));

        int re = getHeightTree(highesParent);
        // printf("%d", INFOTREE(CHILD(ancestry)));
        // printTree(ancestry, 1);

        //TURNSTRING
        String senderEmailString;
        assignString(senderEmailString, SIZE(senderEmailString), ELMT_UserList(users, TO_Email(parentEmail)-1).userEmail);
        
        String receiverString;
        assignString(receiverString, SIZE(receiverString), ELMT_UserList(users, FROM_Email(parentEmail)-1).userEmail);
        printf("\nMasukkan Email Penerima: ");
        printString(receiverString);
        printf("\n");

        String ccString;
        boolean firstTry = true;

        while (true) {

            if (!firstTry) {
                printf("(Anda dapat memasukkan KEMBALI untuk membatalkan pembalasan pesan)\n");
            }
            printf("Masukkan Penerima Cc: ");
            STARTWORD();

            if (EOP) {
                if (!firstTry) {
                    if (isStringEqual(currentWord.TabWord, "KEMBALI")) {
                        printf("Membatalkan pembalasan pesan!\n");
                        break;
                    }
                }

                if (!isUserEmailValid(currentWord.TabWord) && !isEmpty_String(currentWord.TabWord)) {
                    printf("Bukan email yang valid!\n\n");
                    firstTry = false;
                    continue;
                }

                if (isStringEqual(currentWord.TabWord, receiverString)) {
                    printf("Alamat email penerima CC tidak dapat sama dengan alamat email penerima utama!\n\n");
                    firstTry = false;
                    continue;
                }

                if (!isEmpty_String(currentWord.TabWord)) {
                    if (findUserIdByEmail(currentWord.TabWord) == IDX_UNDEF) {
                        printf("email ");
                        printString(currentWord.TabWord);
                        printf(" tidak terdaftar dalam PurryMail.\n\n");
                        firstTry = false;
                        continue;
                    } 
                }
            
                assignString(ccString, SIZE(ccString), currentWord.TabWord);
                break;
            } else {
                while (!EOP) {
                    ADVWORD();
                }
                printf("Masukkan hanya 1 kata yaa!\n\n");
                firstTry = true;
            }
        }
        
        if (isStringEqual(currentWord.TabWord, "KEMBALI")) {
            printf("Keluar dari pembalasan pesan.\n");
            error_code = 399;
        } else {
            String subject;
            assignString(subject, SIZE(subject), "Re[");
            String temp;
            createString(temp);
            if (re == 0) {
                appendChar(temp, SIZE(temp), '0'); 
            } else {
                int number = re;
                while (number > 0) {
                    appendChar(temp, SIZE(temp), (number % 10) + '0');
                    number /= 10;
                }
            }
            for (int j = stringLength(temp) - 1; j >= 0; j--) {
                appendChar(subject, SIZE(subject), temp[j]);
            }

            appendString(subject, SIZE(subject), "]: ");

            Email highestParentEmail = ELMT_EmailList(AllEmails, INFOTREE(highesParent) - 1);
            appendString(subject, SIZE(subject), SUBJECT_Email(highestParentEmail));

            LargeString body;
            while(true){
                printf("Masukkan Body:\n");
                STARTBLOCK();
                assignString(body, SIZE(body), currentWord.TabWord);

                if (isEmpty_String(body)){
                    printf("Input tidak valid!\n\n\n");
                }
                else {
                    break;
                }
            }

            datetime t; 
            readDateTime(&t);
            createDraft(replyDraft, senderEmailString, receiverString, ccString, t, subject, body, ID_Email(parentEmail));
        }
    } else {
        while (!EOP) {
            ADVWORD();
        }
        error_code = 399;
        printf("Setelah EMAIL ID jangan ada kata-kata lagi yaa!\n");
    }
}

void kirimDraftEmail (EmailList *emailList, EmailDraft *draft){
    Email newEmail;
    newEmail.id = listLength_EmailList(AllEmails) + 1;
    newEmail.fromUserId = findUserIdByEmail(draft->senderDraft);
    newEmail.toUserId = findUserIdByEmail(draft->receiverDraft);
    if (isEmpty_String(draft->ccDraft)){
        newEmail.ccUserId = -1;
    }
    else {
        newEmail.ccUserId = findUserIdByEmail(draft->ccDraft);
    }
    assignString(newEmail.body, SIZE(newEmail.body), draft->bodyDraft);

    newEmail.timestamp = draft->timestampDraft;
    assignString(newEmail.subject, SIZE(newEmail.subject), draft->subjectDraft);

    newEmail.isAReplyTo = draft->isAreplyDraft;
    newEmail.isRead = 0;
    newEmail.ccRead = 0;
    addEmail(newEmail);
    addReplyToTree(newEmail);

    updateImportance(&AllStatusImportance, currentUserId, newEmail.toUserId, newEmail.ccUserId);
}
