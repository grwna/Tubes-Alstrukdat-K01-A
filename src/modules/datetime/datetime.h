/* File: datetime.h */
/* Spesifikasi ADT datetime */

#ifndef DATETIME_h
#define DATETIME_h

#include "../utility/boolean.h"
#include "../utility/string.h"
#include <time.h>

/* Definisi elemen datetime */
typedef struct {
    int years;
    int months;
    int days;
    int hours;
    int minutes;
    int seconds;
} datetime;

/* ********* SELEKTOR ********** */
#define YEARS(t)    (t).years
#define MONTHS(t)   (t).months
#define DAYS(t)     (t).days
#define HOURS(t)    (t).hours
#define MINUTES(t)  (t).minutes
#define SECONDS(t)  (t).seconds

/* ********* METODE ********** */

/* mengambil data tanggal dan waktu saat fungsi dipanggil */
void readDateTime (datetime *t);

/* menampilkan tanggal dan waktu*/
void displayDateTime (datetime t);

/* membaca data tanggal dan waktu dari string */
datetime readDateTimefromString (String s);

/*  I.S. t terdefinisi, s sembarang
    F.S. s terbentuk dari data tanggal dan waktu dengan template sesuai inbox*/
void setDateTimeasStringInbox (String s, datetime t);

/*  I.S. t terdefinisi, s sembarang
    F.S. s terbentuk dari data tanggal dan waktu dengan template sesuai config */
void setDateTimeasStringConfig (String s, datetime t);

/* membandingkan dua datetime, mengembalikan true jika t1 lebih baru daripada t2 */
boolean isLater(datetime t1, datetime t2);

#endif