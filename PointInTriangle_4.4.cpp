#include<iostream>
#include<cmath>
using namespace std;

#if 0
// Solution1:
// 点D与三边围成的面积之和是否等于三角形ABC的面积
const double eps=1e-8;

struct point{
	point(double i,double j):x(i),y(j){}
	double x,y;
};
void computeEdgeLen(point A,point B,
	point C,double& a,double &b,double &c){
		a=sqrt(pow(B.x-A.x,2)+pow(B.y-A.y,2));
		b=sqrt(pow(C.x-B.x,2)+pow(C.y-B.y,2));
		c=sqrt(pow(A.x-C.x,2)+pow(A.y-C.y,2));
}
 
double Area(point A,point B,point C)
{
	double a,b,c=0;
	computeEdgeLen(A,B,C,a,b,c);
	double p=(a+b+c)/2;

	return sqrt(p*(p-a)*(p-b)*(p-c));  //海伦公式
 
}
//AB与AC的斜率相同 
bool isTriangle(point A,point B,point C){
	if((B.y-A.y)*(B.x-A.x)-(C.y-A.y)*(C.x-A.x) < eps)
		return false;
	else
		return true;
 
}
bool isInTriangle(point A,point B,point C,point D)
{
	if(!isTriangle(A,B,C))
		return false;
	return (Area(A,B,D)+Area(B,C,D)+Area(C,A,D)-Area(A,B,C)<eps);
 
}
int main(){
	point A(0,2);
	point B(0,0);
	point C(1,0);
	point D(0.9,0);
	if(isInTriangle(A,B,C,D))
		cout<<"true"<<endl;
	else
		cout<<"false"<<endl;
	system("pause");
	return 0;
 
 
}
#endif

// Solution2:
// 如果有一个点D在三角形ABC内，那么沿着三角形的边界逆时针走，点D一定保持在边界的左边，也就是说点D在边AB、BC、CA的左边。
struct point{
    double x;
    double y;
};

// 向量积 
// 向量AB(B.x - A.x, B.y - A.y)
// 向量AD(D.x - A.x, D.y - A.y)
// 向量a(x1, y1)与b(x2, y2)平行，则x1 * y2 == y1 * x2 
double vectorProduct(point &a,point &b,point& d){
    return (b.x-a.x)*(d.y-a.y)-(b.y-a.y)*(d.x-a.x);
}
 
bool isInTriangle(point &a,point &b,point &c,point d){
    if(vectorProduct(a,b,d)>=0 && vectorProduct(b,c,d)>=0 && vectorProduct(c,a,d)>=0){
        return true;
    }
    return false;
}
 
int main(){
 
    point a={0.5,1};
    point b={0,0};
    point c={1,0};
 
    point d1={0.5,1};
 
    cout<<isInTriangle(a,b,c,d1)<<endl;
 
    point d2={2,2};
 
    cout<<isInTriangle(a,b,c,d2)<<endl;
 
    return 0;
}
