#include<iostream>
#include<vector>
using namespace std;

//#define INT_MIN -2147483648

// Solution: 分治法
void FindSecondaryMax(vector<int> A, int low, int high, int &secondMaxV, int &maxV)
{
    int maxL = 0, maxR = 0, secondMaxL = 0, secondMaxR = 0;
    if(high - low == 1)  //如果分组只剩下两个数字，则直接比较
	{
		if(A[low] < A[high])
		{
			secondMaxV = A[low];
			maxV = A[high];
			return;
		}
		else
		{
		    secondMaxV = A[high];
		    maxV = A[low];
		    return;
		}
			
	}
	else if(high - low == 0)  //如果分组只剩下一个数字，赋值给最大值 
	{
		maxV = A[low];
		secondMaxV = INT_MIN;
		return;
	}
    FindSecondaryMax(A, low, low + (high - low) / 2, secondMaxL, maxL);
    FindSecondaryMax(A, low + (high - low) / 2 + 1, high, secondMaxR, maxR);

    if(maxL > maxR)
    {
        maxV = maxL;
        secondMaxV = max(max(secondMaxL, secondMaxR), maxR);
    }
    else
    {
        maxV = maxR;
        secondMaxV = max(max(secondMaxL, secondMaxR), maxL);
    }
} 

int main()
{
	vector<int> nums{5, 6, 8, 3, 10, 9};
	int secondMaxValue, maxValue;
	FindSecondaryMax(nums, 0, nums.size() - 1, secondMaxValue, maxValue);
	cout<<"maxValue = "<<maxValue<<" secondMaxValue = "<<secondMaxValue<<endl;
	
	return 0;
}
