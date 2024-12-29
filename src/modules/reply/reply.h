#ifndef REPLY_H
#define REPLY_H

# define MASTER -1

// Include necessary libraries
#include "../utility/string.h"
#include "../utility/boolean.h"
#include "../tree/tree.h"
#include "../email_list/email_list.h"
#include "../datetime/datetime.h"
#include "../stack/stack.h"
#include "../user/user.h"

extern Tree MasterTree;

void assignEmailsToMasterTree();

void createMasterTree();
/* I.S. Sembarang
   F.S. Mengembalikan MASTER tree, yaitu tree yang akan menyimpan id semua email
*/

void assignEmailsToMasterTree();

void addReplyToTree(Email reply);
/* I.S. parentEmail terdefinisi
   F.S. Menambah balasan menjadi "anak" dari parentEmail
   // DIPAKE SESUDAH KIRIM DRAFT
*/

SubTree getSubtreeByID(int ID);
/* I.S. ID Terdefinisi
   F.S. Mengembalikan SubTree yang mengandung ID email
*/

void printReply(int ID);

#endif // REPLY_H