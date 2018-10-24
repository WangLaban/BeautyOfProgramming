#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#define pointNumMax 6
using namespace std;
const double INF = 1e20;
 
struct Point
{
	double x;
	double y;
};
 
bool cmpxy(const Point &a, const Point &b){
	if (a.x != b.x)
		return a.x < b.x;
	return a.y < b.y;
}
 
bool cmpy(const Point &a, const Point &b){
	return a.y < b.y;
}
 
double min(double a, double b)
{
	return a < b ? a : b;
}
 
double dis(const Point &a, const Point &b){
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}
 
double minDisPair(Point* p, int left, int right)
{
	double d = INF;
	if (left == right)
		return d;
	if (left + 1 == right)
		return dis(p[left], p[right]);
	int mid = (left + right) >> 1;
	double d1 = minDisPair(p, left, mid);
	double d2 = minDisPair(p, mid+1, right);
	double minDis = min(d1, d2);
	int i, j;
	vector<Point> tmp;
	for (i = left; i <= right; i++)
	{
		if (fabs(p[i].x - p[mid].x) < minDis)
			tmp.push_back(p[i]);
	}
	sort(tmp.begin(), tmp.end(), cmpy);
	int len = tmp.size();
	for (i = 0; i < len-1; i++)
	{	
		for (j = i + 1; (j < len)&&(j <= pointNumMax + i)  && ((tmp[j].y - tmp[i].y) < minDis); j++)
		{
			double tmpDis = dis(tmp[j], tmp[i]);
			if (tmpDis < minDis)
				minDis = tmpDis;
		}
	}
	return minDis;
}
 
int main()
{
	int n = 5;
	Point* point = new Point[n];
	for (int i = 0; i < n; i++)
		scanf("%lf %lf", &point[i].x, &point[i].y);
	sort(point, point + n, cmpxy);
	printf("%.2lf\n", minDisPair(point, 0, n - 1));		
	return 0;
}
