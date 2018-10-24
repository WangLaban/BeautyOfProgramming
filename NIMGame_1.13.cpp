#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Solution1:
static bool nim1(int x, int y)
{
	// speical case
	if(x == y)
	    return true;  // I win
	    
	// swap the number
	if(x > y)
	{
		int t = x; x = y; y = t;
	}
	
	// basic cases
	if(x == 1 && y == 2)
	    return false;  // I lose
	    
	vector<bool> a1(101, false);
	a1[1] = true;
	a1[2] = true;
	int a = 1, b;
	
	int n = 1;
	
	while(x > a)
	{
		// finde the next a
		while(a1[a])
		    a++;
		n++;
		b = a + n;
		a1[a] = true;
		a1[b] = true;
		//cout<<"x = "<<x<<" y = "<<y<<" a = "<<a<<" b = "<<b<<endl;
	}
	if(x == a && y == b)
	    return false;  // I lose
	else
	    return true;
}

// Solution2:
static bool nim(int x, int y)
{
	double a, b;
	a = (1 + sqrt(5.0)) / 2;
	b = (3 + sqrt(5.0)) / 2;
	if(x == y)
	    return true;
	if(x > y)
	    swap(x, y);
	if(x == (int)((y - x) * a) && y == (int)((y - x) * b))
	    return false;
	return true;
}
int main()
{
	cout<<"(4, 3) = "<<nim(4, 3)<<endl;
	cout<<"(7, 4) = "<<nim(7, 4)<<endl;
	cout<<"(26, 16) = "<<nim(26, 16)<<endl;
	return 0;
}
