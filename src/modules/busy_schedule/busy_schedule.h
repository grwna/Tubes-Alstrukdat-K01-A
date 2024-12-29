#ifndef BUSY_SCHEDULE_H
#define BUSY_SCHEDULE_H

#include "../user/user.h"

/* Membuat jadwal kosong untuk pengguna */
void createBusySchedule(User *user, int days, int hours);
/* I.S. user terdefinisi */
/* F.S. Matriks busy schedule pada user diinisialisasi dengan ukuran days x hours, semua elemen bernilai 1 (sibuk) */

/* Menandai waktu tertentu sebagai sibuk */
void setBusy(User *user, int day, int hour);
/* I.S. user terdefinisi, day dan hour valid dalam rentang matriks */
/* F.S. Elemen busy schedule user di [day][hour] diatur menjadi 1 (sibuk) */

/* Menandai waktu tertentu sebagai kosong */
void setFree(User *user, int day, int hour);
/* I.S. user terdefinisi, day dan hour valid dalam rentang matriks */
/* F.S. Elemen busy schedule user di [day][hour] diatur menjadi 0 (kosong) */

/* Mengecek apakah waktu tertentu sibuk */
boolean isBusy(User user, int day, int hour);
/* Mengembalikan true jika elemen busy schedule di [day][hour] bernilai 1 (sibuk) */

/* Melihat jadwal pengguna */
void viewOwnSchedule();
/* I.S. Pengguna telah login */
/* F.S. Jadwal pengguna ditampilkan dalam format tabel (24x7) */

/* Melihat jadwal pengguna lain */
void viewOtherUserSchedule();
/* I.S. inputEmail terdefinisi */
/* F.S. Jadwal pengguna dengan email inputEmail ditampilkan dalam format tabel (24x7) */

/* Menampilkan jadwal pengguna */
void printSchedule(User user);
/* I.S. user terdefinisi */
/* F.S. Jadwal pengguna ditampilkan dalam format tabel (7x24) */

/* Mengubah jadwal pengguna berdasarkan input */
void updateSchedule();
/* I.S. user terdefinisi */
/* F.S. Jadwal pengguna diperbarui berdasarkan input string multi-baris, dengan format '*' (sibuk) dan '.' (kosong) */

/* Menggabungkan jadwal pengguna */
void scheduleUsers();
/* I.S. Pengguna telah login */
/* F.S. Jadwal pengguna yang sedang login digabungkan dengan jadwal pengguna lain berdasarkan input email */

#endif