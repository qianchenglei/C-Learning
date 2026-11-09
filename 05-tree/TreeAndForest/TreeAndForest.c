#include "TreeAndForest.h"
static char SeqNext(const ElemType **Seq) {
    char ch = **Seq;
    if (ch!='\0') {
        (*Seq)++;
    }
    return ch;
}
static BiTreeNode *NewBiTreeNode(const ElemType Ch) {
    BiTree *Node = malloc(sizeof(BiTreeNode));
    Node->Data = Ch;
    Node->Left = NULL;
    Node->Right = NULL;
    return Node ;
}
void InItBinaryTree(BiTree **Root) {
    if (Root == NULL) {
        return;
    }
    (*Root)=NULL;
}

void CreateBinaryTree(BiTree **Root,const ElemType **Seq) {
    InItBinaryTree(Root);
    char Ch = SeqNext(Seq);
    if (Ch=='#'||Ch=='\0') {
        *Root=NULL;
        return;
    }
    BiTree *Node=NewBiTreeNode(Ch);
    CreateBinaryTree(&Node->Left,Seq);
    CreateBinaryTree(&Node->Right,Seq);
    *Root=Node;
}

bool IsEmpty(BiTree *Root) {
    if (Root == NULL) {
        return true;
    }else {
        return false;
    }
}

