#include <stdio.h>
#include "stack.h"
#include "../datetime/datetime.h"

//gcc driver.c stack.c ../utility/string.c ../datetime/datetime.c ../mesin_kata/mesinkata.c ../mesin_kata/mesinkarakter.c ../user/user.c ../email_list/email_list.c ../inisiasi/inisiasi.c ../utility/error_handler.c -o driver
int main() {
    EmailDraft initialDraft;
    
    Stack draftStack, redoStack;
    int kelar = 0;
    CreateEmptyStack(&draftStack);
    CreateEmptyStack(&redoStack);

    loadConfigPengguna("./../../../config/contohpengguna.config");
    loadConfigUmum("./../../../config/umum.config");
    
    printf("\n================= DRAFT SEMENTARA =================\n");
    while (true) { 
        printf(">> ");
        STARTWORD();

        if (isStringEqual(currentWord.TabWord, "BATAL")) {
            printf("Draft email berhasil dibatalkan!\n\n");
            break; 
        } 
        else if (isStringEqual(currentWord.TabWord, "BUAT_DRAFT")) {
            if (IsEmptyStack(draftStack)) {
                createEmptyDraft (&initialDraft);
                kelar = 0;
                BuatDraft(&initialDraft, &kelar);
                if(!isEmptyDraft(initialDraft)){
                    PushStack(&draftStack, initialDraft);
                    printf("Draft berhasil dibuat!\n\n");
                }
            } 
            else {
                printf("Maaf, sudah ada draft terbuat! Silahkan finalisasi draft yang sudah dibuat.\n\n");
            }
        } 
        else if (isStringEqual(currentWord.TabWord, "UBAH_DRAFT")) {
            if (IsEmptyStack(draftStack)) {
                printf("Belum ada draft yang dibuat!\n\n");
            } 
            else {
                EmailDraft draftUbah;
                createEmptyDraft (&draftUbah);
                kelar = 0;
                BuatDraft(&draftUbah, &kelar);
                if (kelar == 1){
                    PushStack(&draftStack, draftUbah);
                    printf("Draft berhasil diubah!\n\n");
                }
            }
        } 
        else if (isStringEqual(currentWord.TabWord, "LIHAT_DRAFT")) {
            if (IsEmptyStack(draftStack)) {
                printf("Belum ada draft yang dibuat.\n\n");
            } 
            else {
                PrintDraft(InfoTop(draftStack));
            }
        } 
        else if (isStringEqual(currentWord.TabWord, "KIRIM_DRAFT")) {
            if (IsEmptyStack(draftStack)) {
                printf("Belum ada draft yang dibuat.\n\n");
            } 
            else {
                EmailDraft lastEmail;
                lastEmail = InfoTop(draftStack);
                kirimDraftEmail(&AllEmails, &lastEmail);
                printf("Draft Email berhasil dikirim!.\n\n");
                break; 
            }
        } 
        else if (isStringEqual(currentWord.TabWord, "UNDO")) {
            if (IsEmptyStack(draftStack)) {
                printf("Belum ada draft yang dibuat.\n\n");
            } 
            else {
                Undo(&draftStack, &redoStack);
            }
        } 
        else if (isStringEqual(currentWord.TabWord, "REDO")) {
            if (IsEmptyStack(draftStack)) {
                printf("Belum ada draft yang dibuat.\n\n");
            } 
            else {
                Redo(&redoStack, &draftStack);
            }
        } 
        else {
            printf("Perintah tidak valid!.\n\n");
            
        }
    }
    printEmailList (AllEmails);
    return 0;
}
