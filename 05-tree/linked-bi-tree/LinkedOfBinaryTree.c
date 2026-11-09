#include"LinkedOfBinaryTree.h"
#include <stdlib.h>   /* malloc */
#include <stddef.h>   /* NULL */
#include "queue.h"    /* common 的 void* 队列，层序遍历用 */
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
static void Threading( ThreadBinaryTree *p, ThreadBinaryTree **pre);
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

bool IsComplete(const BinaryTree *Root) {
    if(IsBiTreeEmpty(Root)) {
        return true;
    }
    Queue TempQueue;
    InitQueue(&TempQueue);
    EnQueue(&TempQueue, (void*)Root);

    int SeeEmpty = 0;
    BinaryTree *Node;

    while(!QueueEmpty(&TempQueue)) {
        DeQueue(&TempQueue, (void**)&Node);

        if (Node==NULL) {
            SeeEmpty++;
            continue;
        }
        if (SeeEmpty) {return false;}
        EnQueue(&TempQueue, (void*)Node->Left);
        EnQueue(&TempQueue, (void*)Node->Right);
    }
    return true;
}

static void Threading( ThreadBinaryTree *p, ThreadBinaryTree **pre) {
    if (p == NULL) {
        return;
    }
    Threading(p->Left,pre);
    if (p->Left == NULL) {
        p->Left=*pre;
        p->Left_Symbol=1;
    }if (*pre != NULL&&(*pre)->Right == NULL) {
        (*pre)->Right=p;
        (*pre)->Right_Symbol=1;
    }
    *pre = p;
    Threading(p->Right,pre);
}

void ThreadingBiTree(BinaryTree *Root) {
    if(IsBiTreeEmpty(Root)) {
        return;
    }
    BinaryTree *pre = NULL;
    Threading(Root, &pre);

    if (pre != NULL) {
        pre->Right = NULL;
        pre->Right_Symbol  = 1;
    }
}




/* =====================================================
 * 中序线索树上的遍历：不用栈、不用递归
 * ===================================================== */

/* 以 p 为根的子树中，中序第一个结点（一路向左走到底） */
BinaryTree *FirstNode(BinaryTree *p) {
    if (p == NULL) return NULL;
    while (p->Left_Symbol == 0 && p->Left != NULL) {
        p = p->Left;
    }
    return p;
}

/* 中序线索下 p 的后继 */
BinaryTree *NextNode(BinaryTree *p) {
    if (p == NULL) return NULL;
    if (p->Right_Symbol == 0) {      /* 右指针是孩子 → 后继在右子树最左下 */
        return FirstNode(p->Right);
    }
    return p->Right;                 /* 右指针就是线索 */
}

/* 线索遍历：一个 for 循环走完全树 */
void InOrderThread(BinaryTree *root) {
    for (BinaryTree *p = FirstNode(root); p != NULL; p = NextNode(p)) {
        BiTreeVisit(p->data);
    }
}
