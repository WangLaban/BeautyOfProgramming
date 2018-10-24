#include<iostream>
using namespace std;

// Solution1:
int countBitOne1(unsigned int num)
{
	int res = 0;
	while(num)
	{
		if(num % 2)
		    res++;
		num /= 2;
	}
	return res;
} 

// Solution2:
int countBitOne2(unsigned int num)
{
	int res = 0;
	while(num)
	{
		//if(num & 0x1)
		    //res++;
		res += num & 0x1;
		num >>= 1;
	}
	return res;
} 

// Solution3:
int countBitOne3(unsigned int num)
{
	int res = 0;
	while(num)
	{
		num &= (num - 1);
		res++;
	}
	return res;
} 

// Solution4:
int countBitOne4(unsigned int num)
{
    int res = 0;
    
    switch(num)
    {
        case 0x0:
             res = 0;
             break;
        case 0x1:
        case 0x2:
        case 0x4:
        case 0x8:
        case 0x10:
        case 0x20:
        case 0x40:
        case 0x80:
             res = 1;
             break;
        case 0x3:
        case 0x6:
        case 0xc:
        case 0x18:
        case 0x30:
        case 0x60:
        case 0xc0:
             res = 2;
             break; 
        //.....
    }
    return res;
}

// Solution5:
// 预定义的结果表 
int countTable[256]={
        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
};
// 只能针对一个字节的无符号整型变量 
int countBitOne5(unsigned int num)
{
    return countTable[num];
}

int main()
{
	int num = 161;
	int res = countBitOne5(num);
	cout<<"res = "<<res<<endl;
	
	return 0;
}
