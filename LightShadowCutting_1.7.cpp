// 区间被光影线切割的块数为：1 + 光影线数 + 交点数
// 交点数可以转化为逆序数（假设：不存在三条光影线相交于一点） 
#include<iostream>
#include<vector>
using namespace std;

int reverseOrderNum(vector<int> nums)
{
	int res = 0;
	for(int i = 0; i < nums.size() - 1; i++)
	{
		for(int j = i + 1; j < nums.size(); j++)
		{
			if(nums[i] > nums[j])
			    res++;
		}
	}
	return res;
} 
int main()
{
	vector<int> nums{3, 5, 4, 8, 2, 6, 9};
	int res = reverseOrderNum(nums);
	int partition = res + nums.size() + 1;
	cout<<"res = "<<res<<" partition = "<<partition<<endl;
	
	return 0;
}
