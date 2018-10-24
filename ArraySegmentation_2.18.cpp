#if 0
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define MAXN 101
#define MAXSUM 100000
int A[MAXN];
bool dp[MAXN][MAXSUM];

// ��Ŀ��ת��Ϊ��2n������ѡ��n��������;����ӽ��ڸ���ֵsum/2
// ��׶Σ���ǰk1�����н���ѡ��k1=1,2...2*n��
// �ڽ׶Σ�����k1����������ѡ��k2������k2=1,2...k1��
// ״̬����k2�����ĺ�Ϊs��s=1,2...sum/2��
// ���ߣ�������k2�����ĺ������־��ߣ�һ������k2�����а�����k1��������һ���ǲ�������k1������
// dp[k][s]��ʾ��ǰk������ȡ�������������Щ��֮��Ϊs��ȡ���Ƿ���ڡ�

// ע�⣺����������и����Ļ�������ı������ԾͲ���ʹ���ˣ���Ϊ������ѭ���е�s����Ϊ������±�ģ�
// ���ܳ��ָ����ģ�����Ҫ�������е��������鶼������С���Ǹ������ľ���ֵ���������е�Ԫ��ȫ��������
// һ���ķ�Χ��ȫ��ת��Ϊ������Ȼ����ʹ������ı������ԾͿ��Խ����
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
	// ����dp[k][s]Ҫ����u�ξ��ߣ����ڽ׶�k��ѡ���ܵ����ߵ����ƣ�
	// �������ѡ�������ظ������׶ο����ظ����Ƚ��ر�
	for (k1=1; k1<=2*n; k1++)				// ��׶�k1
		for (k2=min(k1,n); k2>=1; k2--)		// �ڽ׶�k2
			for (s=1; s<=sum/2; s++)	// ״̬s
				// ���������߰����򲻰���Ԫ��k1
				if (s>=A[k1] && dp[k2-1][s-A[k1]])
					dp[k2][s] = true;
	// ȷ����ӽ��ĸ���ֵsum/2�ĺ�
	for (s=sum/2; s>=1 && !dp[n][s]; s--);
	printf("the differece between two sub array is %d\n", sum-2*s);
}
#endif

// S(k, 1) = {A[i] | 1<= i <= k}
// S(k, k) = {A[1]+A[2]+��+A[k]}
// S(k, i) = S(k-1, i) U {A[k] + x | x����S(k-1, i-1) }
#include<iostream>
#include<cstring>
using namespace std;

//��һ��û������Ԫ�ظ���Ϊ2N�����������顣Ҫ������ָ�ΪԪ�ظ���ΪN���������飬��ʹ����������ĺ���ӽ���
int arr[] = {0,1,5,7,8,9,6,3,11,20,17};
const int N=5;
const int SUM = 87;

// ģ�¶�̬�滮��0-1��������Ĳ���
int solve1()
{
    int i , j , s;
    int dp[2*N+1][N+1][SUM/2+2];

    /*
    ��dp(i,j,c)����ʾ��ǰi��Ԫ����ȡj��������j��Ԫ��֮�Ͳ�����c�����(��)������������i>=j,c<=S
    ״̬ת�Ʒ��̣�   
    �޵�i����Ʒ����������������ȡ����
    dp(i,j,c)=max{dp(i-1,j-1,c-a[i])+a[i]��dp(i-1,j,c)}
    dp(2N,N,SUM/2+1)������Ŀ�Ľ⡣
    */
    //��ʼ��
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

    //��Ϊ��Ϊ���մ𰸡�dp[2*N][N][SUM/2+1];
    i=2*N , j=N , s=SUM/2+1;
    while(i > 0)
    {
        if(dp[i][j][s] == dp[i-1][j-1][s-arr[i]]+arr[i])   //�ж����״̬�����ĸ�״̬�Ƶ�������
        {
            cout<<arr[i]<<" ";    //ȡ��arr[i]
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
    int dp[N+1][SUM/2+2];     //ȡ��+������Ʒ���ܺͲ�����SUM/2+2�������ֵ�Ƕ��� 
    memset(dp,0,sizeof(dp));    //��ʼ״̬��Ϊ0

    for(i = 1 ; i <= 2*N ; ++i)
    {
        for(j = 1 ; j <= min(i,N) ; ++j)
        {
            for(s = SUM/2+1 ; s >= arr[i] ; --s)    //01�����Ӵ�С������ʡ�ռ䣬�������Ŀռ�
            {
                dp[j][s] = max(dp[j-1][s-arr[i]]+arr[i] , dp[j][s]); 
            }
        }
    }
    //Ҫ�����Ž��򡡿ռ䲻���Ż���
    return dp[N][SUM/2+1];
}

int solve3()
{
    int i , j , s;
    int isOK[N+1][SUM/2+2]; //isOK[i][v]��ʾ�Ƿ�����ҵ�i������ʹ������֮�͵���v
    memset(isOK,0,sizeof(isOK));    //�����Ϸ�
    //ע���ʼ��
    isOK[0][0] = 1; //����,ȡ0����Ʒ���ܺ�Ϊ0���ǺϷ���

    for(i = 1 ; i <= 2*N ; ++i)
    {
        for( j = 1 ; j <= min(i,N) ; ++j)
        {
            for(s = SUM/2+1 ; s >= arr[i] ; --s) //�Ӵ�С����������һά
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

    //Ҫ�����Ž���ռ䲻���Ż�
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
