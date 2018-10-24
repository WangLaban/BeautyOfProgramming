#include<iostream>
#include<stack>
using namespace std;

//定义树的长度，为了后续调用实现的简单，我们直接用宏定义了树节点的总数
#define TREELEN 6

//树节点
struct NODE
{
	NODE *pLeft;  //左节点 
	NODE *pRight;  //右节点 
	char chValue;  //节点值 
};

void Rebuild(char *pPreOrder,  //前序遍历结果 
             char *pInOrder,  //中序遍历结果 
			 int nTreeLen,  //树长度 
			 NODE **pRoot)  //根节点 
{
	//检查边界条件 
	if(pPreOrder == NULL || pInOrder == NULL)
	    return;
	    
	//获得前序遍历的第一个节点 
	NODE *pTemp = new NODE;
	pTemp->chValue = *pPreOrder;
	pTemp->pLeft = NULL;
	pTemp->pRight = NULL;
	
	//如果节点为空，把当前节点复制到根节点 
	if(*pRoot == NULL)
	    *pRoot = pTemp;
	    
	//如果当前树长度为1，那么已经是最后一个节点 
	if(nTreeLen == 1)
	    return;
	    
	//寻找子树长度 
	char *pOrgInOrder = pInOrder;
	char *pLeftEnd = pInOrder;
	int nTempLen = 0;
	
	//找到左子树的结尾 
	while(*pPreOrder != *pLeftEnd)
	{
		if(pPreOrder == NULL || pLeftEnd == NULL)
		    return;
		nTempLen++;
		
		//记录临时长度，以免溢出 
		if(nTempLen > nTreeLen)
		    break;
		pLeftEnd++;
	}
	
	//寻找左子树的长度 
	int nLeftLen = 0;
	nLeftLen = (int)(pLeftEnd - pOrgInOrder);
	
	//寻找右子树的长度 
	int nRightLen = 0;
	nRightLen = nTreeLen - nLeftLen - 1;
	
	//重建左子树 
	if(nLeftLen > 0)
	    Rebuild(pPreOrder + 1, pInOrder, nLeftLen, &((*pRoot)->pLeft));
	   
	//重建右子树 
	if(nRightLen > 0)
	    Rebuild(pPreOrder + nLeftLen + 1, pInOrder + nLeftLen + 1, nRightLen, &((*pRoot)->pRight));
}

//输出节点 
void preOrder(NODE *root)     //递归实现
{
    if(root!=NULL)
        cout<<root->chValue<<endl;
    if(root->pLeft!=NULL)
        preOrder(root->pLeft);
    if(root->pRight!=NULL)
        preOrder(root->pRight);
}

//示例的调用代码 
int main()
{
	char szPreOrder[TREELEN] = {'a', 'b', 'd', 'c', 'e', 'f'};
	char szInOrder[TREELEN] = {'d', 'b', 'e', 'a', 'c', 'f'};
	
	NODE *pRoot = NULL;
	Rebuild(szPreOrder, szInOrder, TREELEN, &pRoot);
	preOrder(pRoot); 
	return 0;
}
