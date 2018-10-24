// 要求：代码中只能使用一个字节存储变量 
// Solution1: 
#if 0
#include <stdio.h>
#define HALF_BITS_LENGTH 4  //这个值是记忆存储单元长度的一半，在这道题里是4bit 
#define FULLMASK 255  //这个数字表示一个全部bit的mask，在二进制表示中，它是11111111 
#define LMASK (FULLMASK << HALF_BITS_LENGTH)  //这个宏表示左bits的mask，在二进制表示中，它是11110000 
#define RMASK (FULLMASK >> HALF_BITS_LENGTH)  //这个宏表示右bits的mask，在二进制表示中，它是00001111 
#define RSET(b, n) (b = ((LMASK & b) | (n)))  //这个宏，将b的右边设置成n 
#define LSET(b, n) (b = ((RMASK & b) | ((n) << HALF_BITS_LENGTH)))  //这个宏，将b的左边设置成n 
#define RGET(b) (RMASK & b)  //这个宏得到b的右边的值 
#define LGET(b) ((LMASK & b) >> HALF_BITS_LENGTH)  //这个宏得到b的左边的值 
#define GRIDW 3  //这个数字表示将帅移动范围的行宽度 

int main()
{
	unsigned char b;
	for (LSET(b, 1); LGET(b) <= GRIDW * GRIDW; LSET(b, (LGET(b) + 1)))
	    for (RSET(b, 1); RGET(b) <= GRIDW * GRIDW; RSET(b, (RGET(b) + 1)))
	    {
	    	if(LGET(b) % GRIDW != RGET(b) % GRIDW)
	    	{
	    		printf("A = %d, B = %d\n", LGET(b), RGET(b)); 
			} 
	    }
	    
	return 0;
} 
#endif

// Solution2: 
#if 0
#include <stdio.h>
#include "windows.h"

int main()
{
	BYTE i = 81;
	while(i--)
	{
		if(i / 9 % 3 == i % 9 % 3)
		    continue;
		printf("A = %d, B = %d\n", i / 9 + 1, i % 9 + 1);
	}
	
	return 0;
}
#endif

// Solution3: 
#include <stdio.h>
struct{
	unsigned char a:4;
	unsigned char b:4;
}i;

int main()
{
	for (i.a = 1; i.a <= 9; i.a++)
	    for (i.b = 1; i.b <= 9; i.b++)
	        if(i.a % 3 != i.b % 3)
	        {
	        	printf("A = %d, B = %d\n", i.a, i.b);
	        }
	        
	return 0;
}
