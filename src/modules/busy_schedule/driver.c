#include <stdio.h>
#include "busy_schedule.h"
#include "../user/user.h"
#include "../utility/error_handler.h"
#include "../utility/string.h" // Pastikan string.h yang benar digunakan

int main() {
    CreateUserList(&users);

    User user1;
    StarredList star;
    createStarredList(&star, 5);
    NEFF_StarredList(star) = 1;
    ELMT_StarredList(star, 0) = 1;
    String email;
    assignString(email, SIZE(email), "purry@ow.ca");
    String password;
    assignString(password, SIZE(password), "P@ssw0Rd");
    addUser(email, password, star);

    // User user2;
    // createUser(&user2, "alstrukdat@itb.ac.id", "P@ssw0RdH3H3");
    // insertLast_UserList(&users, user2);

    // User user3;
    // createUser(&user3, "akuaku@ow.ca", "P@ssw0Rd");
    // insertLast_UserList(&users, user3);

    printf("Login sebagai pengguna pertama: purry@ow.ca\n");
    userLogin(ELMT_UserList(users, 0).id);

    // Menampilkan jadwal pengguna pertama
    printf("\nJadwal awal pengguna pertama:\n");
    viewOwnSchedule();

    // Memperbarui jadwal pengguna pertama
    printf("\nMemperbarui jadwal pengguna pertama:\n");
    updateSchedule(&ELMT_UserList(users, currentUserId-1));

    // Menampilkan jadwal pengguna pertama setelah diperbarui
    printf("\nJadwal setelah diperbarui pengguna pertama:\n");
    viewOwnSchedule();

    // Logout pengguna pertama
    userLogout();
    printf("\nLogout pengguna pertama.\n");

    // // Login sebagai pengguna kedua
    // printf("\nLogin sebagai pengguna kedua: alstrukdat@itb.ac.id\n");
    // userLogin(ELMT_UserList(users,1).id); // currentUserId = 1 (ID dari pengguna kedua)

    // Menampilkan jadwal pengguna kedua
    printf("\nJadwal awal pengguna kedua:\n");
    viewOwnSchedule();

    // // Memperbarui jadwal pengguna kedua
    // printf("\nMemperbarui jadwal pengguna kedua:\n");
    // updateSchedule(&ELMT_UserList(users, currentUserId-1));

    // Menampilkan jadwal pengguna kedua setelah diperbarui
    printf("\nJadwal setelah diperbarui pengguna kedua:\n");
    viewOwnSchedule();

    // // Logout pengguna kedua
    // userLogout();
    // printf("Logout pengguna kedua.\n");

    // // Login sebagai pengguna ketiga
    // printf("\nLogin sebagai pengguna ketiga: akuaku@ow.ca\n");
    // userLogin(ELMT_UserList(users,2).id); // currentUserId = 2 (ID dari pengguna

    // Menampilkan jadwal pengguna ketiga
    printf("\nJadwal awal pengguna ketiga:\n");
    viewOwnSchedule();

    // // Memperbarui jadwal pengguna ketiga
    // printf("\nMemperbarui jadwal pengguna ketiga:\n");
    // updateSchedule(&ELMT_UserList(users, currentUserId-1));

    // Menampilkan jadwal pengguna ketiga setelah diperbarui
    printf("\nJadwal setelah diperbarui pengguna ketiga:\n");
    viewOwnSchedule();

    // Menampilkan jadwal pengguna lain
    printf("\nJadwal pengguna lain:\n");
    viewOtherUserSchedule();
    

    // // Menggabungkan jadwal pengguna
    // printf("SCHEDULE ");
    // scheduleUsers();

    // // Logout pengguna ketiga
    // userLogout();
    // printf("Logout pengguna ketiga.\n");
    return 0;
}
