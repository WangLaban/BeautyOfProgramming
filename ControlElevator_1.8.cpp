#include<iostream>
#include<vector>
using namespace std;

#define MAX_FLOOR 10

// Solution1:
void controlElevator1(vector<int> persons, int &minFloors, int &targetFloor)
{
	for(int i = 2; i <= MAX_FLOOR; i++)
	{
		int sumFloor = 0;
		for(int j = 1; j < MAX_FLOOR; j++)
		{
			sumFloor += persons[j] * abs(j + 1 - i);
		}
		if(sumFloor < minFloors)
		{
			minFloors = sumFloor;
			targetFloor = i;
		}
	}
}

// Solution2: 
void controlElevator2(vector<int> persons, int &minFloors, int &targetFloor)
{
	int N1 = 0, N2 = persons[1], N3 = 0;
	minFloors = 0;
	for(int i = 2; i < MAX_FLOOR; i++)
	{
		N3 += persons[i];
		minFloors += persons[i] * (i - 1);
	}
	for(int i = 2; i < MAX_FLOOR; i++)
	{
		if(N1 + N2 < N3)
		{
			targetFloor = i + 1;
			minFloors += (N1 + N2 - N3);
			N1 += N2;
			N2 = persons[i];
			N3 -= persons[i];
		}
	}
}

// Solution3: ÖÐÎ»Êý
// todo... 
int main()
{
	vector<int> persons{2, 3, 5, 6, 6, 8, 4, 3, 3, 1};
	int targetFloor = 2, minFloors = INT_MAX;
	controlElevator2(persons, minFloors, targetFloor);
	cout<<"target Floor = "<<targetFloor<<" min Floors = "<<minFloors<<endl;
	
	return 0;
}
