#include <stdio.h>
#include "prioqueue.h"
#include "../utility/boolean.h"


//gcc driver.c prioqueue.c ../utility/string.c ../datetime/datetime.c ../mesin_kata/mesinkata.c ../mesin_kata/mesinkarakter.c ../user/user.c ../email_list/email_list.c ../inisiasi/inisiasi.c ../utility/error_handler.c -o driver
int main (){
    readEmailFromConfig("./../../../contohemail.config"); //belum bener
    loadConfigPengguna("./../../../config/contohpengguna.config");
    loadConfigUmum("./../../../config/umum.config");

    Notif notifikasi;
    PrioQueue Q;
    String subjectNotif;
    datetime waktuNotif;
    StatusImportance S;
    boolean importantNotif;

    int i, n;
    char penting, c;

    CreatePrioQueue(&Q);
    printEmailList (AllEmails);
    initStatusImportance (&S, listLength_UserList(users));

    for (i = 0; i < listLength_EmailList(AllEmails); i++){
        if (isImportant(&S, FROM_Email(AllEmails.buffer[i]), TO_Email(AllEmails.buffer[i]), importantLimit)){
            importantNotif = true;
        }
        else {
            importantNotif = false;
        }
        
        String subjectNotif;
        assignString(subjectNotif, SIZE(subjectNotif), SUBJECT_Email(AllEmails.buffer[i]));

        createNotif(&notifikasi, TIMESTAMP_Email(AllEmails.buffer[i]), importantNotif, subjectNotif);
        enqueuePrio(&Q, notifikasi);
        dealocateString (&subjectNotif);
    }
    
    printNotif(Q);
    return 0;
}

