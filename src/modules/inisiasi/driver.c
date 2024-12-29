#include "inisiasi.h"
#include <stdio.h>

int main(){
    CreateUserList(&users);
    loadConfigPengguna("./../../../config/config1/pengguna.config");
    loadConfigUmum("./../../../config/config1/umum.config");
    printf("paginationLimit: %d\n", paginationLimit);
    printf("importanceLimit: %d\n", importantLimit);
    loadConfigEmail("./../../../config/config1/email.config");
    printUserList(users);
    printEmailList(AllEmails);
    printf("paginationLimit: %d\n", paginationLimit);
    printf("importanceLimit: %d\n", importantLimit);
    return 0;
}

