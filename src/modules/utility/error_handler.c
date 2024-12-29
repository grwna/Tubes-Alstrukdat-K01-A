#include "error_handler.h"

int error_code;

void print_error(){
    switch(error_code){
        case 101: // 1__ : Memory Allocation
            printf("ERROR: Memory Allocation failure\n");
            break;
        case 201: // 2__ : Invalid Input
            printf("ERROR: Input invalid! (Input harus berupa integer)\n");            
            break;
        case 202:
            printf("ERROR: File tidak ditemukan.\n");
            break;
        case 301: // 3__ : Invalid Config
            printf("ERROR: Config Invalid.\n");
            break;
        case 302:
            printf("ERROR: Kapasitas String tidak cukup.\n");
            break;
        case 399:
            printf("ERROR: Input melebihi ekspektasi. Silakan coba lagi.\n");
            break;
    }
}