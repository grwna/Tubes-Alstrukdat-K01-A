#ifndef INISIASI_H
#define INISIASI_H

#include "../utility/boolean.h"
#include "../utility/string.h"
#include "../mesin_kata/mesinkata.h"
#include "../email_list/email_list.h"
#include "../user/user.h"
#include "../busy_schedule/busy_schedule.h"
#include "../utility/error_handler.h"
#include "../reply/reply.h"
#include "../busy_schedule/busy_schedule.h"
#include "../importance_status/importanceStatus.h"
#include "../reply/reply.h"

extern int paginationLimit;
extern int importantLimit;

/* I.S. folderName terdefinisi
   F.S. return true jika folderName ada */
boolean isFolderExists(char *folderName);

/* I.S. dir terdefinisi
   F.S. load konfigurasi user/pengguna dari file konfigurasi */
void loadConfigPengguna(char *dir);

/* I.S. dir terdefinisi
   F.S. load konfigurasi email dari file konfigurasi */
void loadConfigEmail(char *dir);

/* I.S. dir terdefinisi
   F.S. load konfigurasi umum dari file konfigurasi */
void loadConfigUmum(char *dir);

/* I.S. dir terdefinisi
   F.S. save konfigurasi ke file konfigurasi */
void saveConfigPengguna(char *dir);

/* I.S. dir terdefinisi
   F.S. save konfigurasi ke file konfigurasi */
void saveConfigEmail(char *dir);

/* I.S. dir terdefinisi
   F.S. save konfigurasi ke file konfigurasi */
void saveConfigUmum(char *dir);

/* I.S. folder terdefinisi
   F.S. save konfigurasi ke folder */
void saveConfigToFolder(char *folder);

/* I.S. path terdefinisi
   F.S. return true jika folderName valid */
boolean isFolderNameValid(char *folderName);

#endif