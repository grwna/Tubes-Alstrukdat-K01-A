#include "string.h"
#include <stdio.h>

void createString(char *s) {
    s[0] = '\0';
}

int stringLength(char *s) {
    int i = 0;
    while(s[i] != '\0') {
        i++;
    }
    return i;
}

boolean isEmpty_String(char *s) {
    return stringLength(s) == 0;
}

boolean isFull_String(char *s, size_t size) {
    return stringLength(s) == size;
}

boolean isStringEqual(char *str1, char *str2) {
    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0') {
        if(str1[i] != str2[i]) {
            return false;
        }
        i++;
    }
    return str1[i] == str2[i];
}

void assignString(char *s, size_t size, char *str) {
    int i = 0;
    while(str[i] != '\0' && i <= size) {
        s[i] = str[i];
        i++;
    }
    if(i > size) {
        error_code = 302;
        createString(s);
        return;
    }
    s[i] = '\0';
}

void appendString(char *s, size_t size, char *str) {
    int i = stringLength(s);
    int j = 0;
    while(str[j] != '\0' && i <= size) {
        s[i] = str[j];
        i++;
        j++;
    }
    if(i > size) {
        error_code = 302;
        createString(s);
        return;
    }
    s[i] = '\0';
}

void appendChar(char *s, size_t size, char c) {
    int i = stringLength(s);
    if(i >= size) {
        error_code = 302;
        createString(s);
        return;
    }
    s[i] = c;
    s[i+1] = '\0';
}

void printString(char* str) {
    printf("%s", str);
}

int stringToInteger(char *s) {
    int i = 0;
    int result = 0, neg_mult = 1;
    if(s[i] == '-'){
        i++;
        neg_mult = -1;
    }
    while(s[i] != '\0' && s[i] >= '0' && s[i] <= '9') {
        result = result * 10 + (s[i] - '0');
        i++;
    }
    if(s[i] != '\0') {
        error_code = 303;
        return -1;
    }
    return result*neg_mult;
}

