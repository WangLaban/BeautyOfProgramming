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
    	//���ڸ�����������о�����������һ����С����1E-6�����ݲ�ֵ
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
            number[j] = number[n - 1];  //�����һ����ǰ�ơ�

            expa = result[i];
            expb = result[j];
            result[j] = result[n - 1];  //�����һ�����ʽǰ��

            //�ֱ���㲻ͬ�������ϣ���������a + b��a - b��b - a��a * b��a / b��b / a��Ȼ����еݹ�

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
    string expr; //�����val�ı��ʽ
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
            if((x & i) == x)  //ֻ�е�x & i == x����ʱx��Ϊi���Ӽ�����ʱi - xΪi����һ�����Ӽ���x��i - x��ͬ����i��һ������
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
                        //����f[2^n-1]ʱ����������˽�������ֹͣ
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
    set<setNode> S[len]; //��Ӧ�����е�����S
    cout<<"sizeof(S) = "<<sizeof(S)<<" len = "<<len<<endl;
    //��ʼ��ֻ��һ��Ԫ�ص��Ӽ���j = 2^i����ֻ��һ��2����λ��1
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

