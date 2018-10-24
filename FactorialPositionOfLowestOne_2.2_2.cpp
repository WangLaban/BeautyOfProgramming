// N!的二进制表示中最低位1的位置 
#include<iostream>
using namespace std;

// 判断最后一个二进制位是否为0：
// 若为0，则将此二进制数右移一位，即为商值
// 若为1，则这个二进制数是奇数，无法被2整除
// 结果为N!含有质因数2的个数 + 1 
// Solution1:
// N!中含有质因数2的个数，等于[N/2] + [N/4] + [N/8] + [N/16] + ... 
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
// N!中含有质因素2的个数，等于N减去N的二进制表示中1个数目
// 假设N = 11011(二进制表示) ，那么N!中含有质因数2的个数为 [N/2] + [N/4] + [N/8] + [N/16] + ...
// 即：
//   1101 + 110 + 11 + 1
// = (1000 + 100 + 1) + (100 + 10 + 1) + (10 + 1) + 1 
// = (1000 + 100 + 10 + 1) + (100 + 10 + 1) + 1
// = 1111 + 111 + 1
// = (10000 - 1) + (1000 - 1) + (10 - 1) + (1 - 1)
// = 11011 - (N二进制表示中1的个数) 
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
