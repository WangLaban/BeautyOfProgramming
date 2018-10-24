#if 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//检测sd[i][j]上的值是否符合要求
bool isOk(int sd[][9], int i, int j)
{
	int temp = sd[i][j];
	int p, q, m, n;
	
	//行 列 
	for(p = 0; p < 9; p++)
		if(p != i && sd[p][j] == temp)
			return false;
	for(p = 0; p < 9; p++)
		if(p !=j && sd[i][p] == temp)
			return false;
	p = i/3;
	q = j/3;
	for(m = p * 3; m < p * 3 + 3; m++)
		for(n = q * 3; n < q * 3 + 3; n++)
			if(!(m == i && n == j) && sd[m][n] == temp)
				return false;
	return true;
}
 
//输出
void print(int sd[][9])
{
	int i, j;
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
			printf("%4d", sd[i][j]);
		printf("\n");
	}
}
 
int main()
{
    int sd[9][9];
    int i, j, temp = 0;
    int k;
 
	memset(sd, 0, sizeof(sd));
	//随机赋值几个位置
    for(i = 0; i < 9; i++)
	{
		temp = rand() % 81;
		sd[temp / 9][temp % 9] = i + 1;
	}
	//回溯法
	k = 0;
    while(1)
    {
        i = k/9;
        j = k % 9;
		while(1)
		{
			sd[i][j]++;
			if(sd[i][j] > 9)  //1-9都不满足条件 
			{
				sd[i][j] = 0;  //回溯，退至上一个 
        		--k;
				break;
			}
			else if(isOk(sd, i, j))  //满足条件 
			{
				++k;
				break;
			}
		}
 
		if(k == 81)
		{
			print(sd);
			return 0;
		}
    }
    return 0;
}
#endif

#include <stdio.h>
#include <stdlib.h> 
int main()
{
    int m[3][3];    //初始3*3
    int sd[9][9];
    int k, i, j, temp;
 
	k = 1; 
    for(i = 0; i < 3; i++)   
        for(j = 0; j < 3; j++)     
            m[i][j] = k++;
        
    for(i = 0; i < 9; i++)
    {
        temp = rand() % 9;  //随机交换 
        j = m[i / 3][i % 3];
        m[i / 3][i % 3] = m[temp / 3][temp % 3];
        m[temp / 3][temp % 3] = j;
    }
 
 
    printf("Initial matrix: \n");
    for(i = 0; i < 3; i++)
    {
	    for (j = 0; j < 3; j++)
            printf("%-5d", m[i][j]);
        printf("\n");
    }
 
    for(i = 0; i < 3; i++)  //解决中间，加上下左右 
    {
        for (j = 0; j < 3; j++)
        {
            sd[i + 3][j + 3] = m[i][j];  //中央的数 
            if(i == 0)
            {
                sd[i + 4][j] = m[i][j];  //左边 第二行 m[4][0-2]
                sd[i + 5][j + 6] = m[i][j];  //右边 第三行m[5][6-8]
            }
            else if(i == 1)
            {
                sd[i + 4][j] = m[i][j];  //左边 第三行 m[5][0-2]
                sd[i + 2][j + 6] = m[i][j];  //右边 第一行m[3][6-8]
            }
            else
            {
                sd[i + 1][j] = m[i][j];  //左边 第一行 m[3][0-2]
                sd[i + 2][j + 6] = m[i][j];  //右边 第二行m[4][6-8]
            }
 
            if(j == 0)
            {
                sd[i][j + 4] = m[i][j];  //上面 第2列 = 第1列 m[0-2][4]
                sd[i + 6][j + 5] = m[i][j];  //下面 第3列 = 第1列 m[6-8][5]
            }
            else if(j == 1)
            {
                sd[i][j + 4] = m[i][j];  //上面 第3列 = 第2列 m[0-2][5]
                sd[i + 6][j + 2] = m[i][j];  //下面 第1列 = 第2列 m[6-8][3]
            }
            else
            {
                sd[i][j + 1] = m[i][j];  //上面 第1列 = 第3列 m[0-2][3]
                sd[i + 6][j + 2] = m[i][j];  //下面 第2列 = 第3列 m[6-8][4]
            }
        }
    }
 
    for(i = 3; i < 6; i++)  //解决 
    {
        for (j = 0; j < 3; j++)
        {
            if(j == 0)
            {
                sd[i - 3][j + 1] = sd[i][j];
                sd[i + 3][j + 2] = sd[i][j];
            }
            else if(j == 1)
            {
                sd[i - 3][j + 1] = sd[i][j];
                sd[i + 3][j - 1] = sd[i][j];
            }
            else
            {
                sd[i - 3][j - 2] = sd[i][j];
                sd[i + 3][j - 1] = sd[i][j];
            }
        }
    }
 
    for(i = 3; i < 6; i++)
    {
        for (j = 6; j < 9; j++)
        {
            if(j == 6)
            {
                sd[i - 3][j + 1] = sd[i][j];
                sd[i + 3][j + 2] = sd[i][j];
            }
            else if(j == 7)
            {
                sd[i - 3][j + 1] = sd[i][j];
                sd[i + 3][j - 1] = sd[i][j];
            }
            else
            {
                sd[i - 3][j - 2] = sd[i][j];
                sd[i + 3][j - 1] = sd[i][j];
            }
        }
    }
 
    printf("Final matrix: \n");
    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 9; j++)
            printf("%-5d", sd[i][j]);
        printf("\n");
    }
 
    return 0;
}


