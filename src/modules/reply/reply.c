#include "reply.h"

Tree MasterTree;

void createMasterTree() {
    MasterTree = newTree(MASTER);
}

void assignEmailsToMasterTree(){
    for(int i = 0; i < AllEmails.nEff; i++){
        addChildTree(getSubtreeByID(AllEmails.buffer[i].isAReplyTo), AllEmails.buffer[i].id);
    }
}

// void createReplyEmail(Email parentEmail, EmailDraft *replyDraft){
//     SubTree parent = getSubtreeByID(ID_Email(parentEmail));
//     Tree ancestry = getLineageTree(parent);
//     int re = getHeightTree(ancestry) - 1;

//     //TURNSTRING
//     String senderEmailString;
//     assignString(senderEmailString, SIZE(senderEmailString), ELMT_UserList(users, FROM_Email(parentEmail)-1).userEmail);
//     String receiverString;
//     assignString(receiverString, SIZE(receiverString), ELMT_UserList(users, TO_Email(parentEmail)-1).userEmail);
//     String ccString;
//     assignString(ccString, SIZE(ccString), ELMT_UserList(users, CC_Email(parentEmail)-1).userEmail);
//     String subject;
  
//     assignString(subject, SIZE(subject), "Re[");
//     String temp;
//     createString(temp);
//     if (re == 0) {
//         appendChar(temp, SIZE(temp), '0'); 
//     } else {
//         int number = re;
//         while (number > 0) {
//             appendChar(temp, SIZE(temp), (number % 10) + '0');
//             number /= 10;
//         }
//     }
//     for (int j = stringLength(temp) - 1; j >= 0; j--) {
//         appendChar(subject, SIZE(subject), temp[j]);
//     }

//     appendString(subject, SIZE(subject), ']: ');
//     appendString(subject, SIZE(subject), SUBJECT_Email(parentEmail));
  
//     LargeString body;

//     printf("Masukkan Email Penerima: ");
//     printString(receiverString);
//     printf("Masukkan Penerima Cc: ");
//     printString(ccString);
//     printf("Masukkan Subjek: ");
//     printString(subject);

//     while(true){
//         printf("Masukkan Body: ");
//         STARTBLOCK();
//         assignString(body, SIZE(body), currentWord.TabWord);

//         if (isEmpty_String(body)){
//             printf("Input tidak valid!\n\n\n");
//         }
//         else{
//             break;
//         }
//     }

//     datetime t; 
//     readDateTime(&t);
//     createDraft(replyDraft, senderEmailString, receiverString, ccString, t, subject, body, ID_Email(parentEmail));
// }

void addReplyToTree(Email reply){
    Tree parent = getAddressByInfoTree(MasterTree, REPLY_Email(reply));
    addChildTree(parent, ID_Email(reply));
}

SubTree getSubtreeByID(int ID){
    return getAddressByInfoTree(MasterTree, ID);
}