#ifndef USER_H
#define USER_H

#include "../utility/boolean.h"
#include "../utility/string.h"
#include "../utility/error_handler.h"
#include "../matrix/matrix.h"

typedef struct
{
    int *buffer;    /* memori tempat penyimpan elemen (container) */
    int nEff;       /* >=0, banyaknya elemen efektif */
    int capacity;   /* ukuran elemen */
} StarredList;

#define NEFF_StarredList(l) (l).nEff
#define BUFFER_StarredList(l) (l).buffer
#define ELMT_StarredList(l, i) (l).buffer[i]
#define CAPACITY_StarredList(l) (l).capacity

typedef struct {
    int id;
    String userEmail;
    String password;
    Matrix schedule;
    StarredList starredEmailList;
} User; 

#define ID_User(user) (user).id
#define EMAIL_User(user) (user).userEmail
#define PASSWORD_User(user) (user).password
#define STARREDLIST_User(user) (user).starredEmailList
#define SCHEDULE_User(user) (user).schedule

/*  Kamus Umum */
#define CAPACITY_User 20
/* Kapasitas penyimpanan */
#define IDX_UNDEF -1
/* Indeks tak terdefinisi*/

typedef struct {
   User contents[CAPACITY_User]; /* memori tempat penyimpan elemen (container) */
   int nEff;
} UserList;
/* Indeks yang digunakan [0..CAPACITY-1] */
/* Jika l adalah UserList, cara deklarasi dan akses: */
/* Deklarasi : l : UserList */
/* Maka cara akses: 
   ELMT(l,i) untuk mengakses elemen ke-i */
/* Definisi : 
   List kosong: semua elemen bernilai MARK
   Definisi elemen pertama: ELMT(l,i) dengan i=0 */

extern int currentUserId;
extern UserList users;

/* ********** SELEKTOR ********** */
#define ELMT_UserList(l, i) (l).contents[i]
#define NEFF_UserList(l) (l).nEff

/* I.S. user sembarang 
   F.S. user terdefinisi dengan email dan passwordnya, id sesuai dengan panjang list */
void createUser(User *user, String userEmail, String password, StarredList StarredList);

/* Mengembalikan jumlah elemen pada list */
int listLength_UserList(UserList l);

/* I.S. l sembarang
   F.S. l terdefinisi, nEff(l) = 0 */
void CreateUserList(UserList *l);

/* Mengembalikan true jika list kosong */
boolean isEmpty_UserList(UserList l);

/* Mengembalikan true jika list penuh */
boolean isFull_UserList(UserList l);

/* Mengembalikan indeks elemen dengan email yang sama dengan email pada parameter */
int indexOf_UserList(UserList l, String userEmail);

/* I.S. l terdefinisi, mungkin kosong, tidak penuh.
   F.S. Menambahkan elemen baru pada posisi terakhir list */
void insertLast_UserList(UserList *l, User newUser);

/* Cek apakah email sesuai regex email */
boolean isUserEmailValid(String userEmail);

/* Cek apakah password sesuai regex password */
boolean isPasswordValid(String password);

/* I.S. UserList users sembarang
   F.S. UserList users terdefinisi, nEff = 0 */
void initUserList();

/* I.S. email valid, email belum terdaftar, list l tidak penuh.
   F.S. user baru terdaftar */
void addUser(String userEmail, String password, StarredList StarredList);

void createStarredList(StarredList *l, int capacity);
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list dinamis l kosong dengan kapasitas capacity */

void deallocateStarredList(StarredList *l);
/* I.S. l terdefinisi; */
/* F.S. (l) dikembalikan ke system, CAPACITY(l)=0; NEFF(l)=0 */

void expandStarredList(StarredList *l, int num);
/* Proses : Menambahkan capacity l sebanyak num */
/* I.S. List sudah terdefinisi */
/* F.S. Ukuran list bertambah sebanyak num */

void shrinkStarredList(StarredList *l, int num);
/* Proses : Mengurangi capacity sebanyak num */
/* I.S. List sudah terdefinisi, ukuran capacity > num, dan nEff < capacity - num. */
/* F.S. Ukuran list berkurang sebanyak num. */

void compressStarredList(StarredList *l);
/* Proses : Mengubah capacity sehingga nEff = capacity */
/* I.S. List tidak kosong */
/* F.S. Ukuran nEff = capacity */

/* cari id user dari email.
   user tidak ada, return -1 */
int findUserIdByEmail(String userEmail);

/* Cek apakah password user sesuai (berdasarkan user id) */
boolean isLoginValid(int id, String password);

/* I.S. currentUserId -1, id valid
   F.S. currentUserId = id */
void userLogin(int id);

/* I.S. currentUserId bukan -1
   F.S. currentUserId = -1 */
void userLogout();

/* I.S. l terdefinisisi
   F.S. print l */
void printUserList(UserList l);

#endif