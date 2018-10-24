#if 0
// ���ݽṹ����
struct NODE
{
    NODE* pLeft;        // ������
    NODE* pRight;       // ������
    int nMaxLeft;       // �������е������
    int nMaxRight;      // �������е������
    char chValue;       // �ýڵ��ֵ
};
 
int nMaxLen = 0;
 
// Ѱ������������ξ���
void FindMaxLen(NODE* pRoot)
{
    // ������Ҷ�ӽڵ㣬����
    if(pRoot == NULL)
    {
        return;
    }
 
    // ���������Ϊ�գ���ô�ýڵ����������Ϊ0
    if(pRoot -> pLeft == NULL)
    {
        pRoot -> nMaxLeft = 0; 
    }
 
    // ���������Ϊ�գ���ô�ýڵ���ұ������Ϊ0
    if(pRoot -> pRight == NULL)
    {
        pRoot -> nMaxRight = 0;
    }
 
    // �����������Ϊ�գ��ݹ�Ѱ�������������
    if(pRoot -> pLeft != NULL)
    {
        FindMaxLen(pRoot -> pLeft);
    }
 
    // �����������Ϊ�գ��ݹ�Ѱ�������������
    if(pRoot -> pRight != NULL)
    {
        FindMaxLen(pRoot -> pRight);
    }
 
    // ������������ڵ����
    if(pRoot -> pLeft != NULL)
    {
        int nTempMax = 0;
        if(pRoot -> pLeft -> nMaxLeft > pRoot -> pLeft -> nMaxRight)
        {
            nTempMax = pRoot -> pLeft -> nMaxLeft;
        }
        else
        {
            nTempMax = pRoot -> pLeft -> nMaxRight;
        }
        pRoot -> nMaxLeft = nTempMax + 1;
    }
 
    // ������������ڵ����
    if(pRoot -> pRight != NULL)
    {
        int nTempMax = 0;
        if(pRoot -> pRight -> nMaxLeft > pRoot -> pRight -> nMaxRight)
        {
            nTempMax = pRoot -> pRight -> nMaxLeft;
        }
        else
        {
            nTempMax = pRoot -> pRight -> nMaxRight;
        }
        pRoot -> nMaxRight = nTempMax + 1;
    }
 
    // ���������
    if(pRoot -> nMaxLeft + pRoot -> nMaxRight > nMaxLen)
    {
        nMaxLen = pRoot -> nMaxLeft + pRoot -> nMaxRight;
    }
}
#endif

#if 0
#include <iostream>
using namespace std;

struct NODE
{
    NODE *pLeft;
    NODE *pRight;
};

struct RESULT
{
    int nMaxDistance;
    int nMaxDepth;
};

RESULT GetMaximumDistance(NODE* root)
{
    if (!root)
    {
        RESULT empty = { 0, -1 };   // trick: nMaxDepth is -1 and then caller will plus 1 to balance it as zero.
        return empty;
    }
 
    RESULT lhs = GetMaximumDistance(root->pLeft);
    RESULT rhs = GetMaximumDistance(root->pRight);
 
    RESULT result;
    result.nMaxDepth = max(lhs.nMaxDepth + 1, rhs.nMaxDepth + 1);
    result.nMaxDistance = max(max(lhs.nMaxDistance, rhs.nMaxDistance), lhs.nMaxDepth + rhs.nMaxDepth + 2);
    return result;
}

void Link(NODE* nodes, int parent, int left, int right)
{
    if (left != -1)
        nodes[parent].pLeft = &nodes[left]; 
 
    if (right != -1)
        nodes[parent].pRight = &nodes[right];
}

