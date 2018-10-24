/* 
 * 编程之美重建二叉树，扩展问题1，2 
 * 扩展问题1：如果前序和中序的字母可能是相同的，怎么重构出所有可能的解？ 
 * 扩展问题2：如何判断给定的前序和中序遍历的结果是合理的？ 
 *问题1思路：搜索所有可能的情况，并调用扩展问题2的解决方案，判断此情况是否合理（剪枝操作），如果合法，则构造解
 *问题2思路：递归判断左右子树是否合理，递归的返回条件是到达叶子节点。
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

//枚举所有的情况，递归判断是否合法，如果递归到只剩一个叶子节点   
//则肯定是合法的   
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
           
                        //如果leftlen和rightlen都大于零，则lres和rres必须都为true，此分割方法才算合法              
                        if((leftlen > 0 && rightlen >0 && lres && rres) ||   
                        (leftlen > 0 && rightlen <=0 && lres) || (left <=0 && rightlen > 0 && rres)){  
                                return true;      
                        }  
                }  
        }  

        return false;     
}

//枚举法，在枚举的同时使用isvalid函数，排除非法情况   
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

        //有重复的字母   
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
