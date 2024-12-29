#include "search.h"

EmailList inboxTest;

int main(){
    initTrie(&currentTrieRoot);
    createEmailList(&inboxTest, 10);
    Email email1, email2, email3, email4, email5, email6, email7, email8, email9, email10;
    datetime t;
    readDateTime(&t);
    String subject;
    assignString(subject, SIZE(subject), "Subject 1");
    String body;
    assignString(body, SIZE(body), "Oh ho! Then come as close as you like.");
    createEmail(&email1, 1, 1, 2, 3, t, subject, body, 0, true, true);
    assignString(subject, SIZE(subject), "Subject 2");
    assignString(body, SIZE(body), "Too slow, too slow! The World is the ultimate Stand. Even without his power to stop time, his speed and power far exceed that of your Star Platinum.");
    createEmail(&email2, 2, 1, 2, 3, t, subject, body, 0, true, true);
    assignString(subject, SIZE(subject), "Subject 3");
    assignString(body, SIZE(body), "So it's the same type of Stand as Star Platinum. Not much range, but immense power and precise movements.");
    createEmail(&email3, 3, 1, 2, 3, t, subject, body, 0, true, true);
    assignString(subject, SIZE(subject), "Subject 4");
    assignString(body, SIZE(body), "I wanted to try a little test to find out just how much more powerful The World was, compared to your Stand.");
    createEmail(&email4, 4, 1, 2, 3, t, subject, body, 0, true, true);
    assignString(subject, SIZE(subject), "Subject 5");
    assignString(body, SIZE(body), "Though it appears a test was hardly necessary.");
    createEmail(&email5, 5, 1, 2, 3, t, subject, body, 0, true, true);
    assignString(subject, SIZE(subject), "Subject 6");
    assignString(body, SIZE(body), "Test? Is that what you call just patting me, and not even enough to hurt?");
    createEmail(&email6, 6, 1, 2, 3, t, subject, body, 0, true, true);
    assignString(subject, SIZE(subject), "Subject 7");
    assignString(body, SIZE(body), "Well, I guess you ripped my 20,000 yen pants, though.");
    createEmail(&email7, 7, 1, 2, 3, t, subject, body, 0, true, true);
    assignString(subject, SIZE(subject), "Subject 8");
    assignString(body, SIZE(body), "Why are you Joestars so stubborn about admitting defeat? Hmph. I suppose I shall rise to your silly provocation, and test you just a bit more.");
    createEmail(&email8, 8, 1, 2, 3, t, subject, body, 0, true, true);
    assignString(subject, SIZE(subject), "Subject 9");
    assignString(body, SIZE(body), "Oh? You're approaching me? Instead of running away, you're coming right to me? Even though your grandfather, Joseph, told you the secret of The World, like an exam student scrambling to finish the problems on an exam until the last moments before the chime?");
    createEmail(&email9, 9, 1, 2, 3, t, subject, body, 0, true, true);
    assignString(subject, SIZE(subject), "Subject 10");
    assignString(body, SIZE(body), "I can't beat the s**t out of you without getting closer.");
    createEmail(&email10, 10, 1, 2, 3, t, subject, body, 0, true, true);
    insertLast_EmailList(&inboxTest, email1);
    insertLast_EmailList(&inboxTest, email2);
    insertLast_EmailList(&inboxTest, email3);
    insertLast_EmailList(&inboxTest, email4);
    insertLast_EmailList(&inboxTest, email5);
    insertLast_EmailList(&inboxTest, email6);
    insertLast_EmailList(&inboxTest, email7);
    insertLast_EmailList(&inboxTest, email8);
    insertLast_EmailList(&inboxTest, email9);
    insertLast_EmailList(&inboxTest, email10);
    fillTrieFromInbox(&currentTrieRoot, inboxTest);
    emailIdList *result = getSearchResult(currentTrieRoot, "you");
    for(int i = 0; i < NEFF_IDLIST(*result); i++){
        printf("%d\n", ELMT_IDLIST(*result, i));
    }
    result = NULL;
}