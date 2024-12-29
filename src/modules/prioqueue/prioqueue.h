/* File : prioqueue.h */
/* Definisi ADT Priority Queue terurut mengecil berdasarkan nilai elemen */

#ifndef PRIOQUEUE_H
#define PRIOQUEUE_H

#include "../utility/boolean.h"
#include "../utility/string.h"
#include "../datetime/datetime.h"
#include "../mesin_kata/mesinkata.h"
#include "../mesin_kata/mesinkarakter.h"
#include "../user/user.h"
#include "../email_list/email_list.h"
#include "../inisiasi/inisiasi.h"
#include "../utility/error_handler.h"
#include "../matrix/matrix.h"
#include "../importance_status/importanceStatus.h"


#define IDX_UNDEF -1
#define CAPACITY 100


/* Definisi tipe data notifikasi */
typedef struct {
    datetime waktu;       // Informasi waktu email
    boolean importance;  // Status kepentingan (true untuk penting, false untuk biasa)
    String subject;      // Subjek email
} Notif;

/* Definisi elemen dan address */
typedef struct {
    Notif buffer[CAPACITY]; // Buffer menyimpan elemen Notif
    int idxHead;
    int idxTail;
} PrioQueue;


/* ********* AKSES (Selektor) ********* */
/* Jika q adalah Queue dan N adalah ElType notifikasi, maka akses elemen : */
#define    WAKTU(N) (N).waktu
#define IMPORTANCE(N) (N).importance
#define  SUBJECT(N) (N).subject
#define IDX_HEAD(Q) (Q).idxHead
#define IDX_TAIL(Q) (Q).idxTail
#define     HEAD(Q) (Q).buffer[(Q).idxHead]
#define     TAIL(Q) (Q).buffer[(Q).idxTail]

/* *** Kreator *** */
void CreatePrioQueue(PrioQueue *Q);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dengan kondisi sbb: */
/* - Index head bernilai IDX_UNDEF */
/* - Index tail bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */

/* ********* Prototype ********* */
boolean isEmptyPrio(PrioQueue Q);
/* Mengirim true jika Q kosong: lihat definisi di atas */
boolean isFullPrio(PrioQueue Q);
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu IDX_TAIL akan selalu di belakang IDX_HEAD dalam buffer melingkar*/

int lengthPrio(PrioQueue Q);
/* Mengirimkan banyaknya elemen prioqueue. Mengirimkan 0 jika Q kosong. */

/* *** Primitif Add/Delete *** */
void enqueuePrio(PrioQueue *Q, Notif val);
/* Proses: Menambahkan val pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. val disisipkan pada posisi yang sesuai, IDX_TAIL "mundur" dalam buffer melingkar.,
        Q terurut mengecil */

void dequeuePrio(PrioQueue *Q, Notif *val);
/* Proses: Menghapus val pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. val = nilai elemen HEAD pd I.S., IDX_HEAD "mundur";
        Q mungkin kosong */

/* *** Display Queue *** */
void displayPrioQueue(PrioQueue Q);
/* Proses : Menuliskan isi PrioQueue dengan traversal, PrioQueue ditulis di antara kurung 
   siku; antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan 
   karakter di depan, di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. Q boleh kosong */
/* F.S. Jika Q tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 30, 20, 1 akan dicetak: [30,20,1] */
/* Jika Queue kosong : menulis [] */

void dealokasiPrio(PrioQueue * Q);
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi */

void createNotif (Notif *notifikasi, datetime waktu, boolean importance, String subject);
/* Membuat notifikasi */

boolean isImportant (StatusImportance *S, int fromUserId, int toUserId, int importantLimit);

/* Mengecek apakah notifikasi penting atau tidak */

boolean isAfter(datetime t1, datetime t2);

void sortPrio(PrioQueue *Q);
/* Sort notifikasi berdasarkan tingkat kepentingan, lalu berdasarkan waktu */

void printNotif (PrioQueue Q);
/* Melakukan print notifikasi */

void tampilkan_notif(int currentUserId);

#endif
