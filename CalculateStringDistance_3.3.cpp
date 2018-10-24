#if 0
#include <iostream>
#include <string>
using namespace std;

// Solution1: Recurse
int calculateStringDistance(string strA, int pABegin, int pAEnd, string strB, int pBBegin, int pBEnd)
{
	if (pABegin > pAEnd)
	{
		if (pBBegin > pBEnd)
			return 0;
		else
			return pBEnd - pBBegin + 1;
	}
	if (pBBegin > pBEnd)
	{
		if (pABegin > pAEnd)
			return 0;
		else
			return pAEnd - pABegin + 1;
	}
	if (strA[pABegin] == strB[pBBegin])
	{
		return calculateStringDistance(strA, pABegin + 1, pAEnd, strB, pBBegin + 1, pBEnd);
	}
	else
	{
		int t1 = calculateStringDistance(strA, pABegin, pAEnd, strB, pBBegin + 1, pBEnd);
		int t2 = calculateStringDistance(strA, pABegin + 1, pAEnd, strB, pBBegin, pBEnd);
		int t3 = calculateStringDistance(strA, pABegin + 1, pAEnd, strB, pBBegin + 1, pBEnd);
		return min(min(t1, t2), t3) + 1;
	}
}

// Solution2: DP
/*
   * DP Algorithm
　 * A loop method using dynamic programming.
　 * Calculate from bottom to top.
*/
 int calculateStringDistance2(string strA, string strB)
 {
     int lenA = (int)strA.length();
	 int lenB = (int)strB.length();
	 int c[lenA+1][lenB+1]; 
	 // Record the distance of all begin points of each string
	 //初始化方式与背包问题有点不同
	 for(int i = 0; i < lenA; i++) c[i][lenB] = lenA - i;
	 for(int j = 0; j < lenB; j++) c[lenA][j] = lenB - j;
	 c[lenA][lenB] = 0;
	 for(int i = lenA-1; i >= 0; i--)
	     for(int j = lenB-1; j >= 0; j--)
		 {
		     if(strB[j] == strA[i])
			     c[i][j] = c[i+1][j+1];
			 else
			     c[i][j] = min(min(c[i][j+1], c[i+1][j]), c[i+1][j+1]) + 1;
		}
		return c[0][0];
}
int main()
{
	string A = "xabcde";
	string B = "wxxabcds";
	//cout << calculateStringDistance(A, 0, A.length() - 1, B, 0, B.length()-1) << endl;
	cout<<calculateStringDistance2(A, B)<<endl;
	return 0;
}
#endif

// Solution3:
#include <iostream>
#define M 100

using namespace std;

const bool debug = false; // Whether to print debug info
const bool memoize = true; // Whether to use memoization
unsigned int cnt = 0; // Line number for the debug info

int memoizedDistance[M][M]; // Matrix for memoiztion
 
int minValue(int a, int b, int c)
{
    if(a < b && a < c) return a;
	else if(b < a && b < c) return b;
	else return c;
}
 
/*
    * A recursive method which can be decorated by memoization.
    * Calculate from top to bottom.
*/
int calculateStringDistance(string strA, int pABegin, int pAEnd, string strB, int pBBegin, int pBEnd)
{
    if(memoize && memoizedDistance[pABegin][pBBegin] >= 0)
	    return memoizedDistance[pABegin][pBBegin];
	if(pABegin > pAEnd)
	{
	    if(pBBegin > pBEnd)
	    {
		    if(memoize)
			    memoizedDistance[pABegin][pBBegin] = 0;
			if(debug)
			    cout << cnt++ << ": m(" << pABegin << "," << pBBegin << ")=0" << endl;
			return 0;
		}
		else
		{
		    int temp = pBEnd - pBBegin + 1;
			if(memoize)
			    memoizedDistance[pABegin][pBBegin] = temp;
			if(debug)
			    cout << cnt++ << ": m(" << pABegin << "," << pBBegin << ")=" << temp << endl;
			return temp;
		}
	}
	if(pBBegin > pBEnd)
	{
	    if(pABegin > pAEnd)
		{
		    if(memoize)
			    memoizedDistance[pABegin][pBBegin] = 0;
			if(debug)
			    cout << cnt++ << ": m(" << pABegin << "," << pBBegin << ")=0" << endl;
		    return 0;
		}
		else
		{
		    int temp = pAEnd - pABegin + 1;
			if(memoize)
			    memoizedDistance[pABegin][pBBegin] = temp;
			if(debug)
			    cout << cnt++ << ": m(" << pABegin << "," << pBBegin << ")=" << temp << endl;
			return temp;
		}
	}
	if(strA[pABegin] == strB[pBBegin])
	{
	    int temp = calculateStringDistance(strA, pABegin+1, pAEnd, strB, pBBegin+1, pBEnd);
		if(memoize)
		    memoizedDistance[pABegin][pBBegin] = temp;
		if(debug)
		    cout << cnt++ << ": m(" << pABegin << "," << pBBegin << ")=" << temp << endl;
		return temp;
	}
	else
	{
	    int t1 = calculateStringDistance(strA, pABegin, pAEnd, strB, pBBegin+1, pBEnd);
		int t2 = calculateStringDistance(strA, pABegin+1, pAEnd, strB, pBBegin, pBEnd);
		int t3 = calculateStringDistance(strA, pABegin+1, pAEnd, strB, pBBegin+1, pBEnd);
		int temp = minValue(t1, t2, t3) + 1;
		if(memoize)
		    memoizedDistance[pABegin][pBBegin] = temp;
		if(debug)
		    cout << cnt++ << ": m(" << pABegin << "," << pBBegin << ")=" << temp << endl;
		return temp;
	}
}
 
int main()
{
    if(memoize)
	{
	     // initialize the matrix : memoizedDistance[][]
		 for(int i = 0; i < M; i++)
		     for(int j = 0; j < M; j++)
			     memoizedDistance[i][j] = -1; // -1 means unfilled cell yet
	}
	string strA = "abcdfef";
	string strB = "a";
 
    cout << endl << "Similarity = " << 1.0 / (1 + calculateStringDistance(strA, 0, (int)strA.length()-1, strB, 0, (int)strB.length()-1)) << endl;
    return 0;
}
