// N!ĩβ�ж��ٸ�0 
#include<iostream>
using namespace std;

// Solution1:
// N! = K * 10^M, K���ܱ�10��������ôN!ĩβ��M��0
// �����طֽ⣬N! = 2^X * 3 ^ Y * 5 ^ Z... 
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
// [N/5]��ʾ������N������5�ı�������һ��5��[N/5^2]��ʾ������N������5^2�ı����ٹ���һ��5
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
