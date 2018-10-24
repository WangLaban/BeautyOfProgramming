#include<iostream>
#include<stdlib.h>
#include<cassert>
using namespace std;

typedef struct LNode
{
        int data;
        struct LNode *next;
}LinkList;
void CreateListR(LinkList *&L,int a[],int n)
{
     LinkList *s,*r;
     int i;
     L=(LinkList *)malloc(sizeof(LinkList));  //额外的一个节点 
     r=L;
     for(i=0;i<n;i++)
     {
                     s=(LinkList *)malloc(sizeof(LinkList));
                     s->data=a[i];
                     r->next=s;
                     r=s;
     }
     r->next=NULL;
}
void InitList(LinkList *&L)
{
     L=(LinkList *)malloc(sizeof(LinkList));
     L->next=NULL;
}
void DestroyList(LinkList *&L)
{
     LinkList *p=L,*q=p->next;
     while(q!=NULL)
     {
                   free(p);
                   p=q;
                   q=p->next;
     }
     free(p);
}
void DispList(LinkList *L)
{
     LinkList *p=L->next;
     while(p)
     {
             printf("%d",p->data);
             p=p->next;
             if(p)
                 printf("->");
     }
     printf("\n");
}
void DeleteRandomNode(LinkList *pCurrent)
{
     assert(pCurrent!=NULL);
     LinkList *pNext=pCurrent->next;
     if(pNext!=NULL)
     {
                    pCurrent->data=pNext->data;
                    pCurrent->next=pNext->next;
                    free(pNext);
     }
}
void ReverseData(LinkList *&L)
{
     LinkList *pNext=L->next;
     LinkList *p=pNext,*q,*r;
     q=p->next;
     r=q->next;
     q->next=p;
     p->next=NULL;
     p=q;
     q=r;
     r=r->next;
     while(r->next!=NULL)
     {
                   q->next=p;
                   p=q;
                   q=r;
                   r=r->next;
     }
     q->next=p;
     r->next=q;
     L->next=r;
}
     
int main()
{
    int a[]={5,7,3,4,8,9,0};
    LinkList *L=(LinkList *)malloc(sizeof(LinkList));
    InitList(L);
    CreateListR(L,a,7);
    DispList(L);
    LinkList *p=L->next;
    DeleteRandomNode(p->next);
    DispList(L);
    ReverseData(L);//给定链表的头指针，只遍历一次，将单链表的元素顺序反过来
    DispList(L);
    DestroyList(L);
    system("pause");
    return 0;
}
