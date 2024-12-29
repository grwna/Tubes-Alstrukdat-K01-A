#include "email_list.h"
#include <stdio.h>

EmailList AllEmails;
EmailList inbox;
EmailList starred;
EmailList searchResult;

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create email */
void createEmail(Email *email, 
                 int emailId, 
                 int fromUserId,  
                 int toUserId, 
                 int ccUserId, 
                 datetime timestamp, 
                 String subject, 
                 String body, 
                 int isAReplyTo, 
                 boolean isRead, 
                 boolean ccRead){

    ID_Email(*email) = emailId;
    FROM_Email(*email) = fromUserId;
    TO_Email(*email) = toUserId;
    CC_Email(*email) = ccUserId;
    assignString(BODY_Email(*email), SIZE(BODY_Email(*email)), body);
    TIMESTAMP_Email(*email) = timestamp;
    assignString(SUBJECT_Email(*email), SIZE(SUBJECT_Email(*email)), subject);
    REPLY_Email(*email) = isAReplyTo;
    ISREAD_Email(*email) = isRead;
    CCREAD_Email(*email) = ccRead;
}

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create list kosong  */
void createEmailList(EmailList *l, int capacity){
    CAPACITY_EmailList(*l) = capacity;
    NEFF_EmailList(*l) = 0;
    BUFFER_EmailList(*l) = (Email *) malloc(CAPACITY_EmailList(*l) * sizeof(Email));
    if(BUFFER_EmailList(*l) == NULL){
        CAPACITY_EmailList(*l) = 0;
    }
}

void deallocateList(EmailList *l){
    if(BUFFER_EmailList(*l) != NULL){
        free(BUFFER_EmailList(*l));
    }
    BUFFER_EmailList(*l) = NULL;
    CAPACITY_EmailList(*l) = 0;
    NEFF_EmailList(*l) = 0;
}

int listLength_EmailList(EmailList l){
    return NEFF_EmailList(l);
}

boolean isEmpty_EmailList(EmailList l){
    return !NEFF_EmailList(l);
}

boolean isFull_EmailList(EmailList l){
    return NEFF_EmailList(l) == CAPACITY_EmailList(l);
}

void insertLast_EmailList(EmailList *l, Email newEmail){
    int idx = NEFF_EmailList(*l);
    createEmail(&ELMT_EmailList(*l, idx), 
                ID_Email(newEmail), 
                FROM_Email(newEmail), 
                TO_Email(newEmail), 
                CC_Email(newEmail), 
                TIMESTAMP_Email(newEmail),
                SUBJECT_Email(newEmail), 
                BODY_Email(newEmail), 
                REPLY_Email(newEmail), 
                ISREAD_Email(newEmail), 
                CCREAD_Email(newEmail));
    NEFF_EmailList(*l)++;
}

void reallocList(EmailList *l, int newCapacity){
    Email *newBuffer = (Email *) malloc(newCapacity * sizeof(Email));
    for(int i = 0; i < NEFF_EmailList(*l); i++){
        createEmail(&newBuffer[i], 
                    ID_Email(ELMT_EmailList(*l, i)), 
                    FROM_Email(ELMT_EmailList(*l, i)), 
                    TO_Email(ELMT_EmailList(*l, i)), 
                    CC_Email(ELMT_EmailList(*l, i)), 
                    TIMESTAMP_Email(ELMT_EmailList(*l, i)),
                    SUBJECT_Email(ELMT_EmailList(*l, i)), 
                    BODY_Email(ELMT_EmailList(*l, i)), 
                    REPLY_Email(ELMT_EmailList(*l, i)), 
                    ISREAD_Email(ELMT_EmailList(*l, i)), 
                    CCREAD_Email(ELMT_EmailList(*l, i)));
    }
    free(BUFFER_EmailList(*l));
    BUFFER_EmailList(*l) = newBuffer;
}

void expandList(EmailList *l, int num){
    CAPACITY_EmailList(*l) += num;
    reallocList(l, CAPACITY_EmailList(*l));
    reallocList(l, CAPACITY_EmailList(*l));
}

void shrinkList(EmailList *l, int num){
    CAPACITY_EmailList(*l) -= num;
    reallocList(l, CAPACITY_EmailList(*l));
    reallocList(l, CAPACITY_EmailList(*l));
}

void compressList(EmailList *l){
    CAPACITY_EmailList(*l) = NEFF_EmailList(*l);
    reallocList(l, CAPACITY_EmailList(*l));
    reallocList(l, CAPACITY_EmailList(*l));
}

void addEmail(Email newEmail){
    if(isFull_EmailList(AllEmails)){
        expandList(&AllEmails, 10);
    }
    insertLast_EmailList(&AllEmails, newEmail);
}

void getInbox(){
    int count = 0;
    for (int i = 0; i < listLength_EmailList(AllEmails); i++){
        if (ELMT_EmailList(AllEmails, i).toUserId == currentUserId || ELMT_EmailList(AllEmails, i).ccUserId == currentUserId)
        {
            count++;
        }
    }
    deallocateList(&inbox);
    createEmailList(&inbox, count+10);

    for (int i = listLength_EmailList(AllEmails)-1; i >= 0 && count > 0; i--){ // search dari belakang untuk mendapat email terbaru di atas
        if (ELMT_EmailList(AllEmails, i).toUserId == currentUserId || ELMT_EmailList(AllEmails, i).ccUserId == currentUserId)
        {
            insertLast_EmailList(&inbox, ELMT_EmailList(AllEmails, i));
            count--;
        }
    }

    // sortEmailListbyTime(&inbox);
}

void getStarred(){
    User currentUser = ELMT_UserList(users, currentUserId - 1);
    int count = NEFF_StarredList(STARREDLIST_User(currentUser));
    deallocateList(&starred);
    createEmailList(&starred, count+10);
    
    for (int i = 0; i < listLength_EmailList(AllEmails) && count > 0; i++){
        if (ELMT_EmailList(AllEmails, i).toUserId == currentUserId || ELMT_EmailList(AllEmails, i).ccUserId == currentUserId)
        {
            for (int j = 0; j < NEFF_StarredList(STARREDLIST_User(currentUser)); j++) {
                if (ID_Email(ELMT_EmailList(AllEmails, i)) == ELMT_StarredList(STARREDLIST_User(currentUser), j))
                {
                    insertLast_EmailList(&starred, ELMT_EmailList(AllEmails, i));
                    count--;
                }
            }
        }
    }

    // sortEmailListbyTime(&starred);
}

void printEmailList(EmailList l){
    for (int i = 0; i < listLength_EmailList(l); i++){
        printf("Email %d\n", ID_Email(ELMT_EmailList(l, i)));
        printf("From: %d\n", FROM_Email(ELMT_EmailList(l, i)));
        printf("To: %d\n", TO_Email(ELMT_EmailList(l, i)));
        printf("CC: %d\n", CC_Email(ELMT_EmailList(l, i)));
        printf("Timestamp: ");
        String timestampString;
        setDateTimeasStringInbox(timestampString, TIMESTAMP_Email(ELMT_EmailList(l, i)));
        printString(timestampString);
        printf("\nSubject: ");
        printString(SUBJECT_Email(ELMT_EmailList(l, i)));
        printf("\nBody: ");
        printf("\nBody: ");
        printString(BODY_Email(ELMT_EmailList(l, i)));
        printf("\nIs a reply to: %d\n", REPLY_Email(ELMT_EmailList(l, i)));
        printf("\nIs a reply to: %d\n", REPLY_Email(ELMT_EmailList(l, i)));
        printf("Is read: %d\n", ISREAD_Email(ELMT_EmailList(l, i)));
        printf("Is CC read: %d\n\n", CCREAD_Email(ELMT_EmailList(l, i)));
        printf("Is CC read: %d\n\n", CCREAD_Email(ELMT_EmailList(l, i)));
    }
}

// void sortEmailListbyTime(EmailList *l) {
//     for (int i = 0; i < listLength_EmailList(*l); i++) {
//         int minIndex = i;
//         for (int j = i + 1; j < listLength_EmailList(*l); j++) {
//             if (isLater(readDateTimefromString(TIMESTAMP_Email(ELMT_EmailList(*l, j))), readDateTimefromString(TIMESTAMP_Email(ELMT_EmailList(*l, minIndex))))) {
//                 minIndex = j;
//             }
//         }

//         Email tempEmail = ELMT_EmailList(*l, i);
//         ELMT_EmailList(*l, i) = ELMT_EmailList(*l, minIndex);
//         ELMT_EmailList(*l, minIndex) = tempEmail;

//     }
// }

Email getEmailbyID (int id) {

    for (int i = 0; i < listLength_EmailList(AllEmails); i++) {
        if (ID_Email(ELMT_EmailList(AllEmails, i)) == id) {
            return (ELMT_EmailList(AllEmails, i));
        }
    }

    printf("Tidak ada email dengan ID tersebut.\n");

    Email returnbodong;
    datetime timestamp;
    String subject;
    assignString(subject, SIZE(subject), "-");
    String body;
    assignString(body, SIZE(body), "-");
    createEmail(&returnbodong, 0, 0, 0, 0, timestamp, subject, body, 0, 0, 0);
    return returnbodong;
}