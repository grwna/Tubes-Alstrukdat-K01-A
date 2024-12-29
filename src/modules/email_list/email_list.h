/* MODUL INTEGER DYNAMIC LIST */
/* Berisi definisi dan semua primitif pemrosesan list integer */
/* Penempatan elemen selalu rapat kiri */

#ifndef EMAIL_LIST_H
#define EMAIL_LIST_H

#include "../utility/boolean.h"
#include "../utility/string.h"
#include "../datetime/datetime.h"
#include "../user/user.h"
#include <stdlib.h>

/*  Kamus Umum */
#define IDX_MIN 0
/* Indeks minimum list */
#define IDX_UNDEF -1
/* Indeks tak terdefinisi*/

/* Definisi elemen dan koleksi objek */
typedef struct {
   int id;              /* id email */
   int fromUserId;      /* id pengirim */
   int toUserId;        /* id penerima */
   int ccUserId;        /* id penerima cc, -1 jika tidak ada penerima cc. */
   datetime timestamp;  /* waktu pengiriman */
   String subject;      /* subjek email */
   LargeString body;    /* isi email */
   int isAReplyTo;      /* id email yang di-reply, -1 jika bukan reply. */
   boolean isRead;      /* status email dibaca */
   boolean ccRead;      /* status email cc dibaca */
} Email; 

#define ID_Email(E) (E).id
#define FROM_Email(E) (E).fromUserId
#define TO_Email(E) (E).toUserId
#define CC_Email(E) (E).ccUserId
#define BODY_Email(E) (E).body
#define TIMESTAMP_Email(E) (E).timestamp
#define SUBJECT_Email(E) (E).subject
#define REPLY_Email(E) (E).isAReplyTo
#define ISREAD_Email(E) (E).isRead
#define CCREAD_Email(E) (E).ccRead

typedef int IdxType;
typedef struct
{
    Email *buffer; /* memori tempat penyimpan elemen (container) */
    int nEff;       /* >=0, banyaknya elemen efektif */
    int capacity;   /* ukuran elemen */
} EmailList;
/* Indeks yang digunakan [0..capacity-1] */
/* Jika l adalah : EmailList, cara deklarasi dan akses: */
/* Deklarasi : l : EmailList */
/* Maka cara akses:
   l.nEff      untuk mengetahui banyaknya elemen
   l.buffer    untuk mengakses seluruh nilai elemen list
   l.buffer[i] untuk mengakses elemen ke-i */
/* Definisi :
  list kosong: l.nEff = 0
  Definisi elemen pertama : l.buffer[i] dengan i=0
  Definisi elemen terakhir yang terdefinisi: l.buffer[i] dengan i=l.capacity */

extern EmailList AllEmails;
extern EmailList inbox;
extern EmailList starred;
extern EmailList searchResult;

/* ********** SELEKTOR ********** */
#define NEFF_EmailList(l) (l).nEff
#define BUFFER_EmailList(l) (l).buffer
#define ELMT_EmailList(l, i) (l).buffer[i]
#define CAPACITY_EmailList(l) (l).capacity

/* ********** KONSTRUKTOR ********** */
/* I.S. email sembarang
   F.S. email terdefinisi */
void createEmail(Email *email, 
                 int emailId, 
                 int fromUserId, 
                 int toUserId, 
                 int ccUserId, 
                 datetime timestamp, 
                 String subject, 
                 String body, 
                 int isAReplyTo, 
                 boolean isRead, 
                 boolean ccRead);

/* Konstruktor : create list kosong  */

/* I.S. l sembarang, capacity > 0
   F.S. Terbentuk list dinamis l kosong dengan kapasitas capacity */
void createEmailList(EmailList *l, int capacity);

/* I.S. l terdefinisi
   F.S. l dikembalikan ke system, CAPACITY(l)=0; NEFF(l)=0 */
void deallocateList(EmailList *l);

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */

/* Mengirimkan banyaknya elemen efektif list
   Mengirimkan nol jika list l kosong */
int listLength_EmailList(EmailList l);

/* ********** TEST KOSONG/PENUH ********** */

/* Mengirimkan true jika list l kosong, mengirimkan false jika tidak */
boolean isEmpty_EmailList(EmailList l);

/* Mengirimkan true jika list l penuh, mengirimkan false jika tidak */
boolean isFull_EmailList(EmailList l);

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */

/* *** Menambahkan elemen terakhir *** */

/* I.S. List l boleh kosong, tetapi tidak penuh
   F.S. val adalah elemen terakhir l yang baru */
void insertLast_EmailList(EmailList *l, Email newEmail);

/* ********* MENGUBAH UKURAN ARRAY ********* */

/* Proses : Menambahkan capacity l sebanyak num
   I.S. List sudah terdefinisi
   F.S. Ukuran list bertambah sebanyak num */
void expandList(EmailList *l, int num);

/* Proses : Mengurangi capacity sebanyak num
   I.S. List sudah terdefinisi, ukuran capacity > num, dan nEff < capacity - num.
   F.S. Ukuran list berkurang sebanyak num. */
void shrinkList(EmailList *l, int num);

/* Proses : Mengubah capacity sehingga nEff = capacity
   I.S. List tidak kosong
   F.S. Ukuran nEff = capacity */
void compressList(EmailList *l);

/* ********** PROSES SEMUA ELEMEN LIST ********** */

/* I.S. AllEmails terdefinisi, mungkin kosong, mungkin penuh.
   F.S. Menambahkan email ke AllEmails. */  
void addEmail(Email newEmail);

/* I.S. AllEmails terdefinisi.
   F.S. Mengisi Inbox dengan email yang menuju ke user dengan id = currentUserId.*/
void getInbox();

/* I.S. AllEmails terdefinisi.
   F.S. Mengisi Starred dengan email yang bintangnya = 1.*/
void getStarred();

/* menampilkan seluruh email list pada terminal */
void printEmailList(EmailList l);

// /* mengurutkan email list berdasarkan urutan waktu (tidak membentuk email list baru) */
// void sortEmailListbyTime(EmailList *l);

// /* mencari email berdasarkan email id*/
// Email getEmailbyID(int id);

#endif