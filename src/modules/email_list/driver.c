#include "email_list.h"
#include <stdio.h>

int main(){
    createEmailList(&AllEmails, 20);
    createEmailList(&inbox, 10);
    Email email;
    datetime timestamp;
    readDateTime(&timestamp);
    String subject;
    assignString(subject, SIZE(subject), "subject");
    String body;
    assignString(body, SIZE(body), "body");
    for (int i = 0; i < 10; i++){
        createEmail(&email,
                    i+1,
                    i,
                    i+1,
                    -1,
                    timestamp,
                    subject,
                    body,
                    -1,
                    false,
                    false);
        insertLast_EmailList(&AllEmails, email);
    }
    for (int i = 0; i < 10; i++){
        createEmail(&email,
                    i+11,
                    i+1,
                    i,
                    -1,
                    timestamp,
                    subject,
                    body,
                    -1,
                    false,
                    false);
        insertLast_EmailList(&AllEmails, email);
    }
    currentUserId = 2;
    getInbox();
    printf("inbox length = %d\n", listLength_EmailList(inbox));
    printEmailList(inbox);
    printf("===\n");
    printEmailList(AllEmails);
    deallocateList(&AllEmails);
    deallocateList(&inbox);
    return 0;
}   
