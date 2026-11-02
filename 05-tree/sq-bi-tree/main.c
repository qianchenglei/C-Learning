#include "SqBinaryTree.h"
int main() {
    SqBinaryTree tree;
    const ElemType *Data = "ABC#D";
    CreateBinaryTree(&tree,Data);
    for(int i = 1;i<=tree.n;i++) {
        printf("%c ",tree.data[i]);
    }
    printf("%d\n",tree.n);
    printf("%d\n",IsBiTreeEmpty(&tree));
    printf("%d\n",BiTreeDepth(&tree));
    PreOrder(&tree,1);
    InOrder(&tree,1);
    PostOrder(&tree,1);
    printf("%d\n",NodeCount(&tree));
    printf("%d\n",LeafCount(&tree));
    printf("%d\n",IsComplete(&tree));
    return 0;
}