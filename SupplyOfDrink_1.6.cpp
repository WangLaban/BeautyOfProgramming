#include<iostream>
#include<vector>
#include<string>
#include<cmath>
using namespace std;

struct Drink{
	string name;
	int capacity;
	int count;
	int satisfaction;
};
int Cal(int V, int T, vector<Drink> drink)
{
	vector<vector<int>> opt(V + 1, vector<int>(T + 1, 0));
	for(int j = T - 1; j >= 0; j--)
	{
		for(int i = 0; i <= V; i++)
		{
			opt[i][j] = 0;
			for(int k = 0; k <= drink[j].count; k++)
			{
				if(i < k * pow(2, drink[j].capacity))
				{
					break;
				}
				int x = opt[i - k * pow(2, drink[j].capacity)][j + 1] + drink[j].satisfaction * k;
				//cout<<"i = "<<i<<" j = "<<j<<" k = "<<k<<" drink[j].count = "<<drink[j].count<<" drink[j].capacity = "<<drink[j].capacity<<" x = "<<x<<endl;
				if(x > opt[i][j])
				{
					opt[i][j] = x;
				}
			}
		}
	}
	return opt[V][0];
} 

int main()
{
	Drink suanNai = {"suanNai", 0, 2, 2};
	Drink douJiang = {"douJiang", 0, 2, 3};
	Drink lvCha = {"lvCha", 0, 3, 5};
	Drink wangLaoJi = {"wangLaoJi", 0, 3, 4};
	Drink coffee = {"coffee", 1, 2, 6};
	Drink cola = {"cola", 1, 3, 5};
	Drink xianChengDuo = {"xianChengDuo", 1, 4, 4};
	Drink sprite = {"sprite", 2, 1, 18};
	Drink maiDong = {"maiDong", 2, 2, 12};
	vector<Drink> drink{suanNai, douJiang, lvCha, wangLaoJi, coffee, cola, xianChengDuo, sprite, maiDong};
	
	const int volume = 7;
	int res = Cal(volume, drink.size(), drink);
	cout<<"res = "<<res<<endl;
	
	return 0;
}
