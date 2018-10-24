#include <iostream>
#include <cstring>
using namespace std;

/*
   first calculate the count of 1 in a full 1 number
   eg: 1 => cnt = 1;   11 => (01 10 11) cnt = 4;   111 => (001 010 011 100 101 110 111) cnt = 12
   so we got cnt = k * 2^(k-1)
*/

int calc(char* binary, int len)
{
   int nCnt = 1, num = 0;
   int k = len, total = 0;
   char* p = binary+1;

   if (len <= 0)
       return 0;

   while (k > 1)  // The first byte must be '1'
   {
       if (binary[k-1]=='1')
           num += nCnt;

       nCnt *= 2;
       k--;
   }
 
   if (num == (nCnt-1))      // full of 1
       return len*nCnt;
   else
       total = (len-1)*(nCnt/2);

   total += num+1;  // 最高位1的个数，由后面的低位决定，比如10010 --> 10000 10001 10010，为num + 1 

   k = 1;
   while ((*p != '1') && (k<len))
   {
       *p++; k++;
   }

   total += calc(p, len-k);
   return total;
}

int main()
{
   char* test[]= {"100", "1", "10", "11", "111",
                  "10000", "1111", "10110", "110011", "110011001"};
   int test_num = 10;
   int len = 0, i = 0, total=0;

   for (i = 0; i < test_num; i++)
   {
       len = strlen(test[i]);
       total = calc(test[i], len);

       cout << test[i] << ":  result = " << total << endl;
       cout << "\n==========================\n" << endl;
   }

   return 0;
}

