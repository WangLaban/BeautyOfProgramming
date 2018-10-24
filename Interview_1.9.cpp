#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

#if 0 
struct meet_time{
	int start;
	int end;
};

//[) 左闭右开
bool is_overlap(meet_time m1, meet_time m2)//指排序后的
{
	if(m1.end <= m2.start)return false;
	return true;
}

// Solution1:
#if 0
int min_meeting(vector<meet_time> m, int n)
{
	vector<bool> used(n, false);
	int min_color = 0;
 
	//先排序
	sort(m.begin(), m.end(), [](meet_time m1, meet_time m2){
		return m1.start < m2.start;
	});
	
	for(int i = 0; i < n; i++)
	{
		if (!used[i])
		{
			min_color++;
		}
		meet_time temp = m[i];
		
		for (int j = i + 1; j < n; j++)
		{
			if (!is_overlap(temp, m[j]))
			{
				if(!used[j])
				{
					//有非重叠的
					temp = m[j];  //作为下一次的对象！
					used[j] = true;	
				}
			}
		}
	}
	return min_color;
}
#endif

// Solution2: 
int min_meeting(vector<meet_time> m, int n)
{
	int nMaxColor = 0, k = 0;
	vector<int> color(n, 0);
	vector<bool> isForbidden(n, false);
	for(int i = 0; i < n; i++)
	{
		for(k = 0; k < nMaxColor; k++)
		    isForbidden[k] = false;
		// 对当前区间j着色时，必须保证所着的颜色（color[j]）没有被出现在这个区域之前且时间段与当前区间有重叠的区间用到 
		for(int j = 0; j < i; j++)
		{
			if(is_overlap(m[j], m[i]))
			    isForbidden[color[j]] = true;
		}
		for(k = 0; k < nMaxColor; k++)
		    if(!isForbidden[k])
		        break;
		        
		if(k < nMaxColor)
		    color[i] = k;
		else
		    color[i] = nMaxColor++;
	}
	return nMaxColor;
}
int main()
{
	vector<meet_time> m{{0, 6}, {1, 4}, {2, 13}, {3, 5}, {3, 8}, {2, 11}, {5, 7}, {5, 9}, {6, 10}, {8, 11}, {8, 12}, {12, 14}};
	int len = m.size();
	for(int i = 0; i < len; i++)
	{
		cout<<m[i].start<<" "<<m[i].end<<" | ";
	}
	cout<<endl;
	
	int count = min_meeting(m, len);
	cout<<count<<endl;
	return 0;
}
#endif

// Solution3:
#define BEGIN 0
#define END 1
struct meet_time{
	int value;
	int type;
};

int min_meeting(vector<meet_time> TimePoints, int len)
{
	int nMaxColor = 0, nColorUsing = 0;
	for(int i = 0; i < len; i++)
	{
		if(TimePoints[i].type == BEGIN)
		{
			nColorUsing++;
			if(nColorUsing > nMaxColor)
			    nMaxColor = nColorUsing;
		}
		else
		    nColorUsing--;
	}
	return nMaxColor;
}

int main()
{
	vector<int> nums{0, 6, 1, 4, 2, 13, 3, 5, 3, 8, 2, 11, 5, 7, 5, 9, 6, 10, 8, 11, 8, 12, 12, 14};
	vector<meet_time> TimePoints;
	meet_time mt;
	for(int i = 0; i < nums.size(); i++)
	{
		mt.value = nums[i];
		if(i % 2 == 0)
		{
			mt.type = BEGIN;
		}
		else
		{
			mt.type = END;
		}
		TimePoints.push_back(mt);
	}
	sort(TimePoints.begin(), TimePoints.end(), [](meet_time m1, meet_time m2){
		if(m1.value == m2.value)
		    return m1.type == BEGIN ? false : true;  // 注意：当一个区间的开始时间等于另一个区间的结束时间，应该将结束时间排在前面 
		return m1.value < m2.value;
	});
	
	int count = min_meeting(TimePoints, sizeof(TimePoints));
	cout<<count<<endl;
	
	return 0;
}
