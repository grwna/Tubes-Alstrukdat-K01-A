#include "string.h"
#include <stdio.h>

int main(){
    String s;
    createString(s);
    printf("%d\n", stringLength(s));
    printf("%d\n", isEmpty_String(s));
    printf("%d\n", isFull_String(s, SIZE(s)));
    String str1;
    assignString(str1, SIZE(str1), "Hello");
    String str2;
    assignString(str2, SIZE(str2), "Hi!");
    printf("%d\n", isStringEqual(str1, str2));
    assignString(str2, SIZE(str2), "Hello");
    printf("equal: %d\n", isStringEqual(str1, str2));
    printString(str1);
    printf("\n");
    String str3;
    assignString(str3, SIZE(str3), "123");
    printf("%d\n", stringToInteger(str3));
    for(int i = 0;i<5;i++){
        currentWord.TabWord[i] = 'a' + i;
    }
    currentWord.Length = 5;
    LargeString ls;
    assignStringFromCurrentWord(ls, SIZE(ls));
    printString(ls);
    printf("\n");
    appendCurrentWordToString(ls, SIZE(ls));
    printString(ls);
    printf("\n");
    printf("length: %d\n", stringLength(ls));
    return 0;
}