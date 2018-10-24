/**
* 本题目内容如下：
* 在计算机中，有时使用float或double来存储小数是不能得到精确值的. 如果你需要得到精确计算结果，最好是用分数形式来表示小数。有限小数或者无限循环小数都可以转化为分数。
* eg：	0.9 = 9/10;
*	0.33(3) = 1/3(括号里的数字表示的的是循环节)
* 当然一个小数可以用好几种弄分数形式来表示. 如:
* 0.33(3) = 1 / 3 = 3 / 9;
* 给定一个有限小数或无限循环小数, 你能否异分母最小的分数形式来返回这个小数呢?
* 如果输入为循环小数, 循环节用括号标记出来.
*/

/**
* 在此处假定, 输入的数字以回车为结束. 由于输入中带有括号, 所以可以把数字看成是字符串, 以字符的形式读入.
* 新创建一个结构体用于表示分数, 结构体字段有两个即可: 一个分子, 一个分母;
* 如此一来, 对于有限小数, 本题便转换成了求两个数字的最小公约数了.
* 对于无限循环小数, 本题相对来说复杂一些, 需要寻求一种方法来计算出其循环节部分对应的分数形式
*/

#if 1
#include<stdio.h>
#include<stdlib.h>

struct fraction
{
    int numerator;	// 分子
    int denominator;	// 分母
};

int power(int base, int power)
{
    int i = 0;
    int product = 1;
    for (; i < power; ++i)
        product *= base;
    return product;
}

int ctoi(char ch[], int length)
{
    int i;
    int target = 0;
    for (i = length - 1; i >= 0; --i)
	{
        target += (ch[length - i - 1] - '0') * power(10, i);
    }
    return target;
}

int Substract(int x, int y)
{
    int min, max, temp;
    if (x > y)
	{
        max = x;
        min = y;
    }
	else
	{
        max = y;
        min = x;
    }
    while(max - min != 0)
	{
        temp = max - min;
        if (temp > min)
            max = temp;
        else
		{
		    max = min;
			min = temp;
		}
	}
	return min;
}

// 此函数中用于转化有限小数, 首先将小数部分转化为整数, 然后求小数部分与10^ld的最大公约数, 上下约分, 得到分数形式
struct fraction LimitedDecimals(char integer[], int li, char decimal[], int ld)
{
    struct fraction frac;
	int numerator;
	int denominator;
	int divisor;
	numerator = ctoi(decimal, ld);
	denominator = power(10, ld);
	divisor = Substract(numerator, denominator);
	numerator /= divisor;
	denominator /= divisor;
	numerator += ctoi(integer, li) * denominator;
	frac.numerator = numerator;
	frac.denominator = denominator;
	return frac;
}

// 此函数中用于转化无限循环小数
// integer为整数部分, decimal为小数不循环部分, cycle为循环节
// 将循环节部分转换成小数之后, 由于其位于小数点右侧ld位处, 因此需要除以10^ld, 再加上decimal转换成的分数部分, 然后再加上整数部分即可.
// 循环节转换算法:
// Y = 0.(C1C2…Cm)
// Y * 10^m = (C1C2…Cm).C1C2…Cm = C1C2…Cm + 0.(C1C2…Cm)
// Y * 10^m - Y = C1C2…Cm
// 所以, Y = C1C2…Cm / (10^m - 1)
// X = 0.a1a2...an(b1b2...bm) = ((a1a2...an) * (10 ^ m - 1) + (b1b2...bm)) / ((10 ^ m - 1) * 10 ^ n)
struct fraction InfiniteLoopDecimal(char integer[], int li, char decimal[], int ld, char cycle[], int lc)
{
    struct fraction frac;
    int numerator;	// 分子
    int denominator;	// 分母
    int numerator1, numerator2;
    int denominator1, denominator2;
    int divisor;
    // 将循环部分转换成分数
    numerator1 = ctoi(cycle, lc);	// 循环部分分子
    denominator1 = (power(10, lc) - 1) * power(10, ld);	// 循环部分分母
    //numerator2 = ctoi(decimal, ld);
    //denominator2 = power(10, ld);
    //denominator = denominator1 * denominator2;
    //numerator = numerator1 * denominator2 + numerator2 * denominator1;
    numerator2 = ctoi(decimal, ld) * (power(10, lc) - 1);
    numerator = numerator1 + numerator2;
    denominator = denominator1;
    divisor = Substract(numerator, denominator);
    numerator /= divisor;
    denominator /= divisor;
    numerator += ctoi(integer, li) * denominator;
    frac.numerator = numerator;
    frac.denominator = denominator;
    return frac;
}