int main()
{
    // P. 241 Graph 3-12
    NODE test1[9] = { 0 };
    Link(test1, 0, 1, 2);
    Link(test1, 1, 3, 4);
    Link(test1, 2, 5, 6);
    Link(test1, 3, 7, -1);
    Link(test1, 5, -1, 8);
    cout << "test1: " << GetMaximumDistance(&test1[0]).nMaxDistance << endl;

    // P. 242 Graph 3-13 left
    NODE test2[4] = { 0 };
    Link(test2, 0, 1, 2);
    Link(test2, 1, 3, -1);
    cout << "test2: " << GetMaximumDistance(&test2[0]).nMaxDistance << endl;

    // P. 242 Graph 3-13 right
    NODE test3[9] = { 0 };
    Link(test3, 0, -1, 1);
    Link(test3, 1, 2, 3);
    Link(test3, 2, 4, -1);
    Link(test3, 3, 5, 6);
    Link(test3, 4, 7, -1);
    Link(test3, 5, -1, 8);
    cout << "test3: " << GetMaximumDistance(&test3[0]).nMaxDistance << endl;

    // P. 242 Graph 3-14
    // Same as Graph 3-2, not test

    // P. 243 Graph 3-15
    NODE test4[9] = { 0 };
    Link(test4, 0, 1, 2);
    Link(test4, 1, 3, 4);
    Link(test4, 3, 5, 6);
    Link(test4, 5, 7, -1);
    Link(test4, 6, -1, 8);
    cout << "test4: " << GetMaximumDistance(&test4[0]).nMaxDistance << endl;
    
    NODE test5[11] = { 0 };
    Link(test5, 0, 1, 2);
    Link(test5, 1, 3, 4);
    Link(test5, 3, 5, 6);
    Link(test5, 4, -1, 7);
    Link(test5, 5, 8, -1);
    Link(test5, 6, -1, 9);
    Link(test5, 7, -1, 10);
    cout << "test5: " << GetMaximumDistance(&test5[0]).nMaxDistance << endl;
    return 0;
}
#endif

#include <iostream>
#include <stdlib.h>
using namespace std;

struct BinaryTreeNode 
{
	int m_nValue;
	struct BinaryTreeNode *m_pLeft;
	struct BinaryTreeNode *m_pRight;
};

int maxDistance(BinaryTreeNode *root, int *max);
int	DistanceCore(BinaryTreeNode *root,int *max);
//�������,�������ǽ����Ķ������Ƿ���ȷ
void Traverse( BinaryTreeNode * root);
BinaryTreeNode* Construct(int *preorder, int *inorder, int lenght);
BinaryTreeNode* ConstructCore(int *startPreorder, int *endPreorder, int *startInorder, int *endInorder);
int InsertNodeAtMostRight(BinaryTreeNode * root, BinaryTreeNode * node);

int main(int argc, char* argv[])
{
	int preOrder[] = {5, 4, 8, 9, 6, 3, 18, 19, 2};
	int inOrder[] = {9, 8, 6, 3, 4, 5, 19, 18, 2};

	int max;

	//����
	BinaryTreeNode *parent = Construct(preOrder, inOrder, sizeof(inOrder) / sizeof(inOrder[0]));

	cout << "A���ĺ�������Ľ����" << endl;
	Traverse(parent);
	cout << endl;

	BinaryTreeNode *node1 = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
	BinaryTreeNode *node2 = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));

	node1->m_nValue = 0;
	node1->m_pLeft = NULL;
	node1->m_pRight = NULL;

	node2->m_nValue = 0;
	node2->m_pLeft = NULL;
	node2->m_pRight = NULL;

    maxDistance(parent, &max);
	cout <<"max distance of tree's nodes : " << max << endl;

	InsertNodeAtMostRight(parent, node1);
    maxDistance(parent, &max);
	cout <<"max distance of tree's nodes after insert node1: " << max << endl;

	InsertNodeAtMostRight(parent, node2);
    maxDistance(parent, &max);
	cout <<"max distance of tree's nodes after insert node2: " << max << endl;

	//���Լ����������ֻ��һ���ڵ�
    maxDistance(node2, &max);
	cout <<"just one node " << max << endl;

	//���Լ����������ֻ�ж����ڵ�
    maxDistance(node1, &max);
	cout <<"just two node " << max << endl;
	return 0;
}
 
