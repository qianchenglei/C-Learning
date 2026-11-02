#include"LinkedOfBinaryTree.h"
#include "Stack.h"
static char SeqNext(const ElementType **Seq) {
    char Ch = **Seq;
    if(Ch != '\0') {(*Seq)++;}
    return Ch;
}
static BinaryTreeNode *NewNode(const ElementType Ch) {
    BinaryTreeNode *Node = malloc(sizeof(*Node));
    Node->data = Ch;
    Node->Left = NULL;
    Node->Right = NULL;
    return Node;
}
static void BiTreeVisit( const ElementType Data) {
    printf("%c", Data);
}
void Init(BinaryTree **root) {
    *root=NULL;
}

void BuildBiTree(BinaryTree **root, const ElementType **Seq) {
    Init(root);
    char Ch = SeqNext(Seq);
    if(Ch == '#'||Ch == '\0') {
        *root = NULL;
        return;
    }
    BinaryTreeNode *Node = NewNode(Ch);
    BuildBiTree(&Node->Left, Seq);
    BuildBiTree(&Node->Right, Seq);
    *root = Node;
}

bool IsBiTreeEmpty(const BinaryTree *Root) {
    if(Root == NULL) {
        return true;
    }else {
        return false;
    }
}

int BiTreeDepth(const BinaryTree *Root) {
    if(IsBiTreeEmpty(Root)) {
        return 0;
    }
    int Left = BiTreeDepth(Root->Left);
    int Right = BiTreeDepth(Root->Right);

    return 1+(Left>Right?Left:Right);
}

void PreOrder(BinaryTree *Node) {
    if(IsBiTreeEmpty(Node)) {
        return;
    }
    BiTreeVisit(Node->data);
    PreOrder(Node->Left);
    PreOrder(Node->Right);
}

void InOrder(BinaryTree *Node) {
    if(IsBiTreeEmpty(Node)) {
        return;
    }
    InOrder(Node->Left);
    BiTreeVisit(Node->data);
    InOrder(Node->Right);
}

void PostOrder(BinaryTree *Node) {
    if(IsBiTreeEmpty(Node)) {
        return;
    }
    PostOrder(Node->Left);
    PostOrder(Node->Right);
    BiTreeVisit(Node->data);
}

int NodeCount(const BinaryTree *Node) {
    if(IsBiTreeEmpty(Node)) {
        return 0;
    }
    int Left = NodeCount(Node->Left);
    int Right = NodeCount(Node->Right);
    return 1+Left+Right;
}

int LeafCount(const BinaryTree *Node) {
    if(IsBiTreeEmpty(Node)) {
        return 0;
    }
    if(Node->Left == NULL && Node->Right == NULL) {
        return 1;
    }
    return LeafCount(Node->Left) + LeafCount(Node->Right);
}


