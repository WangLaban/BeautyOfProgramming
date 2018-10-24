#include <iostream>
#include <cmath>
#include <algorithm>
 
using namespace std;
 
// 线段树的结点
struct SegNode
{
  int low, high;	// 线段的两端点索引
  int ncover;	// 线段被覆盖的次数
  SegNode *left;	// 结点的左子树
  SegNode *right;	// 结点的右子树
  SegNode() {low=high=0;ncover=0;
	left=right=NULL;}
};
 
// 构造线段树，它是一个完全二叉树
void BuildSegTree(SegNode *&tree, int *index, int low, int high)
{
  if (low < high)
  {
    tree = new SegNode;
    tree->low = low;
    tree->high = high;
    if (high-low>1)
    {
      int m = (low+high)/2;
      BuildSegTree(tree->left, index, low, m);
      BuildSegTree(tree->right, index, m, high);
    }
  }
}
 
// 往线段树中插入线段，即用线段(low,high)来覆盖线段树
void InsertSegTree(SegNode *tree, int low, int high)
{
  // 先序遍历
  if (low<=tree->low && tree->high<=high)
    tree->ncover++;
  else if (tree->high-tree->low > 1)
  {
    int m = (tree->low+tree->high)/2;
    if (low < m) InsertSegTree(tree->left, low, high);
    if (m < high) InsertSegTree(tree->right, low, high);
  }
}
 
// 从线段树中删除线段
void DeleteSegTree(SegNode *tree, int low, int high)
{
  if (low<=tree->low && tree->high<=high)
    tree->ncover--;
  else if (tree->high-tree->low > 1)
  {
    int m = (tree->low+tree->high)/2;
    if (low < m) DeleteSegTree(tree->left, low, high);
    if (m < high) DeleteSegTree(tree->right, low, high);
  }
}
 
// 线段树中是否包含线段(low,high)
bool FindSegTree(SegNode *tree, int low, int high)
{
	// 若当前区间被覆盖，且线段(low,high)属于当前区间则返回覆盖
	if (tree->ncover && tree->low <= low && high <= tree->high )
		return true;
	// 若(low,high)没被当前区间覆盖，则将其分为两段，
	// 分别考虑是否被子结点表示的区间覆盖
	else if (tree->high - tree->low > 1)
	{
		int m = (tree->low + tree->high) >> 1;
		bool ret = true;
		if (low<m) ret = FindSegTree(tree->left, low, high<m?high:m);
		if (!ret)  return false;
		if (m<high) ret = FindSegTree(tree->right, m<low?low:m, high);
		if (!ret)  return false;
		return true;
	}
	return false;
}
 
#define LEFT  true
#define RIGHT false
#define INF 10000
 
// 表示竖直方向的线段
struct Line
{
  int starty, endy;	// 竖线的长度
  int x;		// 竖线的位置
  bool inout;	// 竖线是长方形的左边还是右边
  bool operator<(const Line& a) const{	// 依据x坐标进行排序
    return x<a.x;
  }
};
 
// 所有竖直方向的线段
Line lines[INF];
// 对横向超元线段进行分组
int index[INF];
int nCnt = 0;
 
// 获取key的位置
int GetIndex(int key)
{
	// 用二分查找查出key在index中的位置
	return lower_bound(index,index+nCnt,key)-index;
}
 
// 获取key的位置或比它小的最大数的位置
int GetLower(int key)
{
	size_t pos = lower_bound(index,index+nCnt,key)-index;
	if (key == index[pos]) return pos;
	else return pos-1;
}
 
// 获取key的位置或比它大的最小数的位置
int GetUpper(int key)
{
	return lower_bound(index,index+nCnt,key)-index;
}
 
int main()
{
  int nRec;
  cin >> nRec;
  int i, j;
  int x[2], y[2];
  // 读取nRec个窗口的数据
  for (i=0; i<nRec; i++)
  {
    cin >> x[0] >> y[0] >> x[1] >> y[1];
	// 记录每个长方形的两条竖直边
    lines[2*i].x=x[0];		lines[2*i+1].x=x[1];
    lines[2*i].starty=lines[2*i+1].starty=min(y[0],y[1]);
    lines[2*i].endy=lines[2*i+1].endy=max(y[0],y[1]);
    lines[2*i].inout=LEFT;	lines[2*i+1].inout=RIGHT;
	// 对竖直的线段进行离散化
    index[2*i]=y[0];		index[2*i+1]=y[1];
  }
  // 待查询的窗口区域
  Line search[2];
  cin >> x[0] >> y[0] >> x[1] >> y[1];
  search[0].x=x[0];			search[1].x=x[1];
  search[0].starty=search[1].starty=min(y[0],y[1]);
  search[0].endy=search[1].endy=max(y[0],y[1]);
  search[0].inout=LEFT;		search[1].inout=RIGHT;
  // 对x坐标进行排序O(nlogn)
  sort(index, index+2*nRec);
  sort(lines, lines+2*nRec);
  // 排除index数组中的重复数据O(n)
  for (i=1; i<2*nRec; i++)
    if (index[i]!=index[i-1])
      index[nCnt++] = index[i-1];
  index[nCnt++] = index[2*nRec-1];
  // 建立线段树
  SegNode *tree;
  BuildSegTree(tree, index, 0, nCnt-1);
  // 单词查找的时间复杂度为O(nlogn)
  bool res;
  InsertSegTree(tree, GetIndex(lines[0].starty), GetIndex(lines[0].endy));
  for (i=1; i<2*nRec; i++)
  {
    if (lines[i].inout==LEFT)	// 遇窗口的左边界，将其加入线段树
      InsertSegTree(tree, GetIndex(lines[i].starty), GetIndex(lines[i].endy));
    else						// 遇窗口的右边界，将其删出线段树
      DeleteSegTree(tree, GetIndex(lines[i].starty), GetIndex(lines[i].endy));
	if (lines[i].x!=lines[i-1].x && search[0].x < lines[i+1].x && search[1].x > lines[i].x)
	{
		// 从待查窗口区域的左边界开始查询直到其右边界结束查询
		res = FindSegTree(tree, GetLower(search[0].starty), GetUpper(search[0].endy));
		if (!res) break;
	}else if (search[1].x <= lines[i].x)
		break;
  }
  if (res) printf("Yes\n");
  else	printf("No\n");
  return 0;
}