BinaryTreeNode* Construct(int *preorder, int *inorder, int lenght)
{
	if (preorder == NULL || inorder == NULL || lenght <= 0) 
	{
		return NULL;
	}
	return ConstructCore(preorder, preorder + lenght - 1, inorder, inorder + lenght - 1);
}

BinaryTreeNode* ConstructCore(int *startPreorder, int *endPreorder, int *startInorder, int *endInorder)
{
	int rootValue = startPreorder[0];
	BinaryTreeNode *root = new BinaryTreeNode();
	root->m_nValue = rootValue;
	root->m_pLeft = root->m_pRight = NULL;

	if (startPreorder == endPreorder) 
	{//��������Ѿ������ˣ������ʱ��һ���ǲ������һ���ڵ㣬��Ӧ�����������if��䣬�����������������
		if (startInorder == endInorder && *startPreorder == *startInorder) 
		{
			return root;
		}
		else
		{
			cout << "Invalid input" << endl;
			exit(-1);
		}
	}
 
	int *rootInorder = startInorder;
	while (rootInorder <= endInorder && *rootInorder != rootValue) 
	{
		++rootInorder;
	}
	if (rootInorder <= endInorder && *rootInorder != rootValue) 
	{
		cout << "Invalid input" << endl;
		exit(-1);
	}

	int leftLength = rootInorder - startInorder;
	int *leftPreorderEnd = startPreorder + leftLength;

	if (leftLength > 0) 
	{
		root->m_pLeft = ConstructCore(startPreorder + 1, leftPreorderEnd, startInorder, rootInorder - 1);
	}
	if (leftLength < endPreorder - startPreorder) 
	{
		root->m_pRight = ConstructCore(leftPreorderEnd + 1, endPreorder, rootInorder + 1, endInorder);
	}

	return root;	
}

void Traverse( BinaryTreeNode * root)
{
	if (root == NULL) 
	{
		return;
	}
	else
	{
		Traverse(root->m_pLeft);
		Traverse(root->m_pRight);
		cout << root->m_nValue << "  ";
	}
}
int maxDistance(BinaryTreeNode *root, int *max)
{
	//�����������Ҫ�������ж�root��Ϊ�գ��Ҹ�max����ֵ
	if (root == NULL || max == NULL) 
	{
		return -1;
	}
	*max = 0;
	return DistanceCore(root, max);
}

int	DistanceCore(BinaryTreeNode *root, int *max)
{
	//����ڵ���Ҷ�ӽڵ㣬�򷵻�0�������
	if (root->m_pLeft == NULL && root->m_pRight == NULL) 
	{
		return 0;
	}

	//��������������������
	int lDistance = 0;
	int rDistance = 0;

	//��������Ϊ�գ����ص�ǰ�ڵ㵽��������������
	if (root->m_pLeft != NULL) 
	{
		lDistance = 1 + DistanceCore(root->m_pLeft, max);
	}

	if (root->m_pRight != NULL) 
	{
		rDistance = 1 + DistanceCore(root->m_pRight, max);
	}

	//��������ǰ�ڵ�ʱ���ܻ�õ�������
	if (lDistance + rDistance > *max) 
	{
		//���浱ǰ��õ�������
		*max = lDistance + rDistance;
	}
	//�������������У���Ƚϴ��һ��
	return lDistance > rDistance ? lDistance : rDistance;
}

//Ϊ�˲��Գ���д�ĸ��������������������ұ߲���һ���µĽڵ�
int InsertNodeAtMostRight(BinaryTreeNode * root, BinaryTreeNode * node)
{
	if (root == NULL || node == NULL) 
	{
		return -1;
	}

	while (root->m_pRight != NULL) 
	{
		root = root->m_pRight;
	}

	root->m_pRight = node;
	return 0;
}
