/**
* ����Ŀ�������£�
* �ڼ�����У���ʱʹ��float��double���洢С���ǲ��ܵõ���ȷֵ��. �������Ҫ�õ���ȷ��������������÷�����ʽ����ʾС��������С����������ѭ��С��������ת��Ϊ������
* eg��	0.9 = 9/10;
*	0.33(3) = 1/3(����������ֱ�ʾ�ĵ���ѭ����)
* ��Ȼһ��С�������úü���Ū������ʽ����ʾ. ��:
* 0.33(3) = 1 / 3 = 3 / 9;
* ����һ������С��������ѭ��С��, ���ܷ����ĸ��С�ķ�����ʽ���������С����?
* �������Ϊѭ��С��, ѭ���������ű�ǳ���.
*/

/**
* �ڴ˴��ٶ�, ����������Իس�Ϊ����. ���������д�������, ���Կ��԰����ֿ������ַ���, ���ַ�����ʽ����.
* �´���һ���ṹ�����ڱ�ʾ����, �ṹ���ֶ�����������: һ������, һ����ĸ;
* ���һ��, ��������С��, �����ת���������������ֵ���С��Լ����.
* ��������ѭ��С��, ���������˵����һЩ, ��ҪѰ��һ�ַ������������ѭ���ڲ��ֶ�Ӧ�ķ�����ʽ
*/

#if 1
#include<stdio.h>
#include<stdlib.h>

struct fraction
{
    int numerator;	// ����
    int denominator;	// ��ĸ
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

// �˺���������ת������С��, ���Ƚ�С������ת��Ϊ����, Ȼ����С��������10^ld�����Լ��, ����Լ��, �õ�������ʽ
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

// �˺���������ת������ѭ��С��
// integerΪ��������, decimalΪС����ѭ������, cycleΪѭ����
// ��ѭ���ڲ���ת����С��֮��, ������λ��С�����Ҳ�ldλ��, �����Ҫ����10^ld, �ټ���decimalת���ɵķ�������, Ȼ���ټ����������ּ���.
// ѭ����ת���㷨:
// Y = 0.(C1C2��Cm)
// Y * 10^m = (C1C2��Cm).C1C2��Cm = C1C2��Cm + 0.(C1C2��Cm)
// Y * 10^m - Y = C1C2��Cm
// ����, Y = C1C2��Cm / (10^m - 1)
// X = 0.a1a2...an(b1b2...bm) = ((a1a2...an) * (10 ^ m - 1) + (b1b2...bm)) / ((10 ^ m - 1) * 10 ^ n)
struct fraction InfiniteLoopDecimal(char integer[], int li, char decimal[], int ld, char cycle[], int lc)
{
    struct fraction frac;
    int numerator;	// ����
    int denominator;	// ��ĸ
    int numerator1, numerator2;
    int denominator1, denominator2;
    int divisor;
    // ��ѭ������ת���ɷ���
    numerator1 = ctoi(cycle, lc);	// ѭ�����ַ���
    denominator1 = (power(10, lc) - 1) * power(10, ld);	// ѭ�����ַ�ĸ
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
    // �ֱ��������ַ�������, �ֱ����ڴ洢С�����������֡�С�������Լ�ѭ����
    char integer[100];	// ��������
    char decimal[100];	// С������
    char cycle[100];	// ѭ����
    int li, ld, lc;	// �ֱ��¼�������֡�С�����ֺ�ѭ���ڵĳ���
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
		    printf("���Ǹ�����: %d\n", ctoi(integer, li));
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
		    printf("���Ǹ�����С��: ");
			frac = LimitedDecimals(integer, li, decimal, ld);
			printf("%d/%d\n", frac.numerator, frac.denominator);
			continue;
		}
		printf("���Ǹ�����ѭ��С��: ");
		frac = InfiniteLoopDecimal(integer, li, decimal, ld, cycle, lc);
		printf("%d/%d\n", frac.numerator, frac.denominator);
	}
	return 0;
}
#endif

#if 0
//���ڴ������������˴��������ͣ��Լ���Ӧ�ļӼ��˳����Ƚ���λ����
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

// ����������
#define MAXLEN 1000
struct HP {int len, s[MAXLEN];};

void PrintHP(HP x) 
{
	for (int i=x.len; i>=1; i--)
		cout << x.s[i];
}

// �ַ���ת������
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

// �������ļӷ�
void Plus(const HP a, const HP b, HP &c)
{
	int i; c.s[1] = 0;
	// ������a,b�ļӷ������ͽ��c�Ľ�λ����
	for (i=1; i<=a.len || i<=b.len || c.s[i]; i++)
	{
		if (i <= a.len) c.s[i] += a.s[i];
		if (i <= b.len) c.s[i] += b.s[i];
		c.s[i+1] = c.s[i]/10; c.s[i] %= 10;
	}
	// �˳�ѭ����ԭ����c.s[i]==0������ȡǰһλ
	c.len = i-1; 
	if (c.len == 0) c.len = 1;
}

// �������ļ���
void Subtract(const HP a, const HP b, HP &c)
{
	int i, j;
	for (i=1,j=0; i<=a.len; i++)
	{
		// j��ʾ�Ƿ�Ҫ�Ը�λ���н�λ
		c.s[i] = a.s[i] - j;
		if (i <= b.len) c.s[i] -= b.s[i];
		if (c.s[i] < 0) 
		{
			// ���λ��λ����10
			j = 1;
			c.s[i] += 10;
		}
		else j = 0;
	}
	c.len = a.len;
	while (c.len > 1 && !c.s[c.len]) c.len--;
}

// �������ıȽ�
int HPCompare(const HP &x, const HP &y)
{
	if (x.len > y.len) return 1;
	if (x.len < y.len) return -1;
	int i = x.len;
	while (i>1 && (x.s[i]==y.s[i])) i--;
	return x.s[i] - y.s[i];
}

// �������ĳ˷�
void Multi(const HP a, const HP b, HP &c)
{
	int i, j;
	// �Գ˷��������ֵ���Է���֮���+=����
	c.len = a.len + b.len;
	for (i=1; i<=c.len; i++) c.s[i] = 0;
	for (i=1; i<=a.len; i++)
		for (j=1; j<=b.len; j++)
			c.s[i+j-1] += a.s[i]*b.s[j];
	// ��������λ
	for (i=1; i<c.len; i++) {c.s[i+1] += c.s[i]/10; c.s[i] %= 10;}
	// ���λ������λ
	while (c.s[i]) {c.s[i+1] = c.s[i]/10; c.s[i] %= 10; i++;}
	// ȷ�����λ��Ϊ0
	while (i>1 && !c.s[i]) i--;
	c.len = i;
}

// �������ĳ���
void Divide(const HP a, const HP b, HP &c, HP &d)
{
	int i, j;
	// ������d�汻����a��ǰiλ���ݣ�������μ�ȥ����b���Եõ���c
	d.len = 1; d.s[1] = 0;
	for (i=a.len; i>0; i--)
	{
		if (!(d.len == 1 && d.s[1] == 0))
		{
			// iû��һλ������dҲ��λ
			for (j=d.len; j>0; j--)
				d.s[j+1] = d.s[j];
			d.len++;
		}
		d.s[1] = a.s[i];
		c.s[i] = 0;
		// ����d���ڳ���bʱ���ſ��Խ��м�����
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
// ʮ��λ����
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
// ʮ��λ����
void LeftShift(HP &x, int k)
{
	int i;
	for (i=x.len; i>=1; i--)
		x.s[i+k] = x.s[i];
	for (i=k; i>=1; i--)
		x.s[i] = 0;
	x.len += k;
}
// ������������Լ��
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
		// ��������
		Str2HP(strc.c_str(), c);
		stra = str.substr(posc+1, posa-posc-1);
		// ��ѭ������
		Str2HP(stra.c_str(), a);
		// up���ӣ�down��ĸ
		HP up = c, down = tmp;
		// ����10^|a|
		LeftShift(down, stra.size());
		LeftShift(up, stra.size());
		Plus(up, a, up);
		if (posa >= 0)
		{
			strb = str.substr(posa+1, posb-posa-1);
			// ѭ������
			Str2HP(strb.c_str(), b);
			HP m = tmp;
			LeftShift(m, strb.size());
			Subtract(m, tmp, m);
			// ����10^(|b|-1)
			Multi(up, m, up);
			Plus(up, b, up);
			Multi(down, m, down);
		}
		// ����ӷ�ĸ�����Լ��
		GCD(down, up, tmp);
		HP h;
		Divide(down, tmp, down, h);
		Divide(up, tmp, up, h);
		PrintHP(up); cout << "/";
		PrintHP(down); cout << endl;
	}
}
#endif
