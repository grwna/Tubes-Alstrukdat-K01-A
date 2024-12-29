#include "mesinkata.h"

int main(){
    STARTFILELINE("./../../../config/pengguna.config");
    while(!EOP){
        printCurrentWord();
        ADVLINE();
    }   
    printCurrentWord();
}
