#if 0
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

// seperate the source
bool fun_1(int arr_target[][2], int target_len, int* arr_src)
{
    bool find = false;
    int i = 0, j = 0, min=0, max = 0;
    int* pNew = NULL;
    vector<int*> vec_stack;
    bool *checked;
 
    checked = new bool[target_len];
    memset(checked, 0, target_len);
 
    vec_stack.push_back(arr_src);
    i = 0;
    while ((size_t)i < vec_stack.size())
    {
        min = vec_stack[i][0];
        max = vec_stack[i][1];
        for (j = 0; j < target_len; j++)
        {
            if ((!checked[j]) && 
                ((arr_target[j][0] <= min) && (arr_target[j][1] >= max)))
            {
                cout << "src " << i+1 << ":" << vec_stack.size() << " ("<< min<< ", " << max << ")" << " vs ("<< arr_target[j][0]<< ", " << arr_target[j][1] << ")  Covered"<< endl;
 
                checked[j] = 1;
                if ((size_t)i == vec_stack.size()-1)
                {
                    cout << "Success Covered !" << endl;
                    find = true;
                }
                break;
            }
            else if ((!checked[j]) 
                         && ((arr_target[j][0] >= max) || (arr_target[j][1] <= min)))
            {
                cout << "src " << i+1 << ":" << vec_stack.size() << " ("<< min<< ", " << max << ")" << " vs ("<< arr_target[j][0]<< ", " << arr_target[j][1] << ")  NOT Covered"<< endl;
                continue;
            }
            else if ((!checked[j]) 
                       && ((arr_target[j][0] <= min) 
                       && (arr_target[j][1] >= min)
                       && (arr_target[j][1] <= max)))
            {
                cout << "src " << i+1 << ":" << vec_stack.size() << " ("<< min<< ", " << max << ")" << " vs ("<< arr_target[j][0]<< ", " << arr_target[j][1] << ")"<< endl;
                pNew = new int[2];
                pNew[0] = arr_target[j][1];
                pNew[1] = max;
                vec_stack.push_back(pNew);
                checked[j] = 1;
                cout << "src seperate " << "(" << min<< ", " << max << ")" << " ==>  ("<< pNew[0]<< ", " << pNew[1] << ")"<< endl;
                break;
            }
            else if ((!checked[j])
                       && ((arr_target[j][0] >= min) 
                       && (arr_target[j][0] <= max) 
                       && (arr_target[j][1] >= max)))
            {
                cout << "src " << i+1 << ":" << vec_stack.size() << " ("<< min<< ", " << max << ")" << " vs ("<< arr_target[j][0]<< ", " << arr_target[j][1] << ")"<< endl;
                pNew = new int[2];
                pNew[0] = arr_target[j][0];
                pNew[1] = min;
                vec_stack.push_back(pNew);
                checked[j] = 1;
                cout << "src seperate " << "(" << min<< ", " << max << ")" 
                         << " ==>  ("<< pNew[0]<< ", " << pNew[1] << ")"<< endl;
                break;
            }
            else if ((!checked[j]) 
                        && ((arr_target[j][0] >= min) && (arr_target[j][1] <= max)))
            {
                cout << "src " << i+1 << ":" << vec_stack.size() << " ("<< min<< ", " << max << ")" << " vs ("<< arr_target[j][0]<< ", " << arr_target[j][1] << ")"<< endl;
                pNew = new int[2];
                pNew[0] = min;
                pNew[1] = arr_target[j][0];
                vec_stack.push_back(pNew);
                cout << "src seperate " << "(" << min<< ", " << max << ")" << " ==>  ("<< pNew[0]<< ", " << pNew[1] << ")  " ;
 
                pNew = new int[2];
                pNew[0] = arr_target[j][1];
                pNew[1] = max;
                vec_stack.push_back(pNew);
                checked[j] = 1;
                cout << "("<< pNew[0]<< ", " << pNew[1] << ")  " <<endl;
                break;
            }
        }
        i++;
    }
 
    for (vector<int*>::iterator it = vec_stack.begin(); it != vec_stack.end(); it++)
    {
        delete[] (*it);
        (*it) = NULL;
    }
    vec_stack.clear();
    delete[] checked;
 
    if (!find)
        cout << "NOT Covered !" << endl;
 
    return find;
}
 
// merge the target
void quick_sort(int arr_target[][2], int left, int right)
{
    int i = left, j = right;
    int a0 = 0, a1 = 0;
 
    if (left > right)
        return;
 
    int x0 = arr_target[left][0];
    int x1 = arr_target[left][1];
 
    while (i != j)
    {
        while (arr_target[j][0] >= x0 && i < j)
            j--;
        while (arr_target[i][0] <= x0 && i < j)
            i++;
 
        if (i < j)
        {
            a0 = arr_target[i][0]; a1= arr_target[i][1];
            arr_target[i][0] = arr_target[j][0];   arr_target[i][1] = arr_target[j][1];
            arr_target[j][0] = a0;   arr_target[j][1] = a1;
        }
    }
    arr_target[left][0] = arr_target[i][0];
    arr_target[left][1] = arr_target[i][1];
 
    arr_target[i][0] = x0;
    arr_target[i][1] = x1;
 
    quick_sort(arr_target, left, i - 1);
    quick_sort(arr_target, i + 1, right);
}
 
int merge(int arr_target[][2], int target_len, vector<int*> &vec_stack)
{
    int i = 0, j = 0;
    int* pNew = NULL;
    bool isSet = false;
 
    pNew = new int[2];
    pNew[0] = arr_target[0][0];;
    pNew[1] = arr_target[0][1];
    vec_stack.push_back(pNew);
 
    j = 0;
    for (i = 1; i < target_len; i++)
    {
        if ((arr_target[i][0] <= vec_stack[j][0])
            && (arr_target[i][1] >= vec_stack[j][1]))
        {
            vec_stack[j][0] = arr_target[i][0];
            vec_stack[j][1] = arr_target[i][1];
        }
        else if ((arr_target[i][0] > vec_stack[j][1]) 
                     || (arr_target[i][1] < vec_stack[j][0]))
        {
            pNew = new int[2];
            pNew[0] = arr_target[i][0];;
            pNew[1] = arr_target[i][1];
            vec_stack.push_back(pNew);
            j++;
        }
        else if ((arr_target[i][0] <= vec_stack[j][0])  
                    && (arr_target[i][1] >= vec_stack[j][0])
                    && (arr_target[i][1] <= vec_stack[j][1]))
        {
            vec_stack[j][0] = arr_target[i][0];
        }
        else if ((arr_target[i][0] >= vec_stack[j][0]) 
                    && (arr_target[i][0] <= vec_stack[j][1]) 
                    && (arr_target[i][1] >= vec_stack[j][1]))
        {
            vec_stack[j][1] = arr_target[i][1];
        }
        else if ((arr_target[i][0] >= vec_stack[j][0]) 
                     && (arr_target[i][1] <= vec_stack[j][1]))
        {
        }
    }
    return vec_stack.size();
}
 
bool fun_2(int arr_target[][2], int target_len, int* arr_src)
{
    int i = 0;
    bool find = false;
    vector<int*> vec_stack;
 
    quick_sort(arr_target, 0, target_len-1);
    merge(arr_target, target_len, vec_stack);
 
    for (i = 0 ; (size_t)i < vec_stack.size(); i++)
    {
        cout << "vstack: (" << vec_stack[i][0] << ", " << vec_stack[i][1] << ")" ;
        if ((arr_src[0] >= vec_stack[i][0]) && (arr_src[1] <= vec_stack[i][1]))
        {
            cout << " ==> Covered (" << arr_src[0] << ", " << arr_src[1] <<")" << endl;
            find = true;
        }
        cout << endl;
    }
 
    if (!find)
        cout << "NOT Covered !" << endl;
 
    for (vector<int*>::iterator it = vec_stack.begin(); it != vec_stack.end(); it++)
    {
        delete[] (*it);
        (*it) = NULL;
    }
    vec_stack.clear();
 
    return find;
}
 
int main()
{
    int arr_target[][2] = {{2,3}, {3,9}, {1,2}, };
    int arr_source[] = {1,6};
 
    //int arr_target[][2] = {{2,3}, {5,7}, {1,2}, {2, 5}, {10, 15}};
    //int arr_source[] = {1,8};
 
    //int arr_target[][2] = {{1,8},};
    //int arr_source[] = {1,8};
 
    int len = sizeof(arr_target)/(sizeof(int)*2);
 
    int* psrc = new int[2];
    psrc[0] = arr_source[0];
    psrc[1] = arr_source[1];
 
    fun_1(arr_target, len, psrc);
    //fun_2(arr_target, len, psrc);

    
    return 0;
}
#endif

#if 0
#include <iostream>
#include <algorithm>
using namespace std;

struct Line{
	int low,high;
	Line(int l=0,int h=0):low(l),high(h){}
	bool operator<(Line & other)
	{
		return low<other.low;
	}
};

const int MAX = 100;
Line lines[MAX];

//注意咱们搜索的数为刚好小于key的那个值
int BinarySearchLower(Line arr[],int len,int target)
{
	int low = 0;
	int high = len-1;
 
	while(low < high){
		int mid = (low + high)/2;
		if(arr[mid].low>=target)high = mid-1;
		else low = mid + 1;
			
	}
	return high;
}

int main()
{
	int n, k, i, j;  
    
	cin>>n;  // n是目标区间的个数,k是待查询的源区间的个数  
	for (i=0; i<n; i++)  
		cin >> lines[i].low >> lines[i].high;  
 
	sort(lines, lines+n);  
 
	int cnt = 0; //合并以后的区间数
	int lasthigh = lines[0].high;  
 
        //合并区间
	for(i=1; i<n; i++){
		if(lasthigh>=lines[i].low && lasthigh<lines[i].high)
			lasthigh = lines[i].high;
		else{
			lines[cnt].high = lasthigh;
			lines[++cnt].low = lines[i].low;
			lasthigh = lines[i].high;
		}
 
	}
	lines[cnt++].high = lasthigh;
 
	Line search = Line(1,6);
 
	int sLow = BinarySearchLower(lines,cnt,search.low);
	int sHigh = BinarySearchLower(lines,cnt,search.high);
	if(sLow==sHigh && search.high<=lines[sLow].high)//注意要判断
		cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
 
	return 0;
}
#endif

#include <iostream>
#include <algorithm>
using namespace std;

struct Pair{
  int b;
  int e;
};

int rangeCmp(const void* a, const void* b){
  return ((Pair*)a)->b-((Pair*)b)->b;
}

bool isCover(Pair& target, Pair ranges[], int n){
  qsort(ranges, n, sizeof(Pair), rangeCmp);
  int b = target.b, e = target.e;
  for(int i = 0; i < n; ++i){   
    if(b>=ranges[i].b && b <= ranges[i].e)
      b = ranges[i].e;
  }
  return b>=e;
}

int main(){
  Pair ranges1[] = {{3,4},{1,2},{3,9}};
  Pair target = {1,6};
  cout<<isCover(target,ranges1,3)<<endl;
  Pair ranges2[] = {{3,5},{1,3},{3,9}};
  cout<<isCover(target,ranges2,3)<<endl;
  system("PAUSE");
  return 0;
}
