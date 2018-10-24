#include<iostream>
#include <limits>
using namespace std;

int main()
{
	int rg[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
	for(__int64 i =2123581660200; i < numeric_limits<__int64>::max(); i++)
	{
		int hit = 0, hit1 = -1, hit2 = -1;
		for(int j = 0; (j < sizeof(rg) / sizeof(int)) && (hit <= 2); j++)
		{
			if((i % rg[j]) != 0)
			{
				hit++;
				if(hit == 1)
				{
					hit1 = j;
				}
				else if(hit == 2)
				{
					hit2 = j;
				}
				else
				    break;
			}
		}
		if(hit == 2 && hit2 == hit1 + 1)
		{
			cout<<"found: "<<i<<endl;
			break;
		}
	}
	return 0;
}
