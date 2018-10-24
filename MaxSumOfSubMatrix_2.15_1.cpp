#include <iostream>
#include <algorithm>
using namespace std;
 
#define MAXN 1003
int A[MAXN][MAXN];
long long PS[MAXN][MAXN];
 
// MatrixSum(a, c, j)表示在第a行和第c行之间的第j列的所有元素的和
// =  PS[c][j]- PS[a-1][j] - PS[c][j-1] + PS[a-1][j-1]
inline long long MatrixSum(int a, int c, int j)
{
	return PS[c][j]-PS[c][j-1]-PS[a-1][j]+PS[a-1][j-1];
}
 
int main()
{
	int m, n, i, j;
	cin >> n >> m;
	for (i=1; i<=n; i++)
		for (j=1; j<=m; j++)
			cin >> A[i][j];
	for (i=0; i<=n; i++)
		PS[i][0] = 0;
	for (j=0; j<=m; j++)
		PS[0][j] = 0;
	// 计算矩阵的部分和
	for (i=1; i<=n; i++)
		for (j=1; j<=m; j++)
			PS[i][j] = A[i][j]+PS[i-1][j]+PS[i][j-1]-PS[i-1][j-1];
	int a, c;
	long long All = A[1][1];
	// 上下边界不会跨过第n行和第1行
	for (a=1; a<=n; a++)
		for (c=a; c<=n; c++)
		{	
			// 将子矩阵上下边界设为第a行和第c行
			// 左右边界不会跨过第m列和第1列
			long long Tail = MatrixSum(a, c, 1);
			int sind = 1, tind = 1;
			for (j=2; j<=m; j++)
			{
				/*Tail = max(MatrixSum(a, c, j), 
					MatrixSum(a, c, j)+Tail); 
				All = max(Tail, All);*/
				if(MatrixSum(a, c, j) > MatrixSum(a, c, j) + Tail)
				{
					Tail = MatrixSum(a, c, j);
					sind = j;
				}
				else
				{
					Tail = MatrixSum(a, c, j) + Tail;
				}
				if(Tail > All)
				{
					All = Tail;
					tind = j;
				}
			}
			// 左右边界会跨过第m列和第1列
			long long Sum = MatrixSum(a, c, 1);
			if(Sum > 0)
			    tind = 1;
			long long Start = Sum;
			for (i=2; i< sind; i++)
			{
				Sum += MatrixSum(a, c, i);
				if (Sum > Start) {Start = Sum; tind = i;}
			}
			//cout<<"a = "<<a<<" c = "<<c<<" sind = "<<sind<<" tind = "<<tind<<" All = "<<All<<" Start = "<<Start<<" Tail = "<<Tail<<endl;
			if(Start + Tail > All)
			{
				All = Start + Tail;
			}
		}
	cout << All;
}
