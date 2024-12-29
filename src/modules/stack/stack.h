/* File : stack.h */
/* deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */
#ifndef stackt_H
#define stackt_H

#include "../utility/boolean.h"
#include "../utility/string.h"
#include "../datetime/datetime.h"
#include "../mesin_kata/mesinkata.h"
#include "../mesin_kata/mesinkarakter.h"
#include "../user/user.h"
#include "../email_list/email_list.h"
#include "../inisiasi/inisiasi.h"
#include "../utility/error_handler.h"

#define Nil -1 /* Nil adalah stack dengan elemen kosong . */
#define MaxEl 100 /* MaxEl adalah ukuran maksimum stack */

/*Tipe data untuk draft*/
typedef struct {
  String senderDraft;      /* Alamat email pengirim */ 
  String receiverDraft;    /* Alamat email penerima */
  String ccDraft;          /* Alamat email CC (bisa kosong atau satu email) */
  datetime timestampDraft; /* Waktu perubahan terakhir */
  String subjectDraft;     /* Subjek email */
  LargeString bodyDraft;   /* Isi email */
  int isAreplyDraft;
} EmailDraft;

typedef int address;   /* indeks tabel */

/* Contoh deklarasi variabel bertype stack dengan ciri TOP : */
/* Versi I : dengan menyimpan tabel dan alamat top secara eksplisit*/
typedef struct { 
  EmailDraft T[MaxEl]; /* tabel penyimpan elemen */
  address TOP;  /* alamat TOP: elemen puncak */
} Stack;
/* Definisi stack S kosong : S.TOP = Nil */
/* Elemen yang dipakai menyimpan nilai Stack T[0]..T[MaxEl-1] */
/* Jika S adalah Stack maka akses elemen : */
   /* S.T[(S.TOP)] untuk mengakses elemen TOP */
   /* S.TOP adalah alamat elemen TOP */

/* Definisi akses dengan Selektor : Set dan Get */
#define Email(D) (D).emailDraft
#define Sender(D) (D).senderDraft
#define Receiver(D) (D).receiverDraft
#define CC(D) (D).ccDraft
#define TimeStamp(D) (D).timestampDraft
#define Subject(D) (D).subjectDraft
#define Body(D) (D).bodyDraft
#define ReplyDraft(D) (D).isAreplyDraft
#define Top(S) (S).TOP
#define InfoTop(S) (S).T[(S).TOP]

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmptyStack(Stack *S);
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 0.. MaxEl */
/* Ciri stack kosong : TOP bernilai Nil */

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyStack(Stack S);
/* Mengirim true jika Stack kosong: lihat definisi di atas */
boolean IsFullStack(Stack S);
/* Mengirim true jika tabel penampung nilai elemen stack penuh */

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void PushStack(Stack * S, EmailDraft X);
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */

/* ************ Menghapus sebuah elemen Stack ************ */
void PopStack(Stack * S, EmailDraft* X);
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */

void Undo(Stack *S, Stack *redoStack);
/* Melakukan Undo 1 perubahan sebelum, maksimalnya hingga draft kembali ke bentuk awal */

void Redo(Stack *redoStack, Stack *S2);
/* Melakukan Redo 1 perubahan setelah, maksimalnya hingga draft kembali ke bentuk akhir */

void PrintDraft(EmailDraft D);
/* Print draft */

void createDraft(EmailDraft *newDraft, String sender, String receiver, String cc, datetime timestamp, String subject, String body, int isAreplyto);

boolean isEmptyDraft (EmailDraft newDraft);

void BuatDraft(EmailDraft *newDraft, int *kelar, String sender);
/* Buat draft dengan ketentuan email harus ada di db, receiver harus ada di db */
/* Jika ada CC akan diteruskan, jika tidak, tidak perlu */

void addDraftToEmails(EmailList *l, EmailDraft *draft, int replyTo);

void createReplyEmail(Email parentEmail, EmailDraft *replyDraft);
/* Membuat email reply dalam bentuk draft*/

void kirimDraftEmail (EmailList *emailList, EmailDraft *draft);


#endif