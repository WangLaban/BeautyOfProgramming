#include <iostream>
using namespace std;

// 1. ����һ�����򣨲���������arr��������һ��iʹ��arr[i]����v,�������򷵻�-1
#if 0
int binarySearch(int A[], int left, int right, int t)
{
    int m;
    while(left <= right){
        m = left + (right - left) / 2;
        if(A[m] < t)
            left = m + 1;
        else if(A[m] > t)
            right = m - 1;
        else 
            return m;
    }
    return -1;
}
int main()
{
    int A[] = {1,2,2,2,3,4,5,6,7};
    cout << binarySearch(A, 0, 8, 2);
    return 0;
}
#endif

// ����һ�����򣨲���������arr������С��iʹ��arr[i]����v���������򷵻�-1
#if 0
int binarySearch(int A[], int left, int right, int t)
{
    int m;
    while(left < right){
        m = left + (right - left) / 2;
        if(A[m] < t)
            left = m + 1;
        else if(A[m] > t)
            right = m - 1;
        else 
            right = m;
    }
    
    if(A[right] == t)
        return right;
    else if(A[left] == t)
        return left;
    else 
        return -1;
}
int main()
{
    int A[] = {3, 3, 3};
    cout << binarySearch(A, 0, sizeof(A) / sizeof(A[0]) - 1, 3);
    return 0;
}
#endif

// 3.����һ�����򣨲���������arr��������iʹ��arr[i]����v���������򷵻�-1
#if 0
int binarySearch(int A[], int left, int right, int t)
{
    int m;
    while(left < right - 1){
        m = left + (right - left) / 2;
        if(A[m] < t)
            left = m + 1;
        else if(A[m] > t)
            right = m - 1;
        else 
            left = m;
    }
    if(A[right] == t)
        return right;
    else if(A[left] == t)
        return left;
    else 
        return -1;
}
int main()
{
    int A[] = {3, 3, 3};
    cout << binarySearch(A, 0, sizeof(A) / sizeof(A[0]) - 1, 3);
    return 0;
}
#endif

// 4.����һ�����򣨲���������arr��������i��ʹ��arr[i]С��v���������򷵻�-1
#if 1
int MaxLessThan(int* arr, int b, int e, int v)
{
	int left = b;
	int right = e;
	int mid;
	while (left <= right && right)
	{
		mid = left + (right - left) / 2;
		if (arr[mid] < v)
			left = mid + 1;
		else
			right = mid - 1;
	}

	if (arr[right] >= v)
		return -1;
	else
		return right;
}
int main()
{
	int arr[] = {3, 3, 3, 4};
	cout<<MaxLessThan(arr, 0, sizeof(arr) / sizeof(int) - 1, 2);
	
	return 0;
}
#endif

// 5.����һ�����򣨲���������arr������С��i��ʹ��arr[i]����v���������򷵻�-1
#if 0
int MinMoreThan(int* arr, int b, int e, int v)
{
	int left = b;
	int right = e;
	int mid;
	while (left < right)
	{
		mid = left + (right - left) / 2;
		if (arr[mid] <= v)
			left = mid + 1;
		else
			right = mid - 1;
	}

	if (arr[left] <= v)
		return -1;
	else
		return left;
}
int main()
{
	int arr[] = {3, 4, 5};
	cout<<MinMoreThan(arr, 0, sizeof(arr) / sizeof(int) - 1, 4);
	
	return 0;
}
#endif
