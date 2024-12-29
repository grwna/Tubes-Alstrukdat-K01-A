#include "modules/busy_schedule/busy_schedule.h"
#include "modules/datetime/datetime.h"
#include "modules/display_inbox/display_inbox.h"
#include "modules/email_list/email_list.h"
#include "modules/encryption/encryption.h"
#include "modules/importance_status/importanceStatus.h"
#include "modules/inisiasi/inisiasi.h"
#include "modules/matrix/matrix.h"
#include "modules/mesin_kata/mesinkata.h"
#include "modules/prioqueue/prioqueue.h"
#include "modules/reply/reply.h"
#include "modules/stack/stack.h"
#include "modules/tree/tree.h"
#include "modules/user/user.h"
#include "modules/utility/boolean.h"
#include "modules/utility/error_handler.h"
#include "modules/utility/main_view.h"
#include "modules/utility/string.h"
#include "modules/busy_schedule/busy_schedule.h"
#include "modules/search/search.h"

void initBufferGlobals(){
    AllEmails.buffer = NULL;
    inbox.buffer = NULL;
    starred.buffer = NULL;
    MasterTree = NULL;
    currentTrieRoot = NULL;
}

int main(){
    error_code = 0;
    initBufferGlobals();
    system("clear");
    startPurry();
    printf("Selamat datang di PurryMail!\n");
    waitForEnter();
    while(true){
        if(error_code != 0){
            if(error_code == 401){
                HANDLE_EOP_ERROR();
            }
            print_error();
            error_code = 0;
        }

        printf("Masukkan folder konfigurasi untuk dimuat:\n>> ");
        STARTWORD();
        HANDLE_EOP_ERROR();
        if(error_code != 0){
            continue;
        }
        if(isEmpty_String(currentWord.TabWord)){
            printf("Folder konfigurasi tidak boleh kosong, silahkan coba lagi!\n");
            continue;
        }
        String configFolder;
        assignString(configFolder, SIZE(configFolder), "config/");
        appendString(configFolder, SIZE(configFolder), currentWord.TabWord);
        if(!isFolderExists(configFolder)){
            printf("Folder konfigurasi tidak ditemukan, silahkan coba lagi!\n");
            continue;
        }
        
        String configPengguna;
        assignString(configPengguna, SIZE(configPengguna), configFolder);
        appendString(configPengguna, SIZE(configPengguna), "/pengguna.config");
        loadConfigPengguna(configPengguna);

        String configUmum;
        assignString(configUmum, SIZE(configUmum), configFolder);
        appendString(configUmum, SIZE(configUmum), "/umum.config");
        loadConfigUmum(configUmum);
        
        String configEmail;
        assignString(configEmail, SIZE(configEmail), configFolder);
        appendString(configEmail, SIZE(configEmail), "/email.config");
        loadConfigEmail(configEmail);

        if(error_code == 0){
            printf("Konfigurasi berhasil dimuat!\n");
            break;
        } else {
            continue;
        }
    }
    while(true){
        if(error_code != 0){
            if(error_code == 401){
                HANDLE_EOP_ERROR();
            }
            print_error();
            error_code = 0;
        }
        waitForEnter();
        if(currentUserId != -1){
            printf("Halo, %s!\n", ELMT_UserList(users, currentUserId-1).userEmail);
        }
        else{
            printf("Selamat datang di PurryMail!\n");
        }
        printHelp();
        // Perintah
        printf(">> ");
        STARTWORD();
        if(error_code != 0){
            continue;
        }
        if(isStringEqual(currentWord.TabWord, "EXIT")){
            HANDLE_EOP_ERROR();
            if(error_code != 0){
                continue;
            }
            printf("Apakah anda yakin ingin keluar? (y/n)\n>> ");
            STARTWORD();
            HANDLE_EOP_ERROR();
            if(error_code != 0){
                continue;
            }
            if(isStringEqual(currentWord.TabWord, "y") || isStringEqual(currentWord.TabWord, "Y") || isStringEqual(currentWord.TabWord, "n") || isStringEqual(currentWord.TabWord, "N")){
                if (isStringEqual(currentWord.TabWord, "y") || isStringEqual(currentWord.TabWord, "Y")) {
                    printf("ヾ(˶ᵔ ᗜ ᵔ˶) selamat bertugas, Agen!\n");
                    break;
                } else {
                    printf("kembali ke tampilan utama!\n");
                    continue;
                }
            } else{
                printf("bukan input yang valid!\n");
                continue;
            }
            break;

        /* **** User Commands **** */

        } else if(isStringEqual(currentWord.TabWord, "REGISTER")){ 
            HANDLE_EOP_ERROR();
            if(error_code != 0){
                continue;
            }
            if(listLength_UserList(users) == 20){
                printf("Jumlah user sudah mencapai batas maksimum\n");
                continue;
            }
            if(currentUserId != -1){
                printf("Anda sudah login, silahkan logout terlebih dahulu untuk melakukan registrasi!\n");
                continue;
            }
            printf("\nMasukkan email address:\n>> ");
            STARTWORD();
            HANDLE_EOP_ERROR();
            if(error_code != 0){
                continue;
            }
            String email;
            assignString(email, SIZE(email), currentWord.TabWord);
            if(!isUserEmailValid(email)){
                printf("Email tidak valid, silahkan coba lagi!\n");
                continue;
            }
            if(findUserIdByEmail(email) != -1){
                printf("Email sudah terdaftar, silahkan coba lagi!\n");
                continue;
            }
            printf("Masukkan password:\n>> ");
            STARTWORD();
            HANDLE_EOP_ERROR();
            if(error_code != 0){
                continue;
            }
            String password;
            assignString(password, SIZE(password), currentWord.TabWord);
            if(!isPasswordValid(password)){
                printf("Password tidak valid, silahkan coba lagi!\n");
                continue;
            }
            StarredList empty;
            createStarredList(&empty, 5);
            addUser(email, password, empty);
            updateSizeStatusImportance(&AllStatusImportance, listLength_UserList(users));
            deallocateStarredList(&empty);
            printf("Registrasi berhasil!\n");
            continue;

        } else if(isStringEqual(currentWord.TabWord, "LOGIN")){
            HANDLE_EOP_ERROR();
            if(error_code != 0){
                continue;
            }
            if(currentUserId != -1){
                printf("Anda sudah login, silahkan logout terlebih dahulu untuk melakukan login lagi!\n");
                continue;
            }
            if(listLength_UserList(users) == 0){
                printf("Belum ada user terdaftar, silahkan registrasi terlebih dahulu!\n");
                continue;
            }
            printf("\nMasukkan email:\n>> ");
            STARTWORD();
            HANDLE_EOP_ERROR();
            if(error_code != 0){
                continue;
            }
            String email;
            assignString(email, SIZE(email), currentWord.TabWord);
            if(error_code != 0){
                printf("Panjang email melebihi batas, silahkan coba lagi!\n");
                error_code = 0;
                continue;
            }
            int tempUserId = findUserIdByEmail(email);
            if(!isUserEmailValid(email)){
                printf("Email tidak valid, silahkan coba lagi!\n");
                continue;
            }
            if(tempUserId == -1){
                printf("Email tidak ditemukan, silahkan coba lagi!\n");
                continue;
            }
            printf("Masukkan password:\n>> ");
            STARTWORD();
            HANDLE_EOP_ERROR();
            if(error_code != 0){
                continue;
            }
            String password;
            assignString(password, SIZE(password), currentWord.TabWord);
            if(error_code != 0){
                printf("Panjang password melebihi batas, silahkan coba lagi!\n");
                error_code = 0;
                continue;
            }
            if(isLoginValid(tempUserId, password)){
                userLogin(tempUserId);
                initTrie(&currentTrieRoot);
                getInbox();
                fillTrieFromInbox(&currentTrieRoot, inbox);
                printf("Login berhasil!\n");
                system("sleep 1");
                system("clear");
                printf("Selamat datang, %s!\n", ELMT_UserList(users, currentUserId-1).userEmail);
                tampilkan_notif(currentUserId);
                continue;
            } else {
                printf("Password salah\n");
            }
        }
        else if(isStringEqual(currentWord.TabWord, "LOGOUT")){
            HANDLE_EOP_ERROR();
            if(error_code != 0){
                continue;
            }
            if(currentUserId == -1){
                printf("Anda belum login!\n");
                continue;
            }
            userLogout();
            printf("ヾ(˶ᵔ ᗜ ᵔ˶) Logout berhasil!\n");

        /* **** Draft Commands **** */

        } else if(isStringEqual(currentWord.TabWord, "BUAT_DRAFT")) {
            HANDLE_EOP_ERROR();
            if(error_code != 0){
                continue;
            }
            if(currentUserId == -1){
                printf("Anda belum login!\n");
                continue;
            }
            else{
                printf("\n\n================= MENU DRAFT =================\n\n");
                EmailDraft initialDraft;
                Stack draftStack, redoStack;
                int kelar = 0;
                CreateEmptyStack(&draftStack);
                CreateEmptyStack(&redoStack);

                if (IsEmptyStack(draftStack)) {
                    kelar = 0;
                    BuatDraft(&initialDraft, &kelar, ELMT_UserList(users, currentUserId-1).userEmail);
                    if (error_code != 0) {
                        error_code = 0;
                        continue;
                    }

                    if(!isEmptyDraft(initialDraft) && kelar == 1){
                        PushStack(&draftStack, initialDraft);
                        printf("Draft berhasil dibuat!\n\n");
                    while (true) {
                        waitForEnter(); 
                        printf("pilihan input: UBAH_DRAFT, LIHAT_DRAFT, ENKRIPSI, KIRIM_DRAFT, UNDO, REDO, atau BATAL\n");
                        printf(">> ");
                        STARTWORD();
                        HANDLE_EOP_ERROR();
                        if(error_code != 0){
                            continue;
                        }

                        if (isStringEqual(currentWord.TabWord, "BATAL")) {
                            printf("Draft email berhasil dibatalkan!\n\n\n");
                            printf("Keluar dari menu pembuatan draft!\n\n");
                            break; 
                        } 
                        else if (isStringEqual(currentWord.TabWord, "BUAT_DRAFT")) { 
                            printf("Maaf, sudah ada draft terbuat! Silahkan finalisasi draft yang sudah dibuat.\n\n");
                        } 
                        else if (isStringEqual(currentWord.TabWord, "UBAH_DRAFT")) {
                            if (IsEmptyStack(draftStack)) {
                                printf("Belum ada draft yang dibuat!\n\n");
                            } 
                            else {
                                EmailDraft draftUbah;
                                kelar = 0;
                                BuatDraft(&draftUbah, &kelar, ELMT_UserList(users, currentUserId-1).userEmail);
                                if (error_code != 0) {
                                    error_code = 0;
                                    continue;
                                }
                                
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
                        else if (isStringEqual(currentWord.TabWord, "ENKRIPSI")) {
                            if (IsEmptyStack(draftStack)) {
                                printf("Belum ada draft yang dibuat.\n\n");
                            } 
                            else {
                                encrypt(InfoTop(draftStack).bodyDraft);
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
                                printf("Draft Email berhasil dikirim!.\n\n\n");
                                printf("Kembali ke menu utama\n\n");
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
                } 
            }
        }
        
        /* **** Inbox Commands **** */

        } else if(isStringEqual(currentWord.TabWord, "DAFTAR_INBOX")) {
            HANDLE_EOP_ERROR();
            if(error_code != 0){
                continue;
            }
            if(currentUserId == -1){
                printf("Anda belum login!\n");
                continue;
            }
            displayInbox();
        

        } else if(isStringEqual(currentWord.TabWord, "DAFTAR_STARRED")) {
            HANDLE_EOP_ERROR();
            if(error_code != 0){
                continue;
            }
            if(currentUserId == -1){
                printf("Anda belum login!\n");
                continue;
            }
            displayStarred();     
        
        /* **** Importance Status Commands **** */

        } else if(isStringEqual(currentWord.TabWord, "STATUS_KEPENTINGAN")){
            HANDLE_EOP_ERROR();
            if(error_code != 0){
                continue;
            }
            if(currentUserId == -1){
                printf("Anda belum login!\n");
                continue;
            }
            displayStatus(AllStatusImportance);

        /* **** SAVE & LOAD **** */

        } else if(isStringEqual(currentWord.TabWord, "SAVE")){
            HANDLE_EOP_ERROR();
            if(error_code != 0){
                continue;
            }
            printf("Masukkan folder konfigurasi untuk disimpan:\n>> ");
            STARTWORD();
            HANDLE_EOP_ERROR();
            if(error_code != 0){
                continue;
            }
            if(isEmpty_String(currentWord.TabWord)){
                printf("Folder konfigurasi tidak boleh kosong, silahkan coba lagi!\n");
                continue;
            }
            else if(!isFolderNameValid(currentWord.TabWord)){
                printf("Nama folder konfigurasi hanya boleh berisi huruf, angka, '-', dan '_'.\n");
                printf("Silahkan coba lagi!\n");
                continue;
            }
            String configFolder;
            assignString(configFolder, SIZE(configFolder), currentWord.TabWord);
            saveConfigToFolder(configFolder);

        } else if(isStringEqual(currentWord.TabWord, "LOAD")){
            if(currentUserId != -1){
                printf("Anda harus logout terlebih dahulu untuk melakukan perintah ini.\n");
                continue;
            }
            HANDLE_EOP_ERROR();
            if(error_code != 0){
                continue;
            }
            printf("Masukkan folder konfigurasi untuk dimuat:\n>> ");
            STARTWORD();
            HANDLE_EOP_ERROR();
            if(error_code != 0){
                continue;
            }
            if(isEmpty_String(currentWord.TabWord)){
                printf("Folder konfigurasi tidak boleh kosong, silahkan coba lagi!\n");
                continue;
            }
            String configFolder;
            assignString(configFolder, SIZE(configFolder), "config/");
            appendString(configFolder, SIZE(configFolder), currentWord.TabWord);
            if(!isFolderExists(configFolder)){
                printf("Folder konfigurasi tidak ditemukan, silahkan coba lagi!\n");
                continue;
            }
            
            String configPengguna;
            assignString(configPengguna, SIZE(configPengguna), configFolder);
            appendString(configPengguna, SIZE(configPengguna), "/pengguna.config");
            loadConfigPengguna(configPengguna);

            String configUmum;
            assignString(configUmum, SIZE(configUmum), configFolder);
            appendString(configUmum, SIZE(configUmum), "/umum.config");
            loadConfigUmum(configUmum);
            
            String configEmail;
            assignString(configEmail, SIZE(configEmail), configFolder);
            appendString(configEmail, SIZE(configEmail), "/email.config");
            loadConfigEmail(configEmail);

            if(error_code == 0){
                printf("Konfigurasi berhasil dimuat!\n");
                break;
            } else {
                continue;
            }
        } else if(isStringEqual(currentWord.TabWord, "CARI_PESAN")){
            if(currentUserId == -1){
                printf("Anda belum login!\n");
                continue;
            }
            if(EOP){
                printf("Kata yang ingin dicari tidak boleh kosong, silahkan coba lagi!\n");
            } else{
                ADVWORD();
                HANDLE_EOP_ERROR();
                if(error_code != 0){
                    continue;
                }
                for(int i = 0; i < currentWord.Length; i++){
                    if(currentWord.TabWord[i] < 'a' || currentWord.TabWord[i] > 'z'){
                        error_code = 2;
                        break;
                    }
                }
                if(error_code != 0){
                    printf("Kata yang ingin dicari hanya boleh berisi huruf kecil, silahkan coba lagi!\n");
                    error_code = 0;
                    continue;
                }
                displaySearchResult(currentWord.TabWord);
            }
        } else if(isStringEqual(currentWord.TabWord, "LIHAT_JADWAL")){
            if(currentUserId == -1){
                printf("Anda belum login!\n");
                continue;
            }
            if (EOP){
                viewOwnSchedule();
            } else{
                viewOtherUserSchedule();
                if(error_code != 0){
                    continue;
                }
            }
            
        } else if(isStringEqual(currentWord.TabWord, "UBAH_JADWAL")){
            HANDLE_EOP_ERROR();
            if(error_code != 0){
                continue;
            }
            if(currentUserId == -1){
                printf("Anda belum login!\n");
                continue;
            }
            updateSchedule(&ELMT_UserList(users, currentUserId-1));

        } else if(isStringEqual(currentWord.TabWord, "SCHEDULE")){
            if(error_code != 0){
                continue;
            }
            if (currentUserId == -1){
                printf("Anda belum login!\n");
                continue;
            } 

            if (EOP){
                printf("Setidaknya harus ada satu agen yang dijadwalkan.\n");
                continue;
            } else{
                scheduleUsers();
                if(error_code != 0){
                    continue;
                }
            }

        } else{
            HANDLE_EOP_ERROR();
            error_code = 0;
            printf("Perintah tidak dikenali, silahkan coba lagi!\n");
        }
    }
}