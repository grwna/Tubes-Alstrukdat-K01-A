# include "encryption.h"
# include <stdio.h>
# include <stdlib.h>

int main(){
    String body;
    createString(&body, 100);
    assignString(&body, SIZE(body), "Encrypt THIS!\nCekCekpola");
    printString(body);
    encrypt(&body);
    printString(body);
    decrypt(&body);
    printString(body);
    return 0;
}