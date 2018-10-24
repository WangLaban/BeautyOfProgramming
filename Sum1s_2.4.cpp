#include<iostream>
using namespace std;

unsigned long long sum1s(unsigned long long n)
{
	unsigned long long iCount = 0;
	unsigned long long iFactor = 1;
	unsigned long long iLowerNum = 0;
	unsigned long long iCurrNum = 0;
	unsigned long long iHigherNum = 0;
	
	while(n / iFactor)
	{
		iLowerNum = n - (n / iFactor) * iFactor;
		iCurrNum = (n / iFactor) % 10;
		iHigherNum = n / (iFactor * 10);
		
		switch(iCurrNum)
		{
			case 0:
				iCount += iHigherNum * iFactor;
				break;
			case 1:
				iCount += iHigherNum * iFactor + iLowerNum + 1;
				break;
			default:
				iCount += (iHigherNum + 1) * iFactor;
		}
		iFactor *= 10;
	}
	return iCount;
}

int main()
{
	unsigned long long res = sum1s(1111111110);
	cout<<"res = "<<res<<endl;
	
	return 0;
}
