/* 
 * ���֮���ؽ�����������չ����1��2 
 * ��չ����1�����ǰ����������ĸ��������ͬ�ģ���ô�ع������п��ܵĽ⣿ 
 * ��չ����2������жϸ�����ǰ�����������Ľ���Ǻ���ģ� 
 *����1˼·���������п��ܵ��������������չ����2�Ľ���������жϴ�����Ƿ������֦������������Ϸ��������
 *����2˼·���ݹ��ж����������Ƿ�����ݹ�ķ��������ǵ���Ҷ�ӽڵ㡣
 * 
 * */ 
#include <iostream>   
#include <string>   
using namespace std;  

struct Node  
{  
        Node *left;  
        Node *right;  
        char value;  
};  

void pre_travel(Node *p)  
{  
        if(p == NULL)  
                return;  
        cout << p->value << endl;  
        pre_travel(p->left);  
        pre_travel(p->right);  
}  

//ö�����е�������ݹ��ж��Ƿ�Ϸ�������ݹ鵽ֻʣһ��Ҷ�ӽڵ�   
//��϶��ǺϷ���   
bool isvalid(const char *preorder, const char *inorder, int len)  
{  
        const char *leftend = inorder;  
   
        if(len == 1)  
                return true;  
   
        for(int i=0; i<len; i++, leftend++){  
                if(*leftend == *preorder){  
                        int leftlen = leftend - inorder;  
                        int rightlen = len - leftlen - 1;                 
   
                        bool lres = false, rres = false;  
                        if(leftlen > 0){  
                                lres = isvalid(preorder+1, inorder, leftlen);  
                        }                 
                        if(rightlen > 0){  
                                rres = isvalid(preorder+leftlen+1, inorder+leftlen+1, rightlen);  
                        }  
           
                        //���leftlen��rightlen�������㣬��lres��rres���붼Ϊtrue���˷ָ������Ϸ�              
                        if((leftlen > 0 && rightlen >0 && lres && rres) ||   
                        (leftlen > 0 && rightlen <=0 && lres) || (left <=0 && rightlen > 0 && rres)){  
                                return true;      
                        }  
                }  
        }  

        return false;     
}

//ö�ٷ�����ö�ٵ�ͬʱʹ��isvalid�������ų��Ƿ����   
void rebuild(const char *preorder, const char *inorder, int len, Node **root)  
{  
        if(preorder == NULL || inorder == NULL)  
                return;

        if(*root == NULL){  
                Node *temp = new Node;  
                temp->left = NULL;  
                temp->right = NULL;  
                temp->value = *preorder;  
                *root = temp;  
        }  

        if(len == 1)  
                return;  

        const char *leftend = inorder;  

        for(int i=0; i<len; i++, leftend++){  
                if(*leftend == *preorder){  
                        int leftlen = leftend - inorder;  
                        int rightlen = len - leftlen - 1;  
   
                        if(leftlen > 0  && rightlen >0){  
                                if(isvalid(preorder+1, inorder, leftlen) && isvalid(preorder+leftlen+1, inorder+leftlen+1, rightlen)){  
                                        rebuild(preorder+1, inorder, leftlen, &((*root)->left));  
                                        rebuild(preorder+leftlen+1, inorder+leftlen+1, rightlen, &((*root)->right));  
                                }  
                        }else if(leftlen > 0 && rightlen <= 0){  
                                if(isvalid(preorder+1, inorder, leftlen))  
                                        rebuild(preorder+1, inorder, leftlen, &((*root)->left));  
                        }else if(leftlen <=0 && rightlen >0){  
                                if(isvalid(preorder+leftlen+1, inorder+leftlen+1, rightlen))  
                                        rebuild(preorder+leftlen+1, inorder+leftlen+1, rightlen, &((*root)->right));  
                        }  
                           
                }  
        }  
}  
 
int main()  
{
        string pre1 = "abdefc";  
        string mid1 = "dbfeac";  

        string pre2 = "abdefc";  
        string mid2 = "dcfeab";  

        //���ظ�����ĸ   
        string pre3 = "aadcef";  
        string mid3 = "daaecf";  

        bool valid = isvalid(pre1.c_str(), mid1.c_str(), pre1.length());  
        cout << valid << endl;  

        valid = isvalid(pre2.c_str(), mid2.c_str(), pre2.length());  
        cout << valid << endl;  
 
        valid = isvalid(pre3.c_str(), mid3.c_str(), pre3.length());  
        cout << valid << endl;  

        Node *root = NULL;  
        rebuild(pre3.c_str(), mid3.c_str(), 6, &root);  
        pre_travel(root);  

        return 0;  
}
