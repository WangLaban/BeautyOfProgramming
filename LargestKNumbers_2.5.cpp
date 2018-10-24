#include<iostream>
#include<vector>
using namespace std;

// Solution1: quick sort
void quick_sort(vector<int> &nums, int start, int end)
{
	if(nums.size() == 0)
	    return;
	if(start >= end)
	    return;
	int pivot = nums[start];
	int i = start, j = end;
	while(i < j)
	{
		while(nums[j] >= pivot && i < j)
		    j--;
		while(nums[i] <= pivot && i < j)
		    i++;
		if(i < j)
		    swap(nums[i], nums[j]);
	}
	swap(nums[i], nums[start]);
	quick_sort(nums, start, i - 1);
	quick_sort(nums, i + 1, end);
}

vector<int> largestKNumbers(vector<int> nums, int k)
{
	if(k >= nums.size())
	    return nums;
	quick_sort(nums, 0, nums.size() - 1);
	vector<int> res;
	
	for(int i = 0; i < k; i++)
	    res.push_back(nums[nums.size() - k + i]);
	return res;
}

// Solution2: �������� 
/*������a[s]...a[t]�е�Ԫ����һ��Ԫ�ػ�����������a[k]��*/
void partition(vector<int> &nums, int s, int t, int &k)
{
    int i, j, x;
    x = nums[s];  //ȡ����Ԫ��
    i = s;  //ɨ��ָ���ֵ
	j = t;
    do
    {
        while((nums[j] <= x) && i < j) j--;  //��������ɨ��,����ǱȻ���Ԫ��С���򲻶� 
        if(i < j) nums[i++] = nums[j];  //��Ԫ���������
        while((nums[i] >= x) && i < j) i++;  //��������ɨ�裬����ǱȻ���Ԫ�ش��򲻶�
        if(i < j) nums[j--] = nums[i];  //СԪ�����ұ���
  
    }while(i < j);  //ֱ��ָ��i��j���
	nums[i] = x;   //����Ԫ�ؾ�λ
	k = i;
}
/*��������ǰK������Ԫ�أ�index:�������������Ԫ���е�K��Ԫ�ص��±�(��0��ʼ���)��highΪ��������±�*/
int largestKNumbers2(vector<int> &nums, int low, int high, int k)
{ 
    int q;
    int index = -1;
    if(low <= high)
    {
        partition(nums, low, high, q);
        int len = q - low + 1;  //��ʾ�ڼ���λ��
        if(len == k)
            index = q;  //���ص�k��λ��
        else if(len < k)
            index = largestKNumbers2(nums, q + 1, high, k-len); 
        else
            index = largestKNumbers2(nums, low, q - 1, k);
    }
    return index;
}

// Solution3: ���ֲ�������K��������С���Ǹ�
int largerNumbers(vector<int> nums, int x) //��ѯ�����ڻ��ߵ���x��Ԫ�ظ���
{
    int sum = 0;
    
    for(int i = 0; i < nums.size(); i++)
    {
        if(nums[i] >= x)
            sum++;            
    }
    return sum;
}

int theKth(vector<int> nums, int max, int min, int k)  //����max min֮��ֻ�����һ�����߶����ͬ������
{
	int delta = 1;  //delta��ȡֵΪ����nums��������������ȵ�Ԫ�ز�ֵ֮��Сֵ 
    while(max - min > delta)
    {
        int mid = min + (max - min) / 2;
        int num = largerNumbers(nums , mid);  //���ر�mid������ָ���
        if(num >= k)  //����k����Ŀ��Ҫ��minֵ��
            min = mid;            
        else
            max = mid;
    }
    return min;
}

// Solution4: ��С��
//��һ��K��Ԫ�ش�С����С��
void heapAdjust(vector<int>& nums, int i, int len);
void buildMinHeap(vector<int>& nums, int k)
{
    for (int i = (k - 2) / 2; i >= 0; i--)
    {
        heapAdjust (nums, i, k);
    }
}

void heapAdjust(vector<int>& nums, int i, int len)
{
    for(int j = 2 * i + 1; j < len; j = (2 * j + 1))  //��i�������ӽ�㿪ʼ��Ҳ����2i+1����ʼ
    {
        if(j + 1 < len && nums[j] > nums[j + 1])  //������ӽ��������ӽ�㣬jָ�����ӽ��
            j++;
        if(nums[j] < nums[i])
        {
            swap(nums[i], nums[j]);
            i = j;
        }
    }
}
void largestKNumbers4(vector<int> &nums, int k)
{
	if(k >= nums.size())
	    return;
	buildMinHeap(nums, k);
	for(int i = k; i < nums.size(); i++)
	{
		if(nums[i] > nums[0])
		{
			swap(nums[0], nums[i]);
			heapAdjust(nums, 0, k);
		}
	}
}
// Solution5: �������� 
int theMax(vector<int> nums)
{
	if(nums.size() == 0)
	    return -1;
	int maxN = nums[0];
	for(int i = 1; i < nums.size(); i++)
	{
		if(nums[i] > maxN)
		    maxN = nums[i];
	}
	return maxN;
}

int theKth(vector<int> nums, vector<int> &count, int k)
{
	for(int i = 0; i < nums.size(); i++)
	{
		count[nums[i]]++;
	}
	int v, sumCount;
	for(sumCount = 0, v = count.size() - 1; v >= 0; v--)
	{
		sumCount += count[v];
		if(sumCount >= k)
		    break;
	}
	return v;
}
int main()
{
    vector<int> nums{3, 44, 38, 5, 47, 15, 36, 26, 27, 2, 46, 4, 19, 50, 48};
    /*vector<int> res = largestKNumbers(nums, 10);
    for(auto i : res)
        cout<<i<<" ";
    cout<<endl;*/
    /*int index = largestKNumbers2(nums, 0, nums.size() - 1, 10);

    for(int i = 0; i <= index; i++)
        cout<<nums[i]<<" ";
    cout<<endl;*/
    /*int key = theKth(nums, 50, 2, 10);
    for(auto i : nums)
        if(i >= key)
            cout<<i<<" ";
    cout<<endl;*/
    /*largestKNumbers4(nums, 10);
    for(int i = 0; i < 10; i++)
        cout<<nums[i]<<" ";
    cout<<endl;*/
    int maxN = theMax(nums);
    vector<int> count(maxN + 1, 0);
    int index = theKth(nums, count, 10);
    
    for(int i = maxN; i >= index; i--)
    {
    	if(count[i])
    	{
    		cout<<i<<" ";
    	}
    }
    cout<<endl;
    
    return 0;
}
