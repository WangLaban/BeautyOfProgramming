#include <iostream>
#include <algorithm>
using namespace std;
 
#define MAXN 1003
int A[MAXN][MAXN];
long long PS[MAXN][MAXN];

// MatrixSum(a, c, j)��ʾ�ڵ�a�к͵�c��֮��ĵ�j�е�����Ԫ�صĺ�
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
	// �������Ĳ��ֺ�
	for (i=1; i<=n; i++)
		for (j=1; j<=m; j++)
			PS[i][j] = A[i][j]+PS[i-1][j]+PS[i][j-1]-PS[i-1][j-1];

	int a, c;
	long long All = A[1][1];
	for (a=1; a<=n; a++)
		for (c=a; c<=n; c++)
		{
			// ���Ӿ������±߽���Ϊ��a�к͵�c�У�����Щ�Ӿ�����ȡ���ֵ
			long long Tail = MatrixSum(a, c, 1);
			
			for (j=2; j<=m; j++)
			{
				Tail = max(MatrixSum(a, c, j), 
					MatrixSum(a, c, j)+Tail); 
				All = max(Tail, All);
			}
		}
	cout << All;
}
