#include<iostream>
#include<cstring>
using namespace std;

int main()
{
	bool flag;
	bool isUsed[10];
	int number, revert_number, t, v;
	for(number = 10000; number < 100000; number++)
	{
		flag = true;
		memset(isUsed, 0, sizeof(isUsed));
		t = number;
		revert_number = 0;
		for(int i = 0; i < 5; i++)
		{
			v = t % 10;;
			revert_number = revert_number * 10 + v;
			t /= 10;
			if(isUsed[v])
			    flag = false;
			else
			    isUsed[v] = 1;
		}
		if(flag && (revert_number % number == 0))
		{
			v = revert_number / number;
			if(v < 10 && !isUsed[v])
			    cout<<number<<" * "<<v<<" = "<<revert_number<<endl;
		}
	}
	return 0;
}
