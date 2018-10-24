// N!末尾有多少个0 
#include<iostream>
using namespace std;

// Solution1:
// N! = K * 10^M, K不能被10整除，那么N!末尾有M个0
// 质因素分解，N! = 2^X * 3 ^ Y * 5 ^ Z... 
// M = min(X, Y) 
int FactorialEndWithZero1(unsigned int n)
{
	int res = 0;
	for(int i = 1; i <= n; i++)
	{
		int num = i;
		while(num % 5 == 0)
		{
			res++;
			num /= 5;
		}
	}
	return res;
}

// Solution2:
// Z = [N/5] + [N/5^2] + [N/5^3] + ...
// [N/5]表示不大于N的数中5的倍数贡献一个5，[N/5^2]表示不大于N的数中5^2的倍数再贡献一个5
int FactorialEndWithZero2(unsigned int n)
{
	int res = 0;
	while(n)
	{
		res += n / 5;
		n /= 5;
	}
	return res;
} 
int main()
{
	int res = FactorialEndWithZero2(126);
	cout<<"res = "<<res<<endl;
	return 0;
}