int main()
{
    // 分别定义三个字符串数组, 分别用于存储小数的整数部分、小数部分以及循环节
    char integer[100];	// 整数部分
    char decimal[100];	// 小数部分
    char cycle[100];	// 循环节
    int li, ld, lc;	// 分别记录整数部分、小数部分和循环节的长度
    char ch;
    struct fraction frac;
    while ((ch = getchar()) != EOF)
	{
        li = 0;
		ld = 0;
		lc = 0;
		while (ch != '.' && ch != '\n')
		{
		    integer[li++] = ch;
			ch = getchar();
		}
		integer[li] = '\0';
		if (ch == '\n')
		{
		    printf("这是个整数: %d\n", ctoi(integer, li));
		    continue;
		}
		while ((ch = getchar()) != '(' && ch != '\n')
		{
		    decimal[ld++] = ch;
		}
		decimal[ld] = '\0';
		if (ch == '(')
		{
		    while((ch = getchar()) != ')')
			{
			    cycle[lc++] = ch;
			}
			cycle[lc] = '\0';
		}
		while (ch != '\n')
		    ch = getchar();
		if (lc == 0)
		{
		    printf("这是个有限小数: ");
			frac = LimitedDecimals(integer, li, decimal, ld);
			printf("%d/%d\n", frac.numerator, frac.denominator);
			continue;
		}
		printf("这是个无限循环小数: ");
		frac = InfiniteLoopDecimal(integer, li, decimal, ld, cycle, lc);
		printf("%d/%d\n", frac.numerator, frac.denominator);
	}
	return 0;
}
#endif

#if 0
//用于大整数，定义了大整数类型，以及对应的加减乘除、比较移位运算
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

// 大整数类型
#define MAXLEN 1000
struct HP {int len, s[MAXLEN];};

void PrintHP(HP x) 
{
	for (int i=x.len; i>=1; i--)
		cout << x.s[i];
}

// 字符串转大整数
void Str2HP(const char *s, HP &x)
{
	x.len = strlen(s);
	for (int i=1; i<=x.len; i++)
		x.s[i] = s[x.len-i] - '0';
	if (x.len == 0)
	{
		x.len = 1;
		x.s[1] = 0;
	}
}

// 大整数的加法
void Plus(const HP a, const HP b, HP &c)
{
	int i; c.s[1] = 0;
	// 大整数a,b的加法操作和结果c的进位操作
	for (i=1; i<=a.len || i<=b.len || c.s[i]; i++)
	{
		if (i <= a.len) c.s[i] += a.s[i];
		if (i <= b.len) c.s[i] += b.s[i];
		c.s[i+1] = c.s[i]/10; c.s[i] %= 10;
	}
	// 退出循环到原因是c.s[i]==0，所以取前一位
	c.len = i-1; 
	if (c.len == 0) c.len = 1;
}

// 大整数的减法
void Subtract(const HP a, const HP b, HP &c)
{
	int i, j;
	for (i=1,j=0; i<=a.len; i++)
	{
		// j表示是否要对高位进行借位
		c.s[i] = a.s[i] - j;
		if (i <= b.len) c.s[i] -= b.s[i];
		if (c.s[i] < 0) 
		{
			// 向高位借位，补10
			j = 1;
			c.s[i] += 10;
		}
		else j = 0;
	}
	c.len = a.len;
	while (c.len > 1 && !c.s[c.len]) c.len--;
}

// 大整数的比较
int HPCompare(const HP &x, const HP &y)
{
	if (x.len > y.len) return 1;
	if (x.len < y.len) return -1;
	int i = x.len;
	while (i>1 && (x.s[i]==y.s[i])) i--;
	return x.s[i] - y.s[i];
}

