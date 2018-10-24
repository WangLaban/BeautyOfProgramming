#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// Solution1: 
void twoSum(vector<int> nums, int &num1, int &num2, const int target)
{
	for(int i = 0; i < nums.size(); i++)
	{
		num1 = nums[i];
		if(find(nums.begin() + i + 1, nums.end(), target - num1) != nums.end())
		{
			num2 = target - num1;
			return;
		}
	}
}

// Solution2:
void twoSum2(vector<int> nums, int &num1, int &num2, const int target)
{
	for(int i = 0, j = nums.size() - 1; i < j; )
	{
		if(nums[i] + nums[j] == target)
		{
			num1 = nums[i];
			num2 = nums[j];
			return;
		}
		else if(nums[i] + nums[j] > target)
		    j--;
		else
		    i++;
	}
}
int main()
{
	vector<int> nums{5, 6, 1, 4, 5, 7, 8, 8};
	int num1 = 0, num2 = 0;
	//twoSum(nums, num1, num2, 10);
	sort(nums.begin(), nums.end());
	twoSum2(nums, num1, num2, 10);
	cout<<"num1 = "<<num1<<" num2 = "<<num2<<endl;
	
	return 0;
}
