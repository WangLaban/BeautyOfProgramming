#include<iostream>
#include<cassert>
using namespace std;

void output(int beg, int len) { printf("%d-%d\n", beg, beg + len - 1); }

inline void output2(int i, int j) { output((i - j + 1) / 2u, j); }

 

//������

void seq3(int n)          

{                        //2*n = (2*m+k-1)*k //m, m+1, ... m+k-1

 if (n <= 0) return;   // 

 unsigned count = 1;  

 while (n % 2u == 0) { n /= 2u; ++count; } //ȥ��������2,��f = 2^x   

 for (unsigned i = 1; ;i += 2) { //��ȡnn���������� nn = i * j �� i <= j

    unsigned j = n / i;

    if (i > j) break;

    if (n % i) continue;

    output2(j << count, i); //k=i  2m+k-1=j*2*f 

    if (i == j) break;

    unsigned t = i << count;   

    if (t > j) output2(t, j);  

    else output2(j, t);

 }

 printf("\n");

}

 

 

//������

void seq4(int n)          

{                        //2*n = (2*m+k-1)*k //m, m+1, ... m+k-1

 if (n <= 0) return;   // 

 unsigned count = 1;  

 while (n % 2u == 0) { n /= 2u; ++count; } //ȥ��������2,��f = 2^x

 n -= 1 * 1;   

 for (unsigned i = 1; n >= 0; n -= 4 * i + 4, i += 2) { //��ȡnn����������

    if (n % i == 0) {     // nn = (i+a)*i -> a = (nn - i * i) / i

      unsigned j = n / i + i;

      output2(j << count, i); //k=i 2m+k-1=j*2*f   

      if (i == j) continue;

      unsigned t = i << count;     

      if (t > j) output2(t, j);  

      else output2(j, t);

    }  

 }

 printf("\n");

}

 

 

//������

unsigned gn = 0; //ֵΪ 2 * n

static void factor(unsigned n, unsigned k = 1, unsigned beg = 3)

{

 assert(n & 1);

 assert(beg & 1);

 if (n == 1) {

    unsigned t = ::gn / k;

    if (t > k) output2(t, k);

    else output2(k, t);

    return;

 }

 assert(n >= beg);

 

 for (unsigned i = beg, count = 0; ;i += 2) {

    //if (n % i) {

    // if (n / i >= i) continue;

    // factor(1, k, n);   // n������

    // factor(1, k * n, n);

    // return; 

    //}

    if (i > n / i) {

      factor(1, k);   // n��������

      factor(1, k * n);

      return;       

    }

    if (n % i) continue;

   

    ++count;

    n /= i;

    while (n % i == 0) { ++count; n /= i; }

    for (unsigned j = 0, f = k; j <= count; ++j, f *= i) 

      factor(n, f, i + 2);

    return;  

 }

}

 

void seq(int n)          

{                        //2*n = (2*m+k-1)*k //m, m+1, ... m+k-1

 if (n <= 0) return;

 ::gn = n * 2u;

 while (n % 2u == 0) { n /= 2u;} //ȥ��������2

 factor(n);

 printf("\n");

}

int main()
{
	int n;
	cout<<"����һ����������"<<endl;
	cin>>n;
	
	seq(n);
	
	return 0;
}
