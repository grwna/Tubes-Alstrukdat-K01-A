#include <stdio.h>
#include "datetime.h"
    
int main() {
    datetime t;
    readDateTime(&t);
    printf("displayDate: ");
    displayDateTime(t);
    printf("\nprintString: ");
    String s, s2;
    setDateTimeasStringConfig(s, t);
    printString(s);
    printf("\n");
    setDateTimeasStringInbox(s2, t);
    printString(s2);
    printf("\n");
    datetime new = readDateTimefromString(s);
    displayDateTime(new);
    String older;
    assignString(older, SIZE(older), "2020-10-17 19.00.26");
    datetime old = readDateTimefromString(older);
    printf("\nisLater: %d\n", isLater(old, new));
    return 0;
}
// #include <stdio.h>
// #include "datetime.h"
    
// int main() {
//     datetime t;
//     readDateTime(&t);
//     displayDateTime(t);

//     Word w = createWord("17-10-2024 @ 19.00.26");
//     printWord(w);
//     printf("\n");

//     t = readDateTimeFromWord(w);
//     displayDateTime(t);

//     w = setDateTimeAsWord(t);
//     printWord(w);
//     printf("\n");

    // return 0;
// }
