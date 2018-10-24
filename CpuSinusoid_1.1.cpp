//C++ code to make task manager generate sine graph
// ָ���߳���CPU1�����У�ͨ����Դ���������Կ���CPU1��ռ����Ϊ�������� 
#include<iostream>
using namespace std;

#include "windows.h"
#include "stdlib.h"
#include "math.h"

//��һ����������0~2��֮��Ļ��ȵȷֳ�200�ݽ��г���������ÿ������������ 
//Ȼ��ÿ��300ms��ʱ��ȡ��һ�������㣬����CPU������Ӧ�����ʱ��

const int SAMPLING_COUNT = 200;  //���������� 
const double PI = 3.1415926535;  //piֵ 
const int TOTAL_AMPLITUDE = 300;  // ÿ���������Ӧ��ʱ��Ƭ

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
	::SetProcessAffinityMask(::GetCurrentProcess(),0x00000002);  //ָ���߳���CPU1������ 
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
