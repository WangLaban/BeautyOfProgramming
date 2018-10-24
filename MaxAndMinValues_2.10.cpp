#include<iostream>
#include<vector>
using namespace std;

// Solution1:
void theMaxAndTheMin(vector<int> nums, int &maxValue, int &minValue)
{
	if(nums.size() == 1)
	{
	    maxValue = minValue = nums[0];
	    return;
	}
	if(nums[0] < nums[1])
	{
	    maxValue = nums[1];
	    minValue = nums[0];
	}
	else
	{
		maxValue = nums[0];
	    minValue = nums[1];
	}
	for(int i = 2; i < nums.size(); i += 2)
	{
		if(i < nums.size() - 1 && nums[i] > nums[i + 1])
		{

			if(nums[i + 1] < minValue)
				minValue = nums[i + 1];
			if(nums[i] > maxValue)
				maxValue = nums[i];
		}
		else if(i < nums.size() - 1)
		{
			if(nums[i] < minValue)
			    minValue = nums[i];
			if(nums[i + 1] > maxValue)
			    maxValue = nums[i + 1];
		}
		else
		{
			if(nums[i] > maxValue)
			    maxValue = nums[i];
			if(nums[i] < minValue)
			    minValue = nums[i];
		}
	}
}

// Solution2: 分治法
void FindMinMax(vector<int> A, int low, int high, int &minV, int &maxV)
{
    int maxL = 0, maxR = 0, minL = 0, minR = 0;
    if(high - low <= 1)  //如果分组只剩下两个数字或者一个数字，则直接比较
	{
		if(A[low] < A[high])
		{
			minV = A[low];
			maxV = A[high];
			return;
		}
		else
		{
		    minV = A[high];
		    maxV = A[low];
		    return;
		}
			
	}
    FindMinMax(A, low, low + (high - low) / 2, minL, maxL);
    FindMinMax(A, low + (high - low) / 2 + 1, high, minR, maxR);

    if(maxL > maxR)
        maxV = maxL;
    else
        maxV = maxR;

    if(minL < minR)
        minV = minL;
    else
        minV = minR;
} 

int main()
{
	vector<int> nums{5, 6, 8, 3, 10, 4};
	int minValue, maxValue;
	//theMaxAndTheMin(nums, maxValue, minValue);
	FindMinMax(nums, 0, nums.size() - 1, minValue, maxValue);
	cout<<"maxValue = "<<maxValue<<" minValue = "<<minValue<<endl;
	
	return 0;
}
