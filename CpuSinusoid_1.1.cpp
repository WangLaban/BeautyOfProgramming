//C++ code to make task manager generate sine graph
// 指定线程在CPU1上运行，通过资源管理器可以看到CPU1的占用率为正弦曲线 
#include<iostream>
using namespace std;

#include "windows.h"
#include "stdlib.h"
#include "math.h"

//把一条正弦曲线0~2π之间的弧度等分成200份进行抽样，计算每个抽样点的振幅 
//然后每隔300ms的时间取下一个抽样点，并让CPU工作对应振幅的时间

const int SAMPLING_COUNT = 200;  //抽样点数量 
const double PI = 3.1415926535;  //pi值 
const int TOTAL_AMPLITUDE = 300;  // 每个抽样点对应的时间片

int main()
{
	DWORD busySpan[SAMPLING_COUNT];
	int amplitude = TOTAL_AMPLITUDE / 2;
	double radian = 0.0;
	double radianIncrement = 2.0 / (double)SAMPLING_COUNT;
	for(int i = 0; i < SAMPLING_COUNT; i++)
	{
		busySpan[i] = (DWORD)(amplitude + (sin(PI * radian) * amplitude));
		radian += radianIncrement;
		cout<<"i: "<<i<<" busySpan: "<<busySpan[i]<<" "<<(TOTAL_AMPLITUDE - busySpan[i])<<endl;
	} 
	::SetProcessAffinityMask(::GetCurrentProcess(),0x00000002);  //指定线程在CPU1上运行 
	DWORD startTime = 0;
	for(int j = 0; ; j = (j + 1) % SAMPLING_COUNT)
	{
		startTime = GetTickCount();
		while ((GetTickCount() - startTime) <= busySpan[j])
		    ;
		Sleep(TOTAL_AMPLITUDE - busySpan[j]);
	}
	
	return 0;
} 
