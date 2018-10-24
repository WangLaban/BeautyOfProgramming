// 1.8拓展问题1：往上爬一个楼层，要耗费k单位的能量；往下走一个楼层，只需耗费1单位的能量 
#include<iostream>
#include<vector>
using namespace std;

#define MAX_FLOOR 10

void controlElevator(vector<int> persons, int &minPowers, int &targetFloor, int weight)
{
	int N1 = 0, N2 = persons[1], N3 = 0;
	for(int i = 2; i < MAX_FLOOR; i++)
	{
		N3 += persons[i];
		minPowers += persons[i] * (i - 1) * weight;
	}
	for(int i = 2; i < MAX_FLOOR; i++)
	{
		if(N1 + N2 < N3 * weight)
		{
			targetFloor = i + 1;
			minPowers += N1 + N2 - N3 * weight;
			N1 += N2;
			N2 = persons[i];
			N3 -= persons[i];
		}
	}
	/*minPowers = INT_MAX;
	for(int i = 2; i <= MAX_FLOOR; i++)
	{
		int sumPowers = 0;
		for(int j = 1; j < MAX_FLOOR; j++)
		{
			if(j + 1 < i)
			sumPowers += persons[j] * (i - j - 1);
			else
			sumPowers += persons[j] * (j + 1 - i) * weight;
		}
		cout<<sumPowers<<endl;
		if(sumPowers < minPowers)
		{
			minPowers = sumPowers;
			targetFloor = i;
		}
	}*/
}

int main()
{
	vector<int> persons{2, 3, 5, 6, 6, 8, 4, 3, 3, 1};
	int targetFloor = 2, minPowers = 0;
	controlElevator(persons, minPowers, targetFloor, 2);
	cout<<"target Floor = "<<targetFloor<<" min Powers = "<<minPowers<<endl;
	
	return 0;
}
