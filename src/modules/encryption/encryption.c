# include "encryption.h"
# include <time.h>
# include <stdio.h>
# include <stdlib.h>

Key plain = {
    .upper = {65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90},
    .lower = {97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122}
};

void encrypt(LargeString body){
    Key encrypt = generateKey();
    for(int i = 0; i < stringLength(body); i++){
        int index = indexOf_encryption(plain, body[i]);
        if(index > -1){
            if(body[i] >= 'A' && body[i] <= 'Z'){
                body[i] = encrypt.upper[index];
            }
            else{
                body[i] = encrypt.lower[index];
            }
        }
    }
    printSuccessMessage(encrypt);
    saveKey_encryption(encrypt);
}

void decrypt(LargeString body){
    Key decrypt;
    int success = loadKey_encryption(&decrypt);
    if(!success){
        return;
    }
    for(int i = 0; i < stringLength(body); i++){
        int index = indexOf_encryption(decrypt, body[i]);
        if(index > -1){
            if(body[i] >= 'A' && body[i] <= 'Z'){
                body[i] = plain.upper[index];
            }
            else if (body[i] >= 'a' && body[i] <= 'z'){
                body[i] = plain.lower[index];
            }
        }
    }

}

void printSuccessMessage(Key K){
    printf("Draft berhasil dienkripsi dengan kunci berikut:\n\n");
    for(int i = 0; i < 26; i++){
        printf("%c -> %c", plain.upper[i],K.upper[i]);
        printf("          ");
        printf("%c -> %c\n", plain.lower[i],K.lower[i]);
    }
    printf("\n");

}


int rng(){
    static int seed = 0;    // Static to retain after every calls
    if (seed == 0) seed = time(NULL);
    seed = ((A * seed + C) % M);
    if(seed < 0) seed *= -1;    // Negative numbers give unpredictable results
    return seed;
} 

Key generateKey(){
    // Ascii A-Z 65-90
    // Ascii a-z 97-122
    
    int i, ascii;
    Key used, key;

    for(i = 0; i < 26; i++) {
        used.upper[i] = 0;
        used.lower[i] = 0;
    }

    // A- Z
    for (i = 0; i < 26; i++){
        ascii = rng() % 26;
        while((used.upper[ascii])){
            ascii = (ascii + 1) % 26;
        }
        key.upper[i] = ascii + 65;
        used.upper[ascii] = 1;
    }
    // a-z
    for (i = 0; i < 26; i++){
        ascii = rng() % 26;
        while((used.lower[ascii])){
            ascii = (ascii + 1) % 26;
        }
        key.lower[i] = ascii + 97;
        used.lower[ascii] = 1;
    }

    return key;
}

/* ========= IO ===============*/
void saveKey_encryption(Key K){
    String path;
    assignString(path, SIZE(path), "config/key/");
    printf(">> Masukkan nama file untuk menyimpan kunci: ");
    STARTWORD();
    appendString(path, SIZE(path), currentWord.TabWord);
    
    FILE *f = fopen(path, "w");
    if(f == NULL){
        printf("Invalid file name\n");
        return;
    }
    for(int i = 0; i < 26; i++){
        fprintf(f, "%c", K.upper[i]);
    }
    for(int i = 0; i < 26; i++){
        fprintf(f, "%c", K.lower[i]);
    }
    printf("\nKunci berhasil disimpan.\n\n");
    fclose(f);
};

int loadKey_encryption(Key *decrypt){
    String path;
    assignString(path, SIZE(path), "config/key/");
    printf(">> Masukkan nama file kunci: ");
    STARTWORD();
    appendString(path, SIZE(path), currentWord.TabWord);

    // int counter = 0;
    STARTFILE(path);
    for (int i = 0; i < 26 && !EOP_FILE; i++) {
        decrypt->upper[i] = currentChar;
        if (currentChar < 'A' || currentChar > 'Z') {
            printf("File memuat karakter yang tidak valid!\n");
            printf("karakter yang tidak valid: %c\n", currentChar);
            return 0;
        }
        ADV();
    }
    for (int i = 0; i < 26 && !EOP_FILE; i++) {
        decrypt->lower[i] = currentChar;
        if (currentChar < 'a' || currentChar > 'z') {
            printf("File memuat karakter yang tidak valid!\n");
            printf("karakter yang tidak valid: %c\n", currentChar);
            return 0;
        }
        ADV();
    }

    if (!EOP_FILE) {
        printf("File bukan merupakan file kunci yang benar!\n");
        return 0;
    }
    return 1;
}

int indexOf_encryption(Key K, int val){
    for(int i = 0; i < 26; i++){
        if(K.upper[i] == val) return i;
        if(K.lower[i] == val) return i;
    }
    return -1;
}