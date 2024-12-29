/* File : tree.h */
/* ADT pohon */
/* Representasi Address dengan pointer */
/* infotype adalah integer */

#ifndef TREE_H
#define TREE_H

#include "../utility/boolean.h"
#include "../utility/string.h"

/* Selektor */
#define INFOTREE(T) (T)->info
#define CHILD(T) (T)->firstChild
#define SIBLING(T) (T)->nextSibling
#define PARENT(T) (T)->parent

typedef int infotype;
typedef struct treeNode* SubTree;
typedef struct treeNode { 
     infotype info;
     SubTree firstChild;
     SubTree nextSibling;
     SubTree parent;
} TreeNode;

/* Definisi Tree */
/* Tree kosong T = NULL */
/* Setiap SubTree bisa memiliki banyak "anak", tapi setiap anak hanya 
   memiliki satu parent*/

typedef SubTree Tree;  // Tree as a whole


/* ========================= KONSTRUKTOR/DEKONSTRUKTOR ==================== */
Tree newTree (infotype root); 
/* Menghasilkan akar pohon dari root, left_tree, dan right_tree, jika alokasi berhasil 
   Menghasilkan pohon kosong (NULL) jika alokasi gagal */

void assignValueTree(Tree T, infotype val);
/* Alokasi Info pada tree yang ada*/

void addChildTree (SubTree T, infotype data);
/* I.S. T Terdefinisi
   F.S. Menambah child pada sebuah SubTree dengan info data 
*/

void addParentTree(Tree T, infotype data);
/* I.S. T Terdefinisi dan merupakan Tree paling atas (tidak ada sibling atau parent)
   F.S. Menambah parent pada sebuah SubTree dengan info data 
*/

void deleteTree(Tree T);
/* Menghapus dan membebaskan SEMUA node pada tree, tidak membenarkan pointer dari 
tree parent, tidak bisa digunakan untuk menghapus subtree */

void deleteSubtree(Tree parent, SubTree target);
/* Menghapus subtree dari parent dengan address child tertentu 
   Karena email menggunakan ID, maka bisa dipastikan targer unik
   Menyesuaikan pointer pada node yang tidak dihapus
*/

/* ****** Display Tree ***** */
void printTree(Tree T,  int level);
/* I.S. T terdefinisi, indent adalah jarak indentasi (spasi), level adalah level saat ini (0) */
/* F.S. Semua simpul T sudah ditulis dengan indentasi (spasi) */
/* Penulisan akar selalu pada baris baru (diakhiri newline) */
/* Contoh, jika h = 2: 
1) Pohon preorder: (A()()) akan ditulis sbb:
A
2) Pohon preorder: (A(B()())(C()())) akan ditulis sbb:
A
  B
  C
3) Pohon preorder: (A(B(D()())())(C()(E()()))) akan ditulis sbb:
A
  B
    D
  C
    E
*/

/* [[[[[[]]]]]] UTILITY [[[[[[[]]]]]]]*/

/* ============= GETTER ==============*/

SubTree getAddressByInfoTree(Tree T, infotype X);
/* I.S. T terdefinisi
   F.S. Mengembalikan SubTree sebagai tree baru
*/

Tree getLineageTree(SubTree P);
/* I.S. T Terdefinisi */
/* F.S. Mengembalikan tree baru yang bermuat hanya subtree dan parent-parentnya (tanpa ada sibling)*/
// PEMAKAIAN untuk display reply, sesudah dipanggil dan digunakan, langsung delete

int getHeightTree(Tree T);
/* I.S. T Terdefinisi */
/* F.S. Mengembalikan height, tree yaitu level max yang dimulai dari 1*/

int getChildAmountTree(SubTree T);
/* I.S. T terdefinisi
   F.S. Mengembalikan jumlah child yang dimiliki oleh T
*/

/* =============== BOOLEAN ==================== */
boolean isEmptyTree (SubTree T);
/* Mengirimkan true jika T adalah pohon biner yang kosong */

boolean isChildlessTree(SubTree T);
/* I.S T terdefinisi */
/* F.S true jika T->firstChild == NULL */

boolean isLeafTree(SubTree T);
/* Menghasilkan true jika T adalah leaf */


#endif