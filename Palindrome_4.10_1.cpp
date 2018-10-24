#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

// (he) ^ 2 = she
int main()
{
	bool flag;
	bool isUsed[10];
	int he, she, t, v;
	for(he = 10; he < 100; he++)
	{
		flag = true;
		memset(isUsed, 0, sizeof(isUsed));
		t = he;
		for(int i = 0; i < 2; i++)
		{
			v = t % 10;
			t /= 10;
			if(isUsed[v])
			    flag = false;
			else
			    isUsed[v] = 1;
		}
		she = pow(he, 2);
		if(flag && he == she % 100 && she >= 100 && she < 1000 && !isUsed[she / 100])
		{
		    cout<<he<<" * "<<he<<" = "<<pow(he, 2)<<endl;
		}
	}
	return 0;
}
