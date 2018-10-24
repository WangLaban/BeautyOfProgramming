#include<iostream>
using namespace std;

typedef struct Node
{
    int data;
    Node* next;
    Node(int data)
    {
        this->data=data;
    }
    Node(){}
}*LinkList;
void initList(LinkList &list)
{
    list=new Node();
    list->next=NULL;
}
void insertList(LinkList &list)
{
     
    int val;
    Node *tail=list;
    while(tail->next!=NULL)
        tail=tail->next;

    while(cin>>val && val!=-1)
    {
        Node *p=new Node(val);
        p->next=NULL;

        tail->next=p;
        tail=tail->next;

    }
}
void listTraverse(LinkList &list)
{
    Node *p=list->next;
    while(p)
    {
        cout<<p->data<<ends;
        p=p->next;
    }
}
int main()
{
    LinkList L;
    initList(L);
    insertList(L);
    listTraverse(L);
    cout<<endl<<endl;
    cout.clear();
    LinkList L2;
    initList(L2);
    insertList(L2);
    listTraverse(L2);
	cout<<endl<<endl;

 //将第一个链表中从第四个结点起链接到第二个链表，构造两个相交的链表
    Node *p=L;
    for(int i=0;i<=4;i++)
    {
        p=p->next;
    }
    Node *q=L2;
    while(q->next)
    {
        q=q->next;
    }

    q->next=p;//将第二个链表的尾节点 连接到L1的第5个节点中

    listTraverse(L); cout<<endl<<endl;
    listTraverse(L2);cout<<endl<<endl;

    /*用p2,p2分别指向2个表头，不断后移，最后达到表尾时，p1=p2，说明有环 */
    Node *p1,*p2;
    p1=L;
    p2=L2;
    bool isCircle=false;
    int count=0;
    while(p1->next!=NULL) p1=p1->next;
    while(p2->next!=NULL) p2=p2->next;
     
    if(p1==p2)
    {
        isCircle=true;
    }
    if(isCircle)
        cout<<"有环:"<<endl;
    else
        cout<<"没环:"<<endl;

    /*
    求环节点\
    */
    p1=L;
    p2=L2;
    int len1=0,len2=0,len;
     
     
    while(p1->next!=NULL) { p1=p1->next;len1++;}
    while(p2->next!=NULL) {p2=p2->next;len2++;}
    Node *p11=L->next,*p22=L2->next;
    if(p1==p2)
    {
        cout<<"有环"<<endl;
        if(len1>=len2) //2个链表长度的差值
        {
            len=len1-len2;
            while(len--)// //遍历差值个步长 （执行abs(length1-length2)次）
                p11=p11->next;
        }
        else
        {
            len=len2-len1;
            while(len--)
                p22=p22->next;
        }
        while(1)
        {
            if(p11==p22)////两个链表中地址相同的结点   （最多执行的次数为：min(length1,length2))
            {
                cout<<"第一个相交的节点:"<<p11->data;
                break;
            }
            else if(p11->next && p22->next)
            {
                p11=p11->next;
                p22=p22->next;
            }
        }
    }//end if
    else
        cout<<"2链表不相交"<<endl;  
}
