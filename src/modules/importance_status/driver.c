#include <stdio.h>
#include "importanceStatus.h"

int main() {
    // Deklarasi Status Importance dan jumlah pengguna
    StatusImportance status;
    int userCount = 5; // Jumlah pengguna (ID: 0-4)

    // Inisialisasi matriks status kepentingan
    initStatusImportance(&status, userCount);
    printf("Initial Status Importance Matrix:\n");
    displayStatus(status);
    printf("\n");

    // Case 1: User 0 sends an email to User 1 and User 2
    printf("[CASE 1] User 1 sends an email to User 2 and cc to User 3:\n");
    updateImportance(&status, 1, 2, 3);
    displayStatus(status);
    printf("\n");

    // Case 2: User 1 replies to User 0 and cc to User 3
    printf("[CASE 2] User 2 replies to User 1 and cc to User 4:\n");
    updateImportance(&status, 2, 1, 4);
    displayStatus(status);
    printf("\n");

    // Case 3: User 3 sends an email to User 4 only
    printf("[CASE 3] User 3 sends an email to User 4:\n");
    updateImportance(&status, 3, 4, -1);
    displayStatus(status);
    printf("\n");

    // Case 4: User 4 replies to User 3, no cc
    printf("[CASE 4] User 4 replies to User 3:\n");
    updateImportance(&status, 4, 3, -1);
    displayStatus(status);
    printf("\n");

    // Case 5: User 2 sends an email to User 0 and cc to User 4
    printf("[CASE 5] User 3 sends an email to User 1 and cc to User 5:\n");
    updateImportance(&status, 3, 1, 5);
    displayStatus(status);
    printf("\n");

    return 0;
}
