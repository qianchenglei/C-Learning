#include"SqBinaryTree.h"


static int BiTreeDepth_Depth(const SqBinaryTree *T,int index);
static void visit(const ElemType Print);



void InItBinaryTree(SqBinaryTree *T){

    T->n = 0;
    memset(T->data,0,sizeof(T->data)); 
}
void CreateBinaryTree(SqBinaryTree *T,const ElemType *S){
    InItBinaryTree(T);
    for(int i = 1;S[i-1]!='\0'&& i <MaxChindUnit+1;i++){
        if(S[i-1]=='#'){
            T->data[i] = 0;
        }else{
            T->data[i] = S[i-1];
            T->n=i;
        }
    }
}

bool IsBiTreeEmpty(const SqBinaryTree *T) {
    if(T->n==0) {
        return true;
    }else return false;
}

int BiTreeDepth(const SqBinaryTree *T) {
    if(IsBiTreeEmpty(T)) {
        return 0;
    }
    return BiTreeDepth_Depth(T,1);
}

int BiTreeDepth_Depth(const SqBinaryTree *T, int index) {
    if (index >T->n||!T->data[index]) {return 0;}
    int Lside = BiTreeDepth_Depth(T,2*index);
    int Rside = BiTreeDepth_Depth(T,2*index+1);
    return 1+(Lside>Rside?Lside:Rside);
}
void visit(const ElemType Print) {
    printf("%c\n",Print);
}

void PreOrder(const SqBinaryTree *T, int index) {
    if (index >T->n||!T->data[index]) {return;}
    visit(T->data[index]);
    PreOrder(T,2*index);
    PreOrder(T,2*index+1);
}

void InOrder(const SqBinaryTree *T, int index) {
    if (index >T->n||!T->data[index]) {return;}
    InOrder(T,2*index);
    visit(T->data[index]);
    InOrder(T,2*index+1);
}

void PostOrder(const SqBinaryTree *T, int index) {
    if (index >T->n||!T->data[index]) {return;}
    PostOrder(T,2*index);
    PostOrder(T,2*index+1);
    visit(T->data[index]);
}

int NodeCount(const SqBinaryTree *T) {
    if(IsBiTreeEmpty(T)) {return 0;}
    int cnt = 0;
    for(int i = 1;i<=T->n;i++) {
        if(T->data[i]!= 0) {
            cnt++;
        }
    }
    return cnt;
}

int LeafCount(const SqBinaryTree *T) {
    if(IsBiTreeEmpty(T)) {return 0;}
    int cnt = 0;
    for(int i = 1;i<=T->n;i++) {
        if (!T->data[i]) continue;
        int L=2*i,r=L+1;
        int HasL = (L<=T->n&&T->data[L]!=0);
        int HasR = (r<=T->n&&T->data[r]!=0);
        if(!HasL&&!HasR) {cnt++;}
    }
    return cnt;
}

bool IsComplete(const SqBinaryTree *T) {
    if (IsBiTreeEmpty(T)) {return true;}
    for(int i = 1;i<=T->n;i++) {
        if(T->data[i]==0) {
            for(int j = i+1;j<=T->n;j++) {
                if(T->data[j]!=0) {
                    return false;
                }
            }
        }
    }
    return true;
}
