#include<iostream>
#include<vector>
using namespace std;

vector<int> find(vector<int> nums, int n)
{
	vector<int> candidate(3, 0);
	int nTimes[3] = {0};
	for(int i = 0; i < n; i++)
	{
		if(nTimes[0] == 0)
		{
			candidate[0] = nums[i];
			nTimes[0] = 1;
		}
		else if(nTimes[1] == 0 && nums[i] != candidate[0])
		{
			candidate[1] = nums[i];
			nTimes[1] = 1;
		}
		else if(nTimes[2] == 0 && nums[i] != candidate[0] && nums[i] != candidate[1])
		{
			candidate[2] = nums[i];
			nTimes[2] = 1;
		}
		else
		{
			if(candidate[0] == nums[i])
			    nTimes[0]++;
			else if(candidate[1] == nums[i])
			    nTimes[1]++;
			else if(candidate[2] == nums[i])
			    nTimes[2]++;
			else
			{
			    nTimes[0]--;
			    nTimes[1]--;
			    nTimes[2]--;
			}
		}
	}
	return candidate;
}

int main()
{
	vector<int> nums{1, 3, 4, 5, 4, 3, 5, 7, 3, 5, 3, 4, 3, 4, 5, 5, 4, 6};
	vector<int> res = find(nums, nums.size());
	cout<<"res[0] = "<<res[0]<<" res[1] = "<<res[1]<<" res[2] = "<<res[2]<<endl;
	
	return 0;
}
