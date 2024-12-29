#include "inisiasi.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef _WIN32
    #include <direct.h>
    #define MAKE_DIR(path) mkdir(path)
#else
    #define MAKE_DIR(path) mkdir(path, 0777)
#endif


int paginationLimit;
int importantLimit;

boolean isFolderExists(char *folderName) {
    struct stat info;

    if (stat(folderName, &info) == 0 && S_ISDIR(info.st_mode)) {
        // Folder exists and is a directory
        return true;
    }
    return false;
}

void loadConfigPengguna(char *dir){
    initUserList();
    STARTFILELINE(dir);
    int userCount = stringToInteger(currentWord.TabWord);
    if(userCount < 0 || userCount > 20 || error_code != 0){
        error_code = 301;
        return;
    }
    int currentUserId;
    String currentUserEmail, currentPassword;
    StarredList StarredList;
    
    while(userCount-- && !EOP_FILE && error_code == 0){
        // user ID
        ADVLINE();
        currentUserId = stringToInteger(currentWord.TabWord);
        if(EOP_FILE || error_code != 0 || currentUserId -1 != NEFF_UserList(users)){
            error_code = 301;
            break;
        }

        // user email
        ADVLINE();
        assignString(currentUserEmail, SIZE(currentUserEmail), currentWord.TabWord);
        if(EOP_FILE || error_code != 0 || !isUserEmailValid(currentUserEmail)){
            error_code = 301;
            break;
        }

        // user password
        ADVLINE();
        assignString(currentPassword, SIZE(currentPassword), currentWord.TabWord);
        if(error_code != 0 && !isPasswordValid(currentPassword)){
            error_code = 301;
            break;
        }

        // user jumlah email starred
        ADVLINE();
        int length = stringToInteger(currentWord.TabWord);   
        if(error_code != 0){
            error_code = 301;
        }
        createStarredList(&StarredList, length+5);
        NEFF_StarredList(StarredList) = length;

        // user starred email
        for (int i = 0; i < length; i++) {
            ADVLINE();
            ELMT_StarredList(StarredList, i) = stringToInteger(currentWord.TabWord);
        }

        addUser(currentUserEmail, currentPassword, StarredList); 
        deallocateStarredList(&StarredList);
        for(int i = 0; i < 24; i++){
            if(EOP_FILE){
                error_code = 301;
                return;
            }
            ADVLINE();
            if(stringLength(currentWord.TabWord) != 7){
                error_code = 301;
                return;
            }
            for(int j = 0; j < stringLength(currentWord.TabWord); j++){
                if(currentWord.TabWord[j] != '0' && currentWord.TabWord[j] != '1'){
                    error_code = 301;
                    return;
                }
                if(currentWord.TabWord[j] == '0'){
                    setFree(&ELMT_UserList(users, NEFF_UserList(users)-1), j, i);
                }
            }
        }
    }
    
    IgnoreBlanks();
    if(EOP_FILE && userCount > 0){
        error_code = 301;
    }

    // printUserList(users);
}

void loadConfigEmail(char *dir){
    STARTFILELINE(dir);
    int emailCount = stringToInteger(currentWord.TabWord);
    if(emailCount < 0 || error_code != 0){
        error_code = 301;
        return;
    }
    deallocateList(&AllEmails);
    createEmailList(&AllEmails, emailCount+10);
    MasterTree = newTree(-1);
    Email currentEmail;
    int emailId, fromUserId, toUserId, ccUserId;
    String subject, body;
    datetime timestamp;
    int isAReplyTo;
    boolean isRead, isCCRead;
    initStatusImportance(&AllStatusImportance, listLength_UserList(users));

    while(emailCount-- && !EOP_FILE){
        ADVLINE();
        emailId = stringToInteger(currentWord.TabWord);
        if(EOP_FILE || error_code != 0 || emailId - 1 != NEFF_EmailList(AllEmails)){
            error_code = 301;
            break;
        }

        ADVLINE();
        fromUserId = stringToInteger(currentWord.TabWord);
        if(EOP_FILE || error_code != 0){
            error_code = 301;
            break;
        }
     
        ADVLINE();
        toUserId = stringToInteger(currentWord.TabWord);
        if(EOP_FILE || error_code != 0){
            error_code = 301;
            break;
        }
      
        ADVLINE();
        ccUserId = stringToInteger(currentWord.TabWord);
        if(EOP_FILE || error_code != 0){
            error_code = 301;
            break;
        }
        
        updateImportance(&AllStatusImportance, fromUserId, toUserId, ccUserId);
        
        ADVLINE();
        String timestampString;
        assignString(timestampString, SIZE(timestampString), currentWord.TabWord);
        timestamp = readDateTimefromString(timestampString);
        if(EOP_FILE || error_code != 0){
            error_code = 301;
            break;
        }

        ADVLINE();
        assignString(subject, SIZE(subject), currentWord.TabWord);
        if(EOP_FILE || error_code != 0){
            error_code = 301;
            break;
        }

        ADVLINE();
        assignString(body, SIZE(body), currentWord.TabWord);
        while(currentWord.TabWord[currentWord.Length-1] == '\n'){
            ADVLINE();
            appendString(body, SIZE(body), currentWord.TabWord);
            if(EOP_FILE || error_code != 0){
                error_code = 301;
                break;
            }
        }

        if(EOP_FILE || error_code != 0){
            error_code = 301;
            break;

        }
      
        ADVLINE();
        isAReplyTo = stringToInteger(currentWord.TabWord);
        if(EOP_FILE || error_code != 0){
            error_code = 301;
            break;
        }

        ADVLINE();
        if(EOP_FILE || (stringToInteger(currentWord.TabWord) < 0 && stringToInteger(currentWord.TabWord) > 1)){ // 0 or 1
            error_code = 301;
            break;
        }
        isRead = stringToInteger(currentWord.TabWord);

        ADVLINE();
        if(stringToInteger(currentWord.TabWord) < 0 && stringToInteger(currentWord.TabWord) > 1){ // 0 or 1
            error_code = 301;
            break;
        }
        isCCRead = stringToInteger(currentWord.TabWord);

        createEmail(&currentEmail, 
                    emailId, 
                    fromUserId, 
                    toUserId, 
                    ccUserId, 
                    timestamp, 
                    subject, 
                    body, 
                    isAReplyTo,
                    isRead, 
                    isCCRead);
        addEmail(currentEmail);
    }
    // displayStatus(AllStatusImportance);
    IgnoreBlanks();
    if((EOP_FILE && emailCount > 0) || !EOP_FILE){
        error_code = 301;
        CLOSE();
    }
    if(error_code){
        deallocateList(&AllEmails);
        CLOSE();
    }

    assignEmailsToMasterTree();
    // printTree(MasterTree, 0);
}

void loadConfigUmum(char *dir){
    STARTFILELINE(dir);
    paginationLimit = stringToInteger(currentWord.TabWord);
    if(error_code != 0 || paginationLimit <= 0){
        return;
    }
    ADVLINE();
    
    importantLimit = stringToInteger(currentWord.TabWord);
    if(error_code != 0 || importantLimit < 0){
        return;
    }
    IgnoreBlanks();
    if(!EOP_FILE){
        error_code = 301;
        CLOSE();
    }
}

void saveConfigPengguna(char *dir){
    FILE *f = fopen(dir, "w");
    if(f == NULL){
        error_code = 202;
        return;
    }
    fprintf(f, "%d\n", listLength_UserList(users));
    for(int i = 0; i < listLength_UserList(users); i++){
        fprintf(f, "%d\n", ID_User(ELMT_UserList(users, i)));
        fprintf(f, "%s\n", EMAIL_User(ELMT_UserList(users, i)));
        fprintf(f, "%s\n", PASSWORD_User(ELMT_UserList(users, i)));
        fprintf(f, "%d\n", NEFF_StarredList(STARREDLIST_User(ELMT_UserList(users, i))));
        for(int j = 0; j < NEFF_StarredList(STARREDLIST_User(ELMT_UserList(users, i))); j++){
            fprintf(f, "%d\n", ELMT_StarredList(STARREDLIST_User(ELMT_UserList(users, i)), j));
        }
      
        for(int k = 0; k < 7; k++){
            fprintf(f, "%d", isBusy(ELMT_UserList(users, i), k, 0));
        }
        for(int j = 1; j < 24; j++){
            fprintf(f, "\n");
            for(int k = 0; k < 7; k++){
                fprintf(f, "%d", isBusy(ELMT_UserList(users, i), k, j));
            }
        }
        if(i < listLength_UserList(users) - 1){
            fprintf(f, "\n");
        }
    }
    fclose(f);
}

void saveConfigEmail(char *dir){
    FILE *f = fopen(dir, "w");
    if(f == NULL){
        error_code = 202;
        return;
    }
    fprintf(f, "%d\n", listLength_EmailList(AllEmails));
    for(int i = 0; i < listLength_EmailList(AllEmails); i++){
        fprintf(f, "%d\n", ID_Email(ELMT_EmailList(AllEmails, i)));
        fprintf(f, "%d\n", FROM_Email(ELMT_EmailList(AllEmails, i)));
        fprintf(f, "%d\n", TO_Email(ELMT_EmailList(AllEmails, i)));
        fprintf(f, "%d\n", CC_Email(ELMT_EmailList(AllEmails, i)));
        String timestampString;
        setDateTimeasStringConfig(timestampString, TIMESTAMP_Email(ELMT_EmailList(AllEmails, i)));
        fprintf(f, "%s\n", timestampString);
        fprintf(f, "%s\n", SUBJECT_Email(ELMT_EmailList(AllEmails, i)));
        int j = 0;
        while(BODY_Email(ELMT_EmailList(AllEmails, i))[j] != '\0'){
            if(BODY_Email(ELMT_EmailList(AllEmails, i))[j] == '\n'){
                fprintf(f, "\\");
            }
            fprintf(f, "%c", BODY_Email(ELMT_EmailList(AllEmails, i))[j]);
            j++;
        }
        fprintf(f, "\n%d\n", REPLY_Email(ELMT_EmailList(AllEmails, i)));
        fprintf(f, "%d\n", ISREAD_Email(ELMT_EmailList(AllEmails, i)));
        fprintf(f, "%d", CCREAD_Email(ELMT_EmailList(AllEmails, i)));
        if(i < listLength_EmailList(AllEmails) - 1){
            fprintf(f, "\n");
        }
    }
    fclose(f);
}

void saveConfigUmum(char *dir){
    FILE *f = fopen(dir, "w");
    if(f == NULL){
        error_code = 202;
        return;
    }
    fprintf(f, "%d\n", paginationLimit);
    fprintf(f, "%d", importantLimit);
    fclose(f);
}

void saveConfigToFolder(char *folderName) {
    String folderPath;
    assignString(folderPath, SIZE(folderPath), "config/");
    appendString(folderPath, SIZE(folderPath), folderName);
    if(!isFolderExists(folderPath)){
        printf("Folder %s tidak ditemukan, membuat folder baru...\n", folderName);
        MAKE_DIR(folderPath);
        printf("Folder %s berhasil dibuat.\n", folderName);
    }
    String filePath;
    // Create the path for pengguna.config
    assignString(filePath, SIZE(filePath), folderPath);
    appendString(filePath, SIZE(folderPath), "/pengguna.config");
    saveConfigPengguna(filePath);
    if(error_code != 0){
        return;
    }

    // Create the path for email.config
    assignString(filePath, SIZE(filePath), folderPath);
    appendString(filePath, SIZE(folderPath), "/email.config");
    saveConfigEmail(filePath);
    if(error_code != 0){
        return;
    }

    // Create the path for umum.config
    assignString(filePath, SIZE(filePath), folderPath);
    appendString(filePath, SIZE(folderPath), "/umum.config");
    saveConfigUmum(filePath);
    if(error_code != 0){
        return;
    }

    printf("Konfigurasi berhasil disimpan di folder %s\n", folderName);
}

boolean isFolderNameValid(char* folderName){
    for(int i = 0; folderName[i] != '\0'; i++){
        if((folderName[i] >= 'a' && folderName[i] <= 'z')  || (folderName[i] >= 'A' && folderName[i] <= 'Z') || (folderName[i] >= '0' && folderName[i] <= '9') || folderName[i] == '_' || folderName[i] == '-'){
            continue;
        } else {
            return false;
        }
    }
    return true;
}