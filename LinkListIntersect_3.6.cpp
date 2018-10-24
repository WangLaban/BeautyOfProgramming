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

 //����һ�������дӵ��ĸ���������ӵ��ڶ����������������ཻ������
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

    q->next=p;//���ڶ��������β�ڵ� ���ӵ�L1�ĵ�5���ڵ���

    listTraverse(L); cout<<endl<<endl;
    listTraverse(L2);cout<<endl<<endl;

    /*��p2,p2�ֱ�ָ��2����ͷ�����Ϻ��ƣ����ﵽ��βʱ��p1=p2��˵���л� */
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
        cout<<"�л�:"<<endl;
    else
        cout<<"û��:"<<endl;

    /*
    �󻷽ڵ�\
    */
    p1=L;
    p2=L2;
    int len1=0,len2=0,len;
     
     
    while(p1->next!=NULL) { p1=p1->next;len1++;}
    while(p2->next!=NULL) {p2=p2->next;len2++;}
    Node *p11=L->next,*p22=L2->next;
    if(p1==p2)
    {
        cout<<"�л�"<<endl;
        if(len1>=len2) //2�������ȵĲ�ֵ
        {
            len=len1-len2;
            while(len--)// //������ֵ������ ��ִ��abs(length1-length2)�Σ�
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
            if(p11==p22)////���������е�ַ��ͬ�Ľ��   �����ִ�еĴ���Ϊ��min(length1,length2))
            {
                cout<<"��һ���ཻ�Ľڵ�:"<<p11->data;
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
        cout<<"2�����ཻ"<<endl;  
}
