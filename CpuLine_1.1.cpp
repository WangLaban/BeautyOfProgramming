// ��ˣ�һֱ��12% - 13%�䲨�� 
#include <Windows.h>  
#include <stdlib.h>  
int main()  
{  
    int busyTime = 10;  
    int idleTime = busyTime;  
    unsigned __int64 startTime = 0;  
    ::SetThreadAffinityMask(::GetCurrentProcess(),0x00000001); //�����������Ϊʲôû�ã����� 
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
