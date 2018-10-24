#if 0
// 数据结构定义
struct NODE
{
    NODE* pLeft;        // 左子树
    NODE* pRight;       // 右子树
    int nMaxLeft;       // 左子树中的最长距离
    int nMaxRight;      // 右子树中的最长距离
    char chValue;       // 该节点的值
};
 
int nMaxLen = 0;
 
// 寻找树中最长的两段距离
void FindMaxLen(NODE* pRoot)
{
    // 遍历到叶子节点，返回
    if(pRoot == NULL)
    {
        return;
    }
 
    // 如果左子树为空，那么该节点的左边最长距离为0
    if(pRoot -> pLeft == NULL)
    {
        pRoot -> nMaxLeft = 0; 
    }
 
    // 如果右子树为空，那么该节点的右边最长距离为0
    if(pRoot -> pRight == NULL)
    {
        pRoot -> nMaxRight = 0;
    }
 
    // 如果左子树不为空，递归寻找左子树最长距离
    if(pRoot -> pLeft != NULL)
    {
        FindMaxLen(pRoot -> pLeft);
    }
 
    // 如果右子树不为空，递归寻找右子树最长距离
    if(pRoot -> pRight != NULL)
    {
        FindMaxLen(pRoot -> pRight);
    }
 
    // 计算左子树最长节点距离
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
 
    // 计算右子树最长节点距离
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
 
    // 更新最长距离
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
//后序遍历,用于我们建立的二叉树是否正确
void Traverse( BinaryTreeNode * root);
BinaryTreeNode* Construct(int *preorder, int *inorder, int lenght);
BinaryTreeNode* ConstructCore(int *startPreorder, int *endPreorder, int *startInorder, int *endInorder);
int InsertNodeAtMostRight(BinaryTreeNode * root, BinaryTreeNode * node);

int main(int argc, char* argv[])
{
	int preOrder[] = {5, 4, 8, 9, 6, 3, 18, 19, 2};
	int inOrder[] = {9, 8, 6, 3, 4, 5, 19, 18, 2};

	int max;

	//建树
	BinaryTreeNode *parent = Construct(preOrder, inOrder, sizeof(inOrder) / sizeof(inOrder[0]));

	cout << "A树的后序遍历的结果：" << endl;
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

	//测试极端情况，即只有一个节点
    maxDistance(node2, &max);
	cout <<"just one node " << max << endl;

	//测试极端情况，即只有二个节点
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
	{//先序遍历已经结束了，那这个时候一定是插入最后一个节点，则应该满足下面的if语句，否则输入的数据有误
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
	//这个函数的主要功能是判断root不为空，且给max赋初值
	if (root == NULL || max == NULL) 
	{
		return -1;
	}
	*max = 0;
	return DistanceCore(root, max);
}

int	DistanceCore(BinaryTreeNode *root, int *max)
{
	//如果节点是叶子节点，则返回0——深度
	if (root->m_pLeft == NULL && root->m_pRight == NULL) 
	{
		return 0;
	}

	//保存左右子树的最大深度
	int lDistance = 0;
	int rDistance = 0;

	//左子树不为空，返回当前节点到左子树的最大深度
	if (root->m_pLeft != NULL) 
	{
		lDistance = 1 + DistanceCore(root->m_pLeft, max);
	}

	if (root->m_pRight != NULL) 
	{
		rDistance = 1 + DistanceCore(root->m_pRight, max);
	}

	//遍历到当前节点时，能获得的最大距离
	if (lDistance + rDistance > *max) 
	{
		//保存当前获得的最大距离
		*max = lDistance + rDistance;
	}
	//返回左右子树中，深度较大的一个
	return lDistance > rDistance ? lDistance : rDistance;
}

//为了测试程序写的辅助函数，在树的最最右边插入一个新的节点
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
