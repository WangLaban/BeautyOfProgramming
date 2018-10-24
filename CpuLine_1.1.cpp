// 多核，一直在12% - 13%间波动 
#include <Windows.h>  
#include <stdlib.h>  
int main()  
{  
    int busyTime = 10;  
    int idleTime = busyTime;  
    unsigned __int64 startTime = 0;  
    ::SetThreadAffinityMask(::GetCurrentProcess(),0x00000001); //该语句在这里为什么没用？？？ 
    while(true)  
    {  
        startTime = GetTickCount();  
        //busy loop  
        while((GetTickCount() - startTime) <= busyTime)
		    ; 
		
        //idle loop  
        Sleep(idleTime);  
    }  
    return 0;  
}
