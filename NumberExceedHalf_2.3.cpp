#include<iostream>
#include<vector>
using namespace std;

int find(vector<int> nums, int n)
{
	int candidate = nums[0];
	int nTimes = 0;
	for(int i = 0; i < n; i++)
	{
		if(nTimes == 0)  //���ǰ�涼���ԣ�����Ϊ��������
		{
			candidate = nums[i];
			nTimes = 1;
		}
		else
		{
			if(candidate == nums[i])  //������
			    nTimes++;
			else  //��������
			    nTimes--;
		}
	}
	return candidate;
}

int main()
{
	vector<int> nums{1, 3, 7, 5, 4, 3, 7, 3, 6, 3, 4, 3, 3, 3};
	int res = find(nums, nums.size());
	cout<<"res = "<<res<<endl;
	
	return 0;
}
