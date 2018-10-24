#include<iostream>
#include<stack>
using namespace std;

//�������ĳ��ȣ�Ϊ�˺�������ʵ�ֵļ򵥣�����ֱ���ú궨�������ڵ������
#define TREELEN 6

//���ڵ�
struct NODE
{
	NODE *pLeft;  //��ڵ� 
	NODE *pRight;  //�ҽڵ� 
	char chValue;  //�ڵ�ֵ 
};

void Rebuild(char *pPreOrder,  //ǰ�������� 
             char *pInOrder,  //���������� 
			 int nTreeLen,  //������ 
			 NODE **pRoot)  //���ڵ� 
{
	//���߽����� 
	if(pPreOrder == NULL || pInOrder == NULL)
	    return;
	    
	//���ǰ������ĵ�һ���ڵ� 
	NODE *pTemp = new NODE;
	pTemp->chValue = *pPreOrder;
	pTemp->pLeft = NULL;
	pTemp->pRight = NULL;
	
	//����ڵ�Ϊ�գ��ѵ�ǰ�ڵ㸴�Ƶ����ڵ� 
	if(*pRoot == NULL)
	    *pRoot = pTemp;
	    
	//�����ǰ������Ϊ1����ô�Ѿ������һ���ڵ� 
	if(nTreeLen == 1)
	    return;
	    
	//Ѱ���������� 
	char *pOrgInOrder = pInOrder;
	char *pLeftEnd = pInOrder;
	int nTempLen = 0;
	
	//�ҵ��������Ľ�β 
	while(*pPreOrder != *pLeftEnd)
	{
		if(pPreOrder == NULL || pLeftEnd == NULL)
		    return;
		nTempLen++;
		
		//��¼��ʱ���ȣ�������� 
		if(nTempLen > nTreeLen)
		    break;
		pLeftEnd++;
	}
	
	//Ѱ���������ĳ��� 
	int nLeftLen = 0;
	nLeftLen = (int)(pLeftEnd - pOrgInOrder);
	
	//Ѱ���������ĳ��� 
	int nRightLen = 0;
	nRightLen = nTreeLen - nLeftLen - 1;
	
	//�ؽ������� 
	if(nLeftLen > 0)
	    Rebuild(pPreOrder + 1, pInOrder, nLeftLen, &((*pRoot)->pLeft));
	   
	//�ؽ������� 
	if(nRightLen > 0)
	    Rebuild(pPreOrder + nLeftLen + 1, pInOrder + nLeftLen + 1, nRightLen, &((*pRoot)->pRight));
}

//����ڵ� 
void preOrder(NODE *root)     //�ݹ�ʵ��
{
    if(root!=NULL)
        cout<<root->chValue<<endl;
    if(root->pLeft!=NULL)
        preOrder(root->pLeft);
    if(root->pRight!=NULL)
        preOrder(root->pRight);
}

//ʾ���ĵ��ô��� 
int main()
{
	char szPreOrder[TREELEN] = {'a', 'b', 'd', 'c', 'e', 'f'};
	char szInOrder[TREELEN] = {'d', 'b', 'e', 'a', 'c', 'f'};
	
	NODE *pRoot = NULL;
	Rebuild(szPreOrder, szInOrder, TREELEN, &pRoot);
	preOrder(pRoot); 
	return 0;
}
