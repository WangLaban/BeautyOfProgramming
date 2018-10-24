#include <iostream>
using namespace std;

const double eps = 1e-8;
void CalcTime(double PoleLen,double *xPos,int AntNum,double speed,double &tMin,double &tMax)
{
	if(PoleLen <= eps || AntNum <= eps || speed <= eps || xPos == NULL)
	    return;

    tMax=tMin=0;
    for(int i=0;i<AntNum;++i)
    {
        double curMax=0;
        double curMin=0;
        if (xPos[i]>(PoleLen/2))
        {
            curMax=xPos[i] / speed;
        }
        else
        {
            curMax=(PoleLen-xPos[i]) / speed;
        }
        curMin = PoleLen / speed - curMax;
        if (tMax < curMax)
        {
            tMax = curMax;
        }
        if (tMin < curMin)  //注意这里是小于因为是所有蚂蚁最短时间，取最短中最大的
        {
            tMin = curMin;
        }
    }
}

int main()
{
    double poleLength=27;
    double ants[5]={3,7,11,17,23};
    double speed=2;
    double timeMax,timeMin;

    CalcTime(poleLength,ants,5,speed,timeMin,timeMax);
    cout<<"MaxTime: "<<timeMax<<endl;
    cout<<"MinTime: "<<timeMin<<endl;
    
    return 0;
}
