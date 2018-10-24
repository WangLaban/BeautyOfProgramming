#include<iostream>
using namespace std;

void reverse(int arr[], int b, int e)
{
    while(b < e)
    {
        int temp = arr[e];
        arr[e--] = arr[b];
        arr[b++] = temp;
    }
} 

void rightShift(int arr[], int n, int k)
{
    k %= n;
    reverse(arr, 0, n - k - 1);
    reverse(arr, n - k, n - 1);
    reverse(arr, 0, n - 1);
}

int main()
{
	int arr[] = {1, 2, 3, 5, 6, 8, 11};
	rightShift(arr, sizeof(arr) / sizeof(int), 11);
	
	for(int i = 0; i < sizeof(arr) / sizeof(int); i++)
	    cout<<arr[i]<<" ";
	cout<<endl;
	
	return 0;
}
