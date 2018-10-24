// N!�Ķ����Ʊ�ʾ�����λ1��λ�� 
#include<iostream>
using namespace std;

// �ж����һ��������λ�Ƿ�Ϊ0��
// ��Ϊ0���򽫴˶�����������һλ����Ϊ��ֵ
// ��Ϊ1������������������������޷���2����
// ���ΪN!����������2�ĸ��� + 1 
// Solution1:
// N!�к���������2�ĸ���������[N/2] + [N/4] + [N/8] + [N/16] + ... 
int FactorialPositionOfLowestOne(unsigned int n)
{
	int res = 0;
	while(n)
	{
		n >>= 1;
		res += n;
	} 
	return ++res;
} 

// Solution2:
// N!�к���������2�ĸ���������N��ȥN�Ķ����Ʊ�ʾ��1����Ŀ
// ����N = 11011(�����Ʊ�ʾ) ����ôN!�к���������2�ĸ���Ϊ [N/2] + [N/4] + [N/8] + [N/16] + ...
// ����
//   1101 + 110 + 11 + 1
// = (1000 + 100 + 1) + (100 + 10 + 1) + (10 + 1) + 1 
// = (1000 + 100 + 10 + 1) + (100 + 10 + 1) + 1
// = 1111 + 111 + 1
// = (10000 - 1) + (1000 - 1) + (10 - 1) + (1 - 1)
// = 11011 - (N�����Ʊ�ʾ��1�ĸ���) 
int countBitOne(unsigned int num)
{
	int res = 0;
	while(num)
	{
		num &= (num - 1);
		res++;
	}
	return res;
} 
int FactorialPositionOfLowestOne2(unsigned int n)
{
	int res = n - countBitOne(n) + 1;
}
 
int main()
{
	int res = FactorialPositionOfLowestOne2(27);
	cout<<"res = "<<res<<endl;
	
	return 0;
}
