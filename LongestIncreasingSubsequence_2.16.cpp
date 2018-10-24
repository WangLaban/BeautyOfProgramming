#include<iostream>
#include<vector>
using namespace std;

// Solution1:
int LIS(vector<int> nums)
{
	vector<int> lis(nums.size(), 1);  //任意一个数字本身可以构成一个长度为1的子序列 
	for(int i = 0; i < nums.size(); i++)
	{
		for(int j = 0; j < i; j++)
		{
			if(nums[i] > nums[j] && lis[j] + 1 > lis[i])
			    lis[i] = lis[j] + 1;
		}
	}
	int max = lis[0];
	for(int i = 1; i < lis.size(); i++)
	{
		if(lis[i] > max)
		    max = lis[i];
	}
	return max;
}

// Solution2:
int LIS2(vector<int> nums)
{
	//记录数组中的递增序列信息
	vector<int> maxV(nums.size() + 1, 0);
	maxV[0] = INT_MIN;  //边界值
	maxV[1] = nums[0];  //边界值 
	vector<int> lis(nums.size(), 1);
	int nMaxLIS = 1;  //数组最长递增子序列的长度
	
	/*for(int i = 1; i < nums.size(); i++)
	{
		//遍历历史最长递增序列信息
		int j;
		for(j = nMaxLIS; j >= 0; j--)
		{
			if(nums[i] > maxV[j])
			{
				lis[i] = j + 1;
				break;
			}
		} 
		//如果当前最长序列大于最长递增序列长度，更新最长信息
		if(lis[i] > nMaxLIS)
		{
			nMaxLIS = lis[i];
			maxV[lis[i]] = nums[i];
		} 
		else if(maxV[j] < nums[i] && nums[i] < maxV[j + 1])
		{
			maxV[j + 1] = nums[i];
		}
	} */
	for(int i = 1; i < nums.size(); i++)
	{ // 依次引入A[1],...,A[N-1] 
        if(nums[i] > maxV[nMaxLIS])
		{
            nMaxLIS++;
            maxV[nMaxLIS] = nums[i];
        }
        else
	    {
            int j = nMaxLIS - 1;
            while(nums[i] < maxV[j])
                j--;
            maxV[j + 1] = nums[i];      
        }   
    }
	return nMaxLIS;
}
int main()
{
	//vector<int> nums{1, -1, 2, -3, 4, -5, 6, -7};
	vector<int> nums{5, 6, 2, 3};
	int res = LIS2(nums);
	cout<<"res = "<<res<<endl;
	
	return 0;
}
