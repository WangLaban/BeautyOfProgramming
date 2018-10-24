#include<iostream>
using namespace std;

// Solution1: 辗转相除
// 缺点：对于大整数，取模运算开销大
int gcd(int x, int y)
{
	return (!y) ? x : gcd(y, x % y);
}

// Solution2: 
// 缺点：迭代次数过多
int gcd2(int x, int y)
{
	if(x < y)
	    return gcd2(y - x, x);
	else if(x == y)
	    return x;
	else
	    return gcd2(x - y, y);
}

// Solution3: 
int gcd3(int x, int y)
{
	if(x == y)
	    return x;
	if((x & 1) == 0)  //注意：等于==的优先级高于按位与&，所以左值必须加上括号
	//if(!(x & 1))
	{
		if((y & 1) == 0)
		//if(!(y & 1))
		    return (gcd3(x >> 1, y >> 1) << 1);
		else
		    return gcd3(x >> 1, y);
	}
	else
	{
		if((y & 1) == 0)
		//if(!(y & 1))
		    return gcd3(x, y >> 1);
		else
		    return (x > y) ? gcd3(x - y, y) : gcd3(y - x, x);
	}
}
int main()
{
	int x = 42, y = 30;
	int res = gcd3(x, y);
	cout<<"res = "<<res<<endl;
	
	return 0;
}
