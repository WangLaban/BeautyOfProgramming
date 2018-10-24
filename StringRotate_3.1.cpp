/*3.1 字符串移位包含的问题
给定两个字符串s1和s2，要求判定s2是否能够被s1做循环移位(rotate)得到的字符串包含。
例如：
给定s1=AABCD和s2=CDAA，返回true
给定s1=ABCD和s2=ACBD，返回false
*/
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

/*方法一：判断字符串t是否能够被s做循环移位(rotate)得到的字符串包含；
使用最直接的方法对s进行循环移位（0-len）位，再进行字符串包含的判定。
时间复杂度O(n^2)
*/
bool judge1(string s, string t)
{
	if (t.empty())
		return s.empty();
 
	int sLen = s.length(), tLen = t.length();
	for (int i = 0; i < sLen; ++i)
	{
		char c = s[0];
		for (int j = 0; j < sLen - 1; ++j)
		{
			s[j] = s[j + 1];
		}//for
		s[sLen - 1] = c;
 
		/*字符串包含判断,
		strstr函数strstr(str1,str2) 函数用于判断字符串str2是否是str1的子串。
		如果是，则该函数返回str2在str1中首次出现的地址；否则，返回NULL。*/
		if (strstr(s.c_str(),t.c_str()) != NULL)
			return true;
	}//for
	return false;
}

/*方法二：判断字符串t是否能够被s做循环移位(rotate)得到的字符串包含；
分析，得到规律，对s做循环移位得到的字符串都是ss的子串，所以可以直接判断t是否
为ss的子串即可。
*/
bool judge2(string s, string t)
{
	string ss = s + s;
	/*string内部函数find 找到的话，返回的就是第一个找到的字符串的第一个字母的序号，没有找到就返回-1*/
	return ss.find(t) != -1;
}

int main()
{
	string s = "ABCD", t = "ACBD";
	cout << judge1(s, t) << endl;
	cout << judge2(s, t) << endl;

	return 0;
}
