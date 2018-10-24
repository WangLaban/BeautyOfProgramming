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

// Solution2: 部分排序 
/*将数组a[s]...a[t]中的元素用一个元素划开，保存中a[k]中*/
void partition(vector<int> &nums, int s, int t, int &k)
{
    int i, j, x;
    x = nums[s];  //取划分元素
    i = s;  //扫描指针初值
	j = t;
    do
    {
        while((nums[j] <= x) && i < j) j--;  //从右向左扫描,如果是比划分元素小，则不动 
        if(i < j) nums[i++] = nums[j];  //大元素向左边移
        while((nums[i] >= x) && i < j) i++;  //从左向右扫描，如果是比划分元素大，则不动
        if(i < j) nums[j--] = nums[i];  //小元素向右边移
  
    }while(i < j);  //直到指针i与j相等
	nums[i] = x;   //划分元素就位
	k = i;
}
/*查找数组前K个最大的元素，index:返回数组中最大元素中第K个元素的下标(从0开始编号)，high为数组最大下标*/
int largestKNumbers2(vector<int> &nums, int low, int high, int k)
{ 
    int q;
    int index = -1;
    if(low <= high)
    {
        partition(nums, low, high, q);
        int len = q - low + 1;  //表示第几个位置
        if(len == k)
            index = q;  //返回第k个位置
        else if(len < k)
            index = largestKNumbers2(nums, q + 1, high, k-len); 
        else
            index = largestKNumbers2(nums, low, q - 1, k);
    }
    return index;
}

// Solution3: 二分查找最大的K个数中最小的那个
int largerNumbers(vector<int> nums, int x) //查询出大于或者等于x的元素个数
{
    int sum = 0;
    
    for(int i = 0; i < nums.size(); i++)
    {
        if(nums[i] >= x)
            sum++;            
    }
    return sum;
}

int theKth(vector<int> nums, int max, int min, int k)  //最终max min之间只会存在一个或者多个相同的数字
{
	int delta = 1;  //delta的取值为所有nums中任意两个不相等的元素差值之最小值 
    while(max - min > delta)
    {
        int mid = min + (max - min) / 2;
        int num = largerNumbers(nums , mid);  //返回比mid大的数字个数
        if(num >= k)  //最大的k个数目都要比min值大
            min = mid;            
        else
            max = mid;
    }
    return min;
}

// Solution4: 最小堆
//建一个K个元素大小的最小堆
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
    for(int j = 2 * i + 1; j < len; j = (2 * j + 1))  //从i结点的左子结点开始，也就是2i+1处开始
    {
        if(j + 1 < len && nums[j] > nums[j + 1])  //如果左子结点大于右子结点，j指向右子结点
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
// Solution5: 计数排序 
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
