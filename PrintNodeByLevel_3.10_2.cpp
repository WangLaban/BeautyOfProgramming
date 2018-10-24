#include<iostream>
#include<vector>
#include<stack>
using namespace std;

struct node  
{
    node *left;  
    node *right;  
    char value;  
    node(char v,node *l=NULL,node *r=NULL): value(v),left(l),right(r){}
};

void PrintByReverseLevel(node *root)  
{  
    vector<node *> q;  
    stack<int> q2; //记录当前节点的层次  
    node *p;  
    q.push_back(root);  
    q2.push(0);  
    int cur=0;  
    int last=1;  
    while(cur<q.size())  
    {  
        int level=q2.top();  
        last=q.size();  
        while(cur<last)  
        {  
            p=q[cur];  
            
            if(p->left)  
            {  
                q.push_back(p->left);  
                q2.push(level+1);  
            }
            if(p->right)  
            {  
                q.push_back(p->right);  
                q2.push(level+1);  
            }
            cur++;  
        }  
    }  
    while(!q2.empty())  
    {  
        cout << q[--cur]->value;  
        int temp=q2.top();  
        q2.pop();  
        if(q2.empty() || temp!=q2.top())  
            cout << endl;  
    }  
}

int main()     
{        
    node *h=new node('h');         
    node *i=new node('i');     
    node *e=new node('e',h);     
    node *c=new node('c',e);     
    node *f=new node('f',NULL,i);     
    node *g=new node('g');     
    node *d=new node('d',f,g);     
    node *b=new node('b',c,d);     
    node *a=new node('a',NULL,b);     
    
    PrintByReverseLevel(a); 
}
// result:
// ih
// gfe
// dc
// b
// a

