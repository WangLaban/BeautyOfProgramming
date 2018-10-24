#include<iostream>
#include<vector>
using namespace std;

int maxSubarraySum(vector<int> nums)
{
	int sum = 0, maxSum = INT_MIN;
	for(int i = 0; i < nums.size(); i++)
	{
		sum += nums[i];
		maxSum = max(maxSum, sum);
		if(sum < 0)
		{
			sum = 0;
		}
		
	}
	return maxSum;
} 

int maxSubarraySum2(vector<int> nums)
{
    int maxSum = INT_MIN, sum = 0;
    for(int i = 0; i < nums.size(); i++)
    {
        sum = max(sum + nums[i], nums[i]);
        maxSum = max(maxSum, sum);
    }
    return maxSum;
}
int main()
{
	vector<int> nums{-2, -5, -3, -6, -10, -8, -6, -1};
	//vector<int> nums{1, -2, 3, 5, -3, 2};
	//vector<int> nums{0, -2, 3, 5, -1, 2};
	//vector<int> nums{-9, -2, -3, -5, -3};
	int res = maxSubarraySum2(nums);
	cout<<"res = "<<res<<endl;
	
	return 0;
}
