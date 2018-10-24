#if 0
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define MAXN 101
#define MAXSUM 100000
int A[MAXN];
bool dp[MAXN][MAXSUM];

// 题目可转换为从2n个数中选出n个数，其和尽量接近于给定值sum/2
// 外阶段：在前k1个数中进行选择，k1=1,2...2*n。
// 内阶段：从这k1个数中任意选出k2个数，k2=1,2...k1。
// 状态：这k2个数的和为s，s=1,2...sum/2。
// 决策：决定这k2个数的和有两种决策，一个是这k2个数中包含第k1个数，另一个是不包含第k1个数。
// dp[k][s]表示从前k个数中取任意个数，且这些数之和为s的取法是否存在。

// 注意：如果数组中有负数的话，上面的背包策略就不能使用了（因为第三重循环中的s是作为数组的下标的，
// 不能出现负数的），需要将数组中的所有数组都加上最小的那个负数的绝对值，将数组中的元素全部都增加
// 一定的范围，全部转化为正数，然后再使用上面的背包策略就可以解决了
int main()
{
	int n, i, k1, k2, s, u;
	cin >> n;
	for (i=1; i<=2*n; i++)
		cin >> A[i];
	int sum = 0;
	for (i=1; i<=2*n; i++)
		sum += A[i];
	memset(dp,0,sizeof(dp));
	dp[0][0]=true;
	// 对于dp[k][s]要进行u次决策，由于阶段k的选择受到决策的限制，
	// 这里决策选择不允许重复，但阶段可以重复，比较特别
	for (k1=1; k1<=2*n; k1++)				// 外阶段k1
		for (k2=min(k1,n); k2>=1; k2--)		// 内阶段k2
			for (s=1; s<=sum/2; s++)	// 状态s
				// 有两个决策包含或不包含元素k1
				if (s>=A[k1] && dp[k2-1][s-A[k1]])
					dp[k2][s] = true;
	// 确定最接近的给定值sum/2的和
	for (s=sum/2; s>=1 && !dp[n][s]; s--);
	printf("the differece between two sub array is %d\n", sum-2*s);
}
#endif

// S(k, 1) = {A[i] | 1<= i <= k}
// S(k, k) = {A[1]+A[2]+…+A[k]}
// S(k, i) = S(k-1, i) U {A[k] + x | x属于S(k-1, i-1) }
#include<iostream>
#include<cstring>
using namespace std;

//有一个没有排序，元素个数为2N的正整数数组。要求把它分割为元素个数为N的两个数组，并使两个子数组的和最接近。
int arr[] = {0,1,5,7,8,9,6,3,11,20,17};
const int N=5;
const int SUM = 87;

// 模仿动态规划解0-1背包问题的策略
int solve1()
{
    int i , j , s;
    int dp[2*N+1][N+1][SUM/2+2];

    /*
    用dp(i,j,c)来表示从前i个元素中取j个、且这j个元素之和不超过c的最佳(大)方案，在这里i>=j,c<=S
    状态转移方程：   
    限第i个物品　　　　　　　不取　　
    dp(i,j,c)=max{dp(i-1,j-1,c-a[i])+a[i]，dp(i-1,j,c)}
    dp(2N,N,SUM/2+1)就是题目的解。
    */
    //初始化
    memset(dp,0,sizeof(dp));

    for(i = 1 ; i <= 2*N ; ++i)
    {
        for(j = 1 ; j <= min(i,N) ; ++j)
        {
            for(s = SUM/2+1 ; s >= arr[i] ; --s)
            {
                dp[i][j][s] = max(dp[i-1][j-1][s-arr[i]]+arr[i] , dp[i-1][j][s]);
            }
        }
    }

    //因为这为最终答案　dp[2*N][N][SUM/2+1];
    i=2*N , j=N , s=SUM/2+1;
    while(i > 0)
    {
        if(dp[i][j][s] == dp[i-1][j-1][s-arr[i]]+arr[i])   //判定这个状态是由哪个状态推导出来的
        {
            cout<<arr[i]<<" ";    //取中arr[i]
            j--;
            s -= arr[i];
        }    
        i--;
    }
    cout<<endl;
    return dp[2*N][N][SUM/2+1];
}

int solve2()
{
    int i , j , s;
    int dp[N+1][SUM/2+2];     //取Ｎ+１件物品，总和不超过SUM/2+2，的最大值是多少 
    memset(dp,0,sizeof(dp));    //初始状态都为0

    for(i = 1 ; i <= 2*N ; ++i)
    {
        for(j = 1 ; j <= min(i,N) ; ++j)
        {
            for(s = SUM/2+1 ; s >= arr[i] ; --s)    //01背包从大到小，可以省空间，即最外层的空间
            {
                dp[j][s] = max(dp[j-1][s-arr[i]]+arr[i] , dp[j][s]); 
            }
        }
    }
    //要求最优解则　空间不能优化，
    return dp[N][SUM/2+1];
}

int solve3()
{
    int i , j , s;
    int isOK[N+1][SUM/2+2]; //isOK[i][v]表示是否可以找到i个数，使得它们之和等于v
    memset(isOK,0,sizeof(isOK));    //都不合法
    //注意初始化
    isOK[0][0] = 1; //可以,取0件物品，总合为0，是合法的

    for(i = 1 ; i <= 2*N ; ++i)
    {
        for( j = 1 ; j <= min(i,N) ; ++j)
        {
            for(s = SUM/2+1 ; s >= arr[i] ; --s) //从大到小，数组少了一维
            {
                if( isOK[j-1][s-arr[i]] )
                    isOK[j][s] = 1;
            }
        }
    }
    for(s = SUM/2+1 ; s >= 0 ; --s)
    {
        if(isOK[N][s])
            return s;
    }

    //要求最优解则空间不能优化
    return 0;
}

int main(void)
{
    int s1 = solve1();
    int s2 = solve2();
    int s3 = solve3();
    cout<<"s1="<<s1<<endl;
    cout<<"s2="<<s2<<endl;
    cout<<"s3="<<s3<<endl;
    system("pause");
    return 0;
}
