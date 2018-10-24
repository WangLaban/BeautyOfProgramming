#include<iostream>
using namespace std;

// Solution1:
long long maxProduct(const int *d, unsigned int n)
{
  long long ret;
  long long max;
  int i, j;
  for(i=0; i<n; i++)
  {
    for(j=0, ret=1; j<n; j++)
    {
      ret *= ((i==j) ? 1 : d[j]);
      if(ret == 0) break;
    }
    max = (i==0 ? ret : max);
    max = (max<=ret ? ret : max);
  }
 
  return max;
}

// Solution2:
int maxProduct2(int arr[], int len)
{
    int *p=NULL, *s=NULL, *t=NULL;
    int i = 0, max = 0;
 
    if (len == 0)
        return 0;
 
    //s[i]表示数组前i个元素的乘积
	//t[i]表示数组后len - i - 1个元素的乘积 
    p = new int[len]; s = new int[len]; t = new int[len];
    s[0] = 1;
    for (i = 1; i < len; i++)
    {
        s[i] = s[i-1]*arr[i-1];
    }
 
    t[len-1] = 1;
    for (i = len-2; i >= 0; i--)
    {
        t[i] = t[i+1]*arr[i+1];
    }

    for (i = 0; i < len-1; i++)
    {
        p[i] = s[i]*t[i];
        if (p[i] > max)
        {
            max = p[i];
        }
    }
 
    delete[] p; delete[] s; delete[] t;
    p = NULL; s = NULL; t = NULL;
 
    return max;
}

// Solution3:
//1.数组中有多于一个零则最大乘积为0；
//2.数组中只有一个零，而有奇数个负数，则最大乘积必定为0；
//3.数组中只有一个零，而有偶数个负数，则最大乘积为除去0的元素的乘积；  
//4.数组中没有零，而有奇数个负数，则最大乘积为除去绝对值最小的负数的乘积；  
//5.数组中没有零，而有偶数个负数，则最大乘积为除去最小的正数的乘积。
int maxProduct3(int arr[], int len)
{
    int i = 0, max = 1;
    int zeroCnt = 0, negCnt = 0;
    int maxNegIdx = -1, minPosIdx = -1;
 
    if (len == 0)
        return 0;
 
    for (i = 0; i < len; i++)
    {
        if (0 == arr[i])
        {
            zeroCnt++;
        }
        else if(arr[i] > 0)
        {
            if (arr[i] < arr[minPosIdx] || minPosIdx == -1)
                minPosIdx = i;
        }
        else
        {
            negCnt++;
            if (arr[i] > arr[maxNegIdx] || maxNegIdx == -1)
                maxNegIdx = i;
        }
    }

    if (zeroCnt > 1)
    {
        max = 0;
    }
    else if (zeroCnt == 1)
    {
        if (negCnt%2 == 1)
            max = 0;
        else
            for (i = 0; i < len; i++)
                if (arr[i] != 0)
                    max *= arr[i];
    }
    else
    {
        if (negCnt%2 == 1)
        {  //加上大括号，防止下面的else语句和离它最近的if语句配对了 
            for (i = 0; i < len; i++)
                if (i != maxNegIdx)
                    max *= arr[i];
        }
        else
        {
            for (i = 0; i < len; i++)
                if (i != minPosIdx)
                    max *= arr[i];
        }
    }
 
    return max;
}

int main()
{
	int data[] = {1, -3, 2, -5, 7, 5, 12};
	long long res = maxProduct3(data, sizeof(data) / sizeof(int));
	cout<<"res = "<<res<<endl;
	
	return 0;
}
