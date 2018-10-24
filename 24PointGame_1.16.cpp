// Solution1:
#if 0
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

const double Thershold = 1E-6;
const int CardsNumber = 4;
const int ResultValue = 24;
//double number[] = {1, 2, 7, 7};
//string result[] = {"1", "2", "7", "7"};
//double number[] = {5, 5, 5, 1};
//string result[] = {"5", "5", "5", "1"};
//double number[] = {3, 3, 7, 7};
//string result[] = {"3", "3", "7", "7"};
//double number[] = {3, 3, 8, 8};
//string result[] = {"3", "3", "8", "8"};
//double number[] = {1, 4, 5, 6};
//string result[] = {"1", "4", "5", "6"};
//double number[] = {3, 8, 8, 10};
//string result[] = {"3", "8", "8", "10"};
//double number[] = {4, 4, 10, 10};
//string result[] = {"4", "4", "10", "10"};
double number[] = {9, 9, 6, 2};
string result[] = {"9", "9", "6", "2"};

bool PointGame(int n)
{
    if(n == 1)
    {
    	//由于浮点数运算会有精度误差，所以用一个很小的数1E-6来做容差值
        if(fabs(number[0] - ResultValue) < Thershold)
        {
            cout << "result[0] = " << result[0] <<" ResultValue = " << ResultValue << endl;
            cout << "number[0] = " << number[0] << endl;
            return true;
        }
        else
        {
            return false;
        }
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            double a, b;
            string expa, expb;

            a = number[i];
            b = number[j];
            number[j] = number[n - 1];  //将最后一个数前移。

            expa = result[i];
            expb = result[j];
            result[j] = result[n - 1];  //将最后一个表达式前移

            //分别计算不同情况的组合，组合情况有a + b，a - b，b - a，a * b，a / b，b / a，然后进行递归

            result[i] = "(" + expa + "+" + expb + ")";
            number[i] = a + b;
            if(PointGame(n - 1))
                return true;

            result[i] = "(" + expa + "-" + expb + ")";
            number[i] = a - b;
            if(PointGame(n - 1))
                return true;

            result[i] = "(" + expb + "-" + expa + ")";
            number[i] = b - a;
            if(PointGame(n - 1))
                return true;

            result[i] = "(" + expa + "*" + expb + ")";
            number[i] = a * b;
            if(PointGame(n - 1))
                return true;

            if(b != 0)
            {
                result[i] = "(" + expa + "/" + expb + ")";
                number[i] = a / b;
                if(PointGame(n - 1))
                    return true;
            }
            if(a != 0)
            {
                result[i] = "(" + expb + "/" + expa + ")";
                number[i] = b / a;
                if(PointGame(n - 1))
                    return true;
            }

            number[i] = a;
            number[j] = b;
            result[i] = expa;
            result[j] = expb;
        }
    }
    return false;

}
int main()
{

    PointGame(CardsNumber);
    return 0;
}
#endif


// Solution2:
#include<iostream>
#include<cstdio>
#include<string>
#include<map>
#include<set>
#include<cmath>
#include<ctime>
using namespace std;

const double Thershold = 1E-6;

struct setNode
{
    double val;
    string expr; //运算出val的表达式
    setNode(double v, string e) : val(v), expr(e){}
    setNode(double v, char e[]) : val(v), expr(e){}
    bool operator < (const setNode &s) const
    {
        return val < s.val;
    }
};

void f(const int i, set<setNode> s[], const int len, const double result)
{
	// warning: 'sizeof' on array function parameter 's' will return size of 'std::set<setNode>*'
    //int len = sizeof(s) / sizeof(set<setNode>) - 1;  //len = 2^n - 1
    //cout<<"len = "<<len<<endl;  //len = -1
    //cout<<"i = "<<i<<" s[i].size() = "<<s[i].size()<<endl;
    if(s[i].empty() == true)
        for(int x = 1; x <= i/2; x++)
            if((x & i) == x)  //只有当x & i == x成立时x才为i的子集，此时i - x为i的另一个真子集，x与i - x共同构成i的一个划分
            {
                set<setNode>::iterator it1, it2;
                //s[i] U = fork(s[x] ,s[i-x])
                for(it1 = s[x].begin(); it1 != s[x].end(); it1++)
                    for(it2 = s[i - x].begin(); it2 != s[i - x].end(); it2++)
                    {
                        string expr;
                        double tempresult;
                        tempresult = it1->val + it2->val;
                        expr = '(' + it1->expr + '+' + it2->expr + ')';
                        s[i].insert(setNode(tempresult, expr));
                        //计算f[2^n-1]时，若计算好了结果则可以停止
                        if(i == len && tempresult == result)return;


                        tempresult = it1->val - it2->val;
                        expr = '(' + it1->expr + '-' + it2->expr + ')';
                        s[i].insert(setNode(tempresult, expr));
                        if(i == len && tempresult == result)return;
                        if(it1->val != it2->val)
                        {
                            tempresult = it2->val - it1->val;
                            expr = '(' + it2->expr + '-' + it1->expr + ')';
                            s[i].insert(setNode(tempresult, expr));
                            if(i == len && tempresult == result)return;
                        }

                        tempresult = it1->val * it2->val;
                        expr = '(' + it1->expr + '*' + it2->expr + ')';
                        s[i].insert(setNode(tempresult, expr));
                        if(i == len && tempresult == result)return;

                        if(it2->val != 0)
                        {
                            tempresult = it1->val / it2->val;
                            expr = '(' + it1->expr + '/' + it2->expr + ')';
                            s[i].insert(setNode(tempresult, expr));
                            if(i == len && tempresult == result)return;
                        }
                        if(it1->val != it2->val && it1->val != 0)
                        {
                            tempresult = it2->val / it1->val;
                            expr = '(' + it2->expr + '/' + it1->expr + ')';
                            s[i].insert(setNode(tempresult, expr));
                            if(i == len && tempresult == result)return;
                        }
                    }
            }
}

string PointGame2(int cards[], const int cardsNum, const int result)
{
    int len = 1 << cardsNum;
    set<setNode> S[len]; //对应文章中的数组S
    cout<<"sizeof(S) = "<<sizeof(S)<<" len = "<<len<<endl;
    //初始化只有一个元素的子集，j = 2^i，即只有一个2进制位是1
    for(int i = 0, j = 1; i < cardsNum; i++, j = j << 1)
    {
        char buf[30];
        sprintf(buf, "%d", cards[i]);
        S[j].insert(setNode(cards[i], buf));
    }
    for(int i = 1; i <= len - 1; i++)
        f(i, S, len - 1, result);  //2 ^ cardsNum - 1
    for(set<setNode>::iterator it = S[len - 1].begin();
        it != S[len - 1].end(); it++)
        {
            if(fabs(it->val - result) < Thershold)
                return it->expr;
        }
    return "-1";
}

int main()
{
	//int cards[] = {1, 2, 7, 7};
	//int cards[] = {5, 5, 5, 1};
	//int cards[] = {3, 3, 7, 7};
	int cards[] = {3, 3, 8, 8};
	//int cards[] = {1, 4, 5, 6};
	//int cards[] = {3, 8, 8, 10};
	//int cards[] = {4, 4, 10, 10};
	//int cards[] = {9, 9, 6, 2};
	int cardsNum = 4;
	int result = 24;
	string res = PointGame2(cards, cardsNum, result);
	cout<<res<<endl;
	return 0;
}

