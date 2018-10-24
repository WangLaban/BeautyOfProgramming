#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Solution {
public:
    void letterCombinations(string& digits,int index,string* map,string words,vector<string>& res)
    {
    	if(index == digits.size())//�õ�һ�����
    	{
    		res.push_back(words);
    		return;
    	}
    	int i;
    	for(i = 0; i < map[digits[index] - '0'].size();++i)//ȡ��index�������ϵ�ÿһ���ַ���������ȵݹ�
    	{
    		letterCombinations(digits,index + 1,map,words+map[digits[index] - '0'][i],res);
    	}
    }
    vector<string> letterCombinations(string digits) {
    	string map[10] = {"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};//���ֺ���ĸ�Ķ�Ӧ��ϵ
    	vector<string> res;
    	letterCombinations(digits,0,map,"",res);
    	return res;
    }
};

int main()
{
	string nums = "789";
	vector<string> res = Solution().letterCombinations(nums);
	for(auto i : res)
	    cout<<i<<" ";
	cout<<endl;
	
	return 0;
}
