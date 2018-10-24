#include <iostream>
#include <algorithm>
using namespace std;
 
#define MAXN 103
int A[MAXN][MAXN][MAXN];
int PS[MAXN][MAXN][MAXN];
 
inline int CubeSum(int a, int b, int c, int d, int i, int j)
{
	return PS[b][d][j]-PS[a-1][d][j]-PS[b][c-1][j]-PS[b][d][i-1]+
		PS[a-1][c-1][j]+PS[a-1][d][i-1]+PS[b][c-1][i-1]-PS[a-1][c-1][i-1];
}
 
int main()
{
	int n, m, h, i, j, k;
	cin >> n >> m >> h;
	for (i=1; i<=n; i++)
		for (j=1; j<=m; j++)
			for (k=1; k<=h; k++)
				cin >> A[i][j][k];
	for (i=0; i<=n; i++)
		for (j=0; j<=m; j++)
			PS[i][j][0] = 0;
	for (i=0; i<=n; i++)
		for (k=0; k<=h; k++)
			PS[i][0][k] = 0;
	for (j=0; j<=m ; j++)
		for (k=0; k<=h; k++)
			PS[0][j][k] = 0;
	// 计算长方体的部分和
	for (i=1; i<=n; i++)
	for (j=1; j<=m; j++)
	for (k=1; k<=h; k++)
		PS[i][j][k] = A[i][j][k]+PS[i-1][j][k]+PS[i][j-1][k]+PS[i][j][k-1]-
			PS[i-1][j-1][k]-PS[i-1][j][k-1]-PS[i][j-1][k-1]+PS[i-1][j-1][k-1];
	int a, b, c, d;
	int All = A[1][1][1];
	// 限制第一维的取值范围
	for (a=1; a<=n; a++)
	for (b=a; b<=n; b++)
		// 限制第二维的取值范围
		for (c=1; c<=m; c++)
		for (d=c; d<=m; d++)
		{
			// 只剩下最后一维没有确定，利用一维部分和的方法
			int Tail = CubeSum(a,b,c,d,1,1);
			for (j=2; j<=k; j++)
			{
				int cur = CubeSum(a,b,c,d,j,j);
				Tail = max(Tail+cur, cur);
				All = max(Tail, All);
			}
		}
	cout << All;
}
