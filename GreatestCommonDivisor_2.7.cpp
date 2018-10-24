#include<iostream>
using namespace std;

// Solution1: շת���
// ȱ�㣺���ڴ�������ȡģ���㿪����
int gcd(int x, int y)
{
	return (!y) ? x : gcd(y, x % y);
}

// Solution2: 
// ȱ�㣺������������
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
	if((x & 1) == 0)  //ע�⣺����==�����ȼ����ڰ�λ��&��������ֵ�����������
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
