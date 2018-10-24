#include <iostream>
#include <cmath>
#include <algorithm>
 
using namespace std;
 
// �߶����Ľ��
struct SegNode
{
  int low, high;	// �߶ε����˵�����
  int ncover;	// �߶α����ǵĴ���
  SegNode *left;	// ����������
  SegNode *right;	// ����������
  SegNode() {low=high=0;ncover=0;
	left=right=NULL;}
};
 
// �����߶���������һ����ȫ������
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
 
// ���߶����в����߶Σ������߶�(low,high)�������߶���
void InsertSegTree(SegNode *tree, int low, int high)
{
  // �������
  if (low<=tree->low && tree->high<=high)
    tree->ncover++;
  else if (tree->high-tree->low > 1)
  {
    int m = (tree->low+tree->high)/2;
    if (low < m) InsertSegTree(tree->left, low, high);
    if (m < high) InsertSegTree(tree->right, low, high);
  }
}
 
// ���߶�����ɾ���߶�
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
 
// �߶������Ƿ�����߶�(low,high)
bool FindSegTree(SegNode *tree, int low, int high)
{
	// ����ǰ���䱻���ǣ����߶�(low,high)���ڵ�ǰ�����򷵻ظ���
	if (tree->ncover && tree->low <= low && high <= tree->high )
		return true;
	// ��(low,high)û����ǰ���串�ǣ������Ϊ���Σ�
	// �ֱ����Ƿ��ӽ���ʾ�����串��
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
 
// ��ʾ��ֱ������߶�
struct Line
{
  int starty, endy;	// ���ߵĳ���
  int x;		// ���ߵ�λ��
  bool inout;	// �����ǳ����ε���߻����ұ�
  bool operator<(const Line& a) const{	// ����x�����������
    return x<a.x;
  }
};
 
// ������ֱ������߶�
Line lines[INF];
// �Ժ���Ԫ�߶ν��з���
int index[INF];
int nCnt = 0;
 
// ��ȡkey��λ��
int GetIndex(int key)
{
	// �ö��ֲ��Ҳ��key��index�е�λ��
	return lower_bound(index,index+nCnt,key)-index;
}
 
// ��ȡkey��λ�û����С���������λ��
int GetLower(int key)
{
	size_t pos = lower_bound(index,index+nCnt,key)-index;
	if (key == index[pos]) return pos;
	else return pos-1;
}
 
// ��ȡkey��λ�û���������С����λ��
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
  // ��ȡnRec�����ڵ�����
  for (i=0; i<nRec; i++)
  {
    cin >> x[0] >> y[0] >> x[1] >> y[1];
	// ��¼ÿ�������ε�������ֱ��
    lines[2*i].x=x[0];		lines[2*i+1].x=x[1];
    lines[2*i].starty=lines[2*i+1].starty=min(y[0],y[1]);
    lines[2*i].endy=lines[2*i+1].endy=max(y[0],y[1]);
    lines[2*i].inout=LEFT;	lines[2*i+1].inout=RIGHT;
	// ����ֱ���߶ν�����ɢ��
    index[2*i]=y[0];		index[2*i+1]=y[1];
  }
  // ����ѯ�Ĵ�������
  Line search[2];
  cin >> x[0] >> y[0] >> x[1] >> y[1];
  search[0].x=x[0];			search[1].x=x[1];
  search[0].starty=search[1].starty=min(y[0],y[1]);
  search[0].endy=search[1].endy=max(y[0],y[1]);
  search[0].inout=LEFT;		search[1].inout=RIGHT;
  // ��x�����������O(nlogn)
  sort(index, index+2*nRec);
  sort(lines, lines+2*nRec);
  // �ų�index�����е��ظ�����O(n)
  for (i=1; i<2*nRec; i++)
    if (index[i]!=index[i-1])
      index[nCnt++] = index[i-1];
  index[nCnt++] = index[2*nRec-1];
  // �����߶���
  SegNode *tree;
  BuildSegTree(tree, index, 0, nCnt-1);
  // ���ʲ��ҵ�ʱ�临�Ӷ�ΪO(nlogn)
  bool res;
  InsertSegTree(tree, GetIndex(lines[0].starty), GetIndex(lines[0].endy));
  for (i=1; i<2*nRec; i++)
  {
    if (lines[i].inout==LEFT)	// �����ڵ���߽磬��������߶���
      InsertSegTree(tree, GetIndex(lines[i].starty), GetIndex(lines[i].endy));
    else						// �����ڵ��ұ߽磬����ɾ���߶���
      DeleteSegTree(tree, GetIndex(lines[i].starty), GetIndex(lines[i].endy));
	if (lines[i].x!=lines[i-1].x && search[0].x < lines[i+1].x && search[1].x > lines[i].x)
	{
		// �Ӵ��鴰���������߽翪ʼ��ѯֱ�����ұ߽������ѯ
		res = FindSegTree(tree, GetLower(search[0].starty), GetUpper(search[0].endy));
		if (!res) break;
	}else if (search[1].x <= lines[i].x)
		break;
  }
  if (res) printf("Yes\n");
  else	printf("No\n");
  return 0;
}