// 大整数的乘法
void Multi(const HP a, const HP b, HP &c)
{
	int i, j;
	// 对乘法结果赋初值，以方便之后的+=运算
	c.len = a.len + b.len;
	for (i=1; i<=c.len; i++) c.s[i] = 0;
	for (i=1; i<=a.len; i++)
		for (j=1; j<=b.len; j++)
			c.s[i+j-1] += a.s[i]*b.s[j];
	// 运算结果进位
	for (i=1; i<c.len; i++) {c.s[i+1] += c.s[i]/10; c.s[i] %= 10;}
	// 最高位继续进位
	while (c.s[i]) {c.s[i+1] = c.s[i]/10; c.s[i] %= 10; i++;}
	// 确保最高位不为0
	while (i>1 && !c.s[i]) i--;
	c.len = i;
}

// 大整数的除法
void Divide(const HP a, const HP b, HP &c, HP &d)
{
	int i, j;
	// 用余数d存被除数a的前i位数据，用来多次减去除数b，以得到商c
	d.len = 1; d.s[1] = 0;
	for (i=a.len; i>0; i--)
	{
		if (!(d.len == 1 && d.s[1] == 0))
		{
			// i没移一位，余数d也移位
			for (j=d.len; j>0; j--)
				d.s[j+1] = d.s[j];
			d.len++;
		}
		d.s[1] = a.s[i];
		c.s[i] = 0;
		// 余数d大于除数b时，才可以进行减操作
		while ((j=HPCompare(d,b)) >= 0)
		{
			Subtract(d, b, d);
			c.s[i]++;
			if (j == 0) break;
		}
	}
	c.len = a.len;
	while (c.len > 1 && c.s[c.len] == 0)
		c.len--;
}
// 十进位右移
void RightShift(HP &x, int k)
{
	for (int i=1; i<=x.len-k; i++)
		x.s[i] = x.s[i+k];
	x.len -= k;
	if(x.len <= 0)
	{
		x.len = 1;
		x.s[1] = 0;
	}
}
// 十进位左移
void LeftShift(HP &x, int k)
{
	int i;
	for (i=x.len; i>=1; i--)
		x.s[i+k] = x.s[i];
	for (i=k; i>=1; i--)
		x.s[i] = 0;
	x.len += k;
}
// 求大整数的最大公约数
void GCD(HP a, HP b, HP &c)
{
	if (b.len == 1 && b.s[1] == 0)
	{
		c.len = a.len;
		memcpy(c.s, a.s, (a.len+1)*sizeof(int));
	}
	else
	{
		HP m, n;
		Divide(a, b, m, n);
		GCD(b, n, c);
	}
}

int main()
{
	string str;
	string strc, stra, strb;
	cin >> str;
	int posc = str.find('.');
	int posa = str.find('(');
	int posb = str.find(')');
	strc = str.substr(0, posc);
	if (posc < 0)
		cout << strc;
	else
	{	
		HP a, b, c;
		HP tmp; tmp.len = 1; tmp.s[1] = 1;
		// 整数部分
		Str2HP(strc.c_str(), c);
		stra = str.substr(posc+1, posa-posc-1);
		// 非循环部分
		Str2HP(stra.c_str(), a);
		// up分子，down分母
		HP up = c, down = tmp;
		// 乘以10^|a|
		LeftShift(down, stra.size());
		LeftShift(up, stra.size());
		Plus(up, a, up);
		if (posa >= 0)
		{
			strb = str.substr(posa+1, posb-posa-1);
			// 循环部分
			Str2HP(strb.c_str(), b);
			HP m = tmp;
			LeftShift(m, strb.size());
			Subtract(m, tmp, m);
			// 乘以10^(|b|-1)
			Multi(up, m, up);
			Plus(up, b, up);
			Multi(down, m, down);
		}
		// 求分子分母的最大公约数
		GCD(down, up, tmp);
		HP h;
		Divide(down, tmp, down, h);
		Divide(up, tmp, up, h);
		PrintHP(up); cout << "/";
		PrintHP(down); cout << endl;
	}
}
#endif
