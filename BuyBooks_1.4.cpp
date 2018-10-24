#include<iostream>
#include<algorithm>
#include<float.h>
using namespace std;

double min5(double a, double b, double c, double d, double e)
{
	return min(min(min(min(a, b), c), d), e);
}
double F(int y1, int y2, int y3, int y4, int y5)
{
	int p[] = {y1, y2, y3, y4, y5};
	sort(p, p + 5, [](int a, int b){return a > b;});
	y1 = p[0];
	y2 = p[1];
	y3 = p[2];
	y4 = p[3];
	y5 = p[4];
	
	double largest = DBL_MAX;
	if(y5 >= 1)
	    return min5(5 * 8 * (1 - 0.25) + F(y1 - 1, y2 - 1, y3 - 1, y4 - 1, y5 - 1),
	    4 * 8 * (1 - 0.2) + F(y1 -1, y2 - 1, y3 - 1, y4 - 1, y5),
	    3 * 8 * (1 - 0.1) + F(y1 -1, y2 - 1, y3 - 1, y4, y5),
	    2 * 8 * (1 - 0.05) + F(y1 -1, y2 - 1, y3, y4, y5),
	    8 + F(y1 - 1, y2, y3, y4, y5)
		);
	else if(y4 >= 1)
	    return min5(largest,
	    4 * 8 * (1 - 0.2) + F(y1 -1, y2 - 1, y3 - 1, y4 - 1, y5),
	    3 * 8 * (1 - 0.1) + F(y1 -1, y2 - 1, y3 - 1, y4, y5),
	    2 * 8 * (1 - 0.05) + F(y1 -1, y2 - 1, y3, y4, y5),
	    8 + F(y1 - 1, y2, y3, y4, y5)
		);
	else if(y3 >= 1)
	    return min5(largest,
	    largest,
	    3 * 8 * (1 - 0.1) + F(y1 -1, y2 - 1, y3 - 1, y4, y5),
	    2 * 8 * (1 - 0.05) + F(y1 -1, y2 - 1, y3, y4, y5),
	    8 + F(y1 - 1, y2, y3, y4, y5)
		);
	else if(y2 >= 1)
	    return min5(largest,
	    largest,
	    largest,
	    2 * 8 * (1 - 0.05) + F(y1 -1, y2 - 1, y3, y4, y5),
	    8 + F(y1 - 1, y2, y3, y4, y5)
		);
	else if(y1 >= 1)
	    return min5(largest,
	    largest,
	    largest,
	    largest,
	    8 + F(y1 - 1, y2, y3, y4, y5)
		);
	else
	    return 0.0;
} 

int main()
{
	cout<<F(1, 1, 2, 2, 2)<<endl;  //51.2
	cout<<F(1, 1, 2, 2, 3)<<endl;  //59.2
	return 0;
}
