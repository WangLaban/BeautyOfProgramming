// Ҫ�󣺴�����ֻ��ʹ��һ���ֽڴ洢���� 
// Solution1: 
#if 0
#include <stdio.h>
#define HALF_BITS_LENGTH 4  //���ֵ�Ǽ���洢��Ԫ���ȵ�һ�룬�����������4bit 
#define FULLMASK 255  //������ֱ�ʾһ��ȫ��bit��mask���ڶ����Ʊ�ʾ�У�����11111111 
#define LMASK (FULLMASK << HALF_BITS_LENGTH)  //������ʾ��bits��mask���ڶ����Ʊ�ʾ�У�����11110000 
#define RMASK (FULLMASK >> HALF_BITS_LENGTH)  //������ʾ��bits��mask���ڶ����Ʊ�ʾ�У�����00001111 
#define RSET(b, n) (b = ((LMASK & b) | (n)))  //����꣬��b���ұ����ó�n 
#define LSET(b, n) (b = ((RMASK & b) | ((n) << HALF_BITS_LENGTH)))  //����꣬��b��������ó�n 
#define RGET(b) (RMASK & b)  //�����õ�b���ұߵ�ֵ 
#define LGET(b) ((LMASK & b) >> HALF_BITS_LENGTH)  //�����õ�b����ߵ�ֵ 
#define GRIDW 3  //������ֱ�ʾ��˧�ƶ���Χ���п�� 

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
