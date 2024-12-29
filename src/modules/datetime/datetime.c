#include <stdio.h>
#include "datetime.h"

/* mengambil data tanggal dan waktu saat fungsi dipanggil */
void readDateTime (datetime *t) {
    
    time_t seconds;
    time(&seconds);

    struct tm tm = *localtime(&seconds);
    YEARS(*t) = tm.tm_year + 1900;
    MONTHS(*t) = tm.tm_mon + 1;
    DAYS(*t) = tm.tm_mday;
    HOURS(*t) = tm.tm_hour;
    MINUTES(*t) = tm.tm_min;
    SECONDS(*t) = tm.tm_sec;

}

/* menampilkan tanggal dan waktu */
void displayDateTime (datetime t) {
    
    printf("%02d-%02d-%02d @ %02d.%02d.%02d", YEARS(t), MONTHS(t), DAYS(t), HOURS(t), MINUTES(t), SECONDS(t));

}

/* membaca data tanggal dan waktu dari string dengan template sesuai */
datetime readDateTimefromString (String s) {

    datetime t;
    String temp;

    int counter = 0;
    for (int i = 0; i < 4; i++) {
        temp[counter] = s[i];
        counter++;
    }
    temp[counter] = '\0';
    YEARS(t) = stringToInteger(temp);

    counter = 0;
    for (int i = 5; i < 7; i++) {
        temp[counter] = s[i];
        counter++;
    }
    temp[counter] = '\0';
    MONTHS(t) = stringToInteger(temp);
    // printf("MONTHS: %d\n", MONTHS(t));

    counter = 0;
    for (int i = 8; i < 10; i++) {
        temp[counter] = s[i];
        counter++;
    }
    temp[counter] = '\0';
    DAYS(t) = stringToInteger(temp);
    // printf("DAYS: %d\n", DAYS(t));

    counter = 0;

    for (int i = 11; i < 13; i++) {
        (temp[counter]) = (s[i]);
        counter++;
    }
    temp[counter] = '\0';
    HOURS(t) = stringToInteger(temp);
    // printf("HOURS: %d\n", HOURS(t));

    counter = 0;
    for (int i = 14; i < 16; i++) {
        (temp[counter]) = (s[i]);
        counter++;
    }
    temp[counter] = '\0';
    MINUTES(t) = stringToInteger(temp);
    // printf("MINUTES: %d\n", MINUTES(t));

    counter = 0;
    for (int i = 17; i < 19; i++) {
        (temp[counter]) = (s[i]);
        counter++;
    }
    temp[counter] = '\0';
    SECONDS(t) = stringToInteger(temp);
    // printf("SECONDS: %d\n", SECONDS(t));
    
    // displayDateTime(t);
    // printf("\n");
    return t;
}

/* membentuk string dari data tanggal dan waktu dengan template sesuai inbox.*/
void setDateTimeasStringInbox (String s, datetime t) {
    /* days */
    s[0] = (DAYS(t) / 10) + '0';
    s[1] = (DAYS(t) % 10) + '0';

    s[2] = '-';

    /* months */
    s[3] = (MONTHS(t) / 10) + '0';
    s[4] = (MONTHS(t) % 10) + '0';

    s[5] = '-';

    /* years */
    s[6] = (YEARS(t) / 1000) + '0';
    s[7] = ((YEARS(t) / 100) % 10) + '0';
    s[8] = ((YEARS(t) / 10) % 10) + '0';
    s[9] = (YEARS(t) % 10) + '0';

    s[10] = ' ';
    s[11] = '@';
    s[12] = ' ';

    /* hours */
    s[13] = (HOURS(t) / 10) + '0';
    s[14] = (HOURS(t) % 10) + '0';

    s[15] = '.';

    /* minutes */
    s[16] = (MINUTES(t) / 10) + '0';
    s[17] = (MINUTES(t) % 10) + '0';

    s[18] = '.';

    /* seconds */
    s[19] = (SECONDS(t) / 10) + '0';
    s[20] = (SECONDS(t) % 10) + '0';
    s[21] = '\0';
}

/* membentuk string dari data tanggal dan waktu dengan template sesuai config.*/
void setDateTimeasStringConfig (String s, datetime t) {
    /* years */
    s[0] = (YEARS(t) / 1000) + '0';
    s[1] = ((YEARS(t) / 100) % 10) + '0';
    s[2] = ((YEARS(t) / 10) % 10) + '0';
    s[3] = (YEARS(t) % 10) + '0';

    s[4] = '-';

    /* months */
    s[5] = (MONTHS(t) / 10) + '0';
    s[6] = (MONTHS(t) % 10) + '0';

    s[7] = '-';

    /* days */
    s[8] = (DAYS(t) / 10) + '0';
    s[9] = (DAYS(t) % 10) + '0';

    s[10] = ' ';

    /* hours */
    s[11] = (HOURS(t) / 10) + '0';
    s[12] = (HOURS(t) % 10) + '0';

    s[13] = '.';

    /* minutes */
    s[14] = (MINUTES(t) / 10) + '0';
    s[15] = (MINUTES(t) % 10) + '0';

    s[16] = '.';

    /* seconds */
    s[17] = (SECONDS(t) / 10) + '0';
    s[18] = (SECONDS(t) % 10) + '0';
    s[19] = '\0';
}

boolean isLater(datetime t1, datetime t2) {

    if (YEARS(t1) > YEARS(t2)) {
        return true;
    } 
    if (YEARS(t1) < YEARS(t2)) {
        return false;
    }

    if (MONTHS(t1) > MONTHS(t2)) {
        return true;
    } 
    if (MONTHS(t1) < MONTHS(t2)) {
        return false;
    }

    if (DAYS(t1) > DAYS(t2)) {
        return true;
    } 
    if (DAYS(t1) < DAYS(t2)) {
        return false;
    }

    if (HOURS(t1) < HOURS(t2)) {
        return true;
    } 
    if (HOURS(t1) > HOURS(t2)) {
        return false;
    }

    if (MINUTES(t1) > MINUTES(t2)) {
        return true;
    } 
    if (MINUTES(t1) < MINUTES(t2)) {
        return false;
    }

    if (SECONDS(t1) > SECONDS(t2)) {
        return true;
    } 
    if (SECONDS(t1) < SECONDS(t2)) {
        return false;
    }

    return true;
}