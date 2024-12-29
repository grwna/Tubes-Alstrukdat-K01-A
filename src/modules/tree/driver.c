# include "tree.h"
# include <stdio.h>

int main(){
    Tree t = newTree(1);
    newChild(t, 2);
    newChild(t, 3);
    newChild(t, 4);
    newChild(CHILD(t), 5);
    newChild(SIBLING(CHILD(t)), 6);
    newChild(CHILD(SIBLING(CHILD(t))), 8);
    newChild(SIBLING(CHILD(t)), 7);

    printTree(t, 0);
    deleteSubtree(t,CHILD(t));
    deleteSubtree(CHILD(t),SIBLING(CHILD(CHILD(t))));
    printTree(t, 0);
    printf("\n");
    // printf("%d", INFO(PARENT(CHILD(t))));
    // printf("%d\n", treeHeight(t));
    // printf("%d\n", childAmount(CHILD(t)));
    // printf("%d\n",INFO(CHILD(t)));
    // printf("%d\n",INFO(SIBLING(CHILD(t))));
    return 0;
}