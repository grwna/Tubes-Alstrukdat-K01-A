
# include "tree.h"
# include <stdlib.h>
# include <stdio.h>


/* ========================= KONSTRUKTOR/DEKONSTRUKTOR ==================== */
Tree newTree (infotype root){
    SubTree T = (SubTree)malloc(sizeof(TreeNode));
    if(T != NULL){
        INFOTREE(T) = root;
        CHILD(T) = NULL;
        SIBLING(T) = NULL;
        PARENT(T) = NULL;   // <---------------- TANDAI
    }
    return T;
}; 

void assignValueTree(Tree T, infotype val){
    INFOTREE(T) = val;
}

void addChildTree (SubTree parent, infotype data){
    SubTree child = newTree(data);
    PARENT(child) = parent;

    if (isChildlessTree(parent)) {
        CHILD(parent) = child;
    }
    else {
        SubTree current = CHILD(parent);
        while (SIBLING(current) != NULL){
            current = SIBLING(current);
        }
        SIBLING(current) = child;
    }
}

void addParentTree(Tree T, infotype data){
    Tree newParent = newTree(data);
    PARENT(T) = newParent;
    CHILD(newParent) = T;
}

void deleteTree(Tree T) {
    if (T == NULL) return;

    // Recursively delete all children
    while (CHILD(T) != NULL) {
        SubTree child = CHILD(T);
        CHILD(T) = SIBLING(child);
        deleteTree(child);
    }

    // Free the current node
    free(T);
}

void deleteSubtree(Tree parent, SubTree node) {
    if (isEmptyTree(parent) || isChildlessTree(parent)) return;

    // Case 1: Node is the first child of its parent
    if (CHILD(parent) == node) {
        CHILD(parent) = SIBLING(node);
    } else {
        // Case 2: Node is a sibling, so find its previous sibling
        SubTree current = CHILD(parent);
        while (current != NULL && SIBLING(current) != node) {
            current = SIBLING(current);
        }
        if (current != NULL) {
            SIBLING(current) = SIBLING(node);
        }
    }

    // Delete the subtree rooted at 'node'
    deleteTree(node);
}
/* ===================== Display Tree ================ */
// BUAT DEBUGGING AJA
void printTree(Tree T, int level){
    if (isEmptyTree(T)) return;

    for(int i = 0; i < level; i++) {
        if(i == 0) printf("└─");
        if(i == level-1 ) printf(" ");
        else printf("──");
    }
    printf("%d\n", INFOTREE(T));
    printTree(CHILD(T), level+1);
    printTree(SIBLING(T), level);

};
/* I.S. T terdefinisi (tidak boleh kosong), level adalah level saat ini (selalu gunakan 0 saat memanggil) */
/* F.S. Semua simpul T sudah ditulis dengan indentasi (spasi) */
/* Penulisan akar selalu pada baris baru (diakhiri newline) */


/* =============== UTILITY/GETTER ==================== */
SubTree getAddressByInfoTree(Tree T, infotype X){
    if(T != NULL){
        if (INFOTREE(T) == X) return T;
        else {
            SubTree P = getAddressByInfoTree(CHILD(T), X);
            if (P != NULL) return P;
            else return getAddressByInfoTree(SIBLING(T), X);
        }
    }
    return NULL;
}

Tree getLineageTree(SubTree P){
    SubTree newNode = newTree(INFOTREE(P));
    while(PARENT(P)!= NULL){
        P = PARENT(P);
        PARENT(newNode) = newTree(INFOTREE(P));
        newNode = PARENT(newNode);
    }
    return newNode;
}

int getHeightTree(Tree T){
    if (T == NULL) return 0;
 
    int childHeight = 0, siblingHeight = 0;

    childHeight = getHeightTree(CHILD(T));
    // printf("childHeight infotype %d: %d\n", INFOTREE(T), childHeight);

    siblingHeight = getHeightTree(SIBLING(T));
    // printf("siblingHeight infotype %d: %d\n", INFOTREE(T), siblingHeight);

    return ((childHeight + 1) > siblingHeight) ? childHeight + 1 : siblingHeight;
}

int getChildAmountTree(SubTree T){
    int children;
    if(CHILD(T) == NULL) return 0;
    T = CHILD(T);
    children = 1;
    while(SIBLING(T) != NULL){
        T = SIBLING(T);
        children++;
    };
    return children;
}


/* =============== BOOLEAN ==================== */
boolean isEmptyTree (SubTree T){
    return (T == NULL);
};
/* Mengirimkan true jika T adalah pohon biner yang kosong */

boolean isChildlessTree(SubTree T){
    return CHILD(T) == NULL;
};

boolean isLeafTree(SubTree T){
    return ((!isEmptyTree(T)) && isChildlessTree(T));
};
