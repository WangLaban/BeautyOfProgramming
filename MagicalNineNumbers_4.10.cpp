#include <iostream>
using namespace std;

// DFS
void findNum(bool* used,int index,long sum)
{
	if(index !=0 && sum%index != 0)
	{
		return;
	}
	else
	{
		if(index==9)
		{
			cout<<"The number is "<<sum<<" ."<<endl;
			return;
		}
	}
 
	for(int i=1;i<=9;i++)
	{
		if(used[i]==false)
		{
			used[i]=true;
			findNum(used,index+1,sum*10+i);
			used[i]=false;
		}
	}
 
	return;
}
 
int main()
{
	bool used[10]={false};
 
	int index=0;
	long sum=0;
	findNum(used,index,sum);
 
	 system("pause");
	 return 0;
}

