/*3.1 �ַ�����λ����������
���������ַ���s1��s2��Ҫ���ж�s2�Ƿ��ܹ���s1��ѭ����λ(rotate)�õ����ַ���������
���磺
����s1=AABCD��s2=CDAA������true
����s1=ABCD��s2=ACBD������false
*/
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

/*����һ���ж��ַ���t�Ƿ��ܹ���s��ѭ����λ(rotate)�õ����ַ���������
ʹ����ֱ�ӵķ�����s����ѭ����λ��0-len��λ���ٽ����ַ����������ж���
ʱ�临�Ӷ�O(n^2)
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
 
		/*�ַ��������ж�,
		strstr����strstr(str1,str2) ���������ж��ַ���str2�Ƿ���str1���Ӵ���
		����ǣ���ú�������str2��str1���״γ��ֵĵ�ַ�����򣬷���NULL��*/
		if (strstr(s.c_str(),t.c_str()) != NULL)
			return true;
	}//for
	return false;
}

/*���������ж��ַ���t�Ƿ��ܹ���s��ѭ����λ(rotate)�õ����ַ���������
�������õ����ɣ���s��ѭ����λ�õ����ַ�������ss���Ӵ������Կ���ֱ���ж�t�Ƿ�
Ϊss���Ӵ����ɡ�
*/
bool judge2(string s, string t)
{
	string ss = s + s;
	/*string�ڲ�����find �ҵ��Ļ������صľ��ǵ�һ���ҵ����ַ����ĵ�һ����ĸ����ţ�û���ҵ��ͷ���-1*/
	return ss.find(t) != -1;
}

int main()
{
	string s = "ABCD", t = "ACBD";
	cout << judge1(s, t) << endl;
	cout << judge2(s, t) << endl;

	return 0;
}
