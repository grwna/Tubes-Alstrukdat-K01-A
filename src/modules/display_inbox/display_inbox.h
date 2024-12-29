#include "../mesin_kata/mesinkata.h"
#include "../utility/boolean.h"
#include "../utility/string.h"
#include "../email_list/email_list.h"
#include "../user/user.h"
#include "../inisiasi/inisiasi.h"
#include "../encryption/encryption.h"
#include "../search/search.h"
#include "../reply/reply.h"

/* membentuk EMAILID yang valid */
void createID (String id, int i);

/* print string (dalam bentuk "text") berwarna merah pada terminal */
void printAsRed (char *str);

/* menampilkan display inbox pada terminal*/
void displayInbox();

/* menampilkan display starred inbox pada terminal */
void displayStarred();

/* menampilkan display isi inbox yang mengandung subkata pencarian pada terminal */
void displaySearchResult(char *keyword);

/* menampilkan display email (input baca pesan) pada terminal */
void bacaPesan(int id, boolean header, boolean dekripsi);

/* menyalakan star pada email */
void setAsStarred(int id);

/* mematikan star pada email */
void setAsUnstarred(int id);
