#if 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//���sd[i][j]�ϵ�ֵ�Ƿ����Ҫ��
bool isOk(int sd[][9], int i, int j)
{
	int temp = sd[i][j];
	int p, q, m, n;
	
	//�� �� 
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
 
//���
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
	//�����ֵ����λ��
    for(i = 0; i < 9; i++)
	{
		temp = rand() % 81;
		sd[temp / 9][temp % 9] = i + 1;
	}
	//���ݷ�
	k = 0;
    while(1)
    {
        i = k/9;
        j = k % 9;
		while(1)
		{
			sd[i][j]++;
			if(sd[i][j] > 9)  //1-9������������ 
			{
				sd[i][j] = 0;  //���ݣ�������һ�� 
        		--k;
				break;
			}
			else if(isOk(sd, i, j))  //�������� 
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
    int m[3][3];    //��ʼ3*3
    int sd[9][9];
    int k, i, j, temp;
 
	k = 1; 
    for(i = 0; i < 3; i++)   
        for(j = 0; j < 3; j++)     
            m[i][j] = k++;
        
    for(i = 0; i < 9; i++)
    {
        temp = rand() % 9;  //������� 
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
 
    for(i = 0; i < 3; i++)  //����м䣬���������� 
    {
        for (j = 0; j < 3; j++)
        {
            sd[i + 3][j + 3] = m[i][j];  //������� 
            if(i == 0)
            {
                sd[i + 4][j] = m[i][j];  //��� �ڶ��� m[4][0-2]
                sd[i + 5][j + 6] = m[i][j];  //�ұ� ������m[5][6-8]
            }
            else if(i == 1)
            {
                sd[i + 4][j] = m[i][j];  //��� ������ m[5][0-2]
                sd[i + 2][j + 6] = m[i][j];  //�ұ� ��һ��m[3][6-8]
            }
            else
            {
                sd[i + 1][j] = m[i][j];  //��� ��һ�� m[3][0-2]
                sd[i + 2][j + 6] = m[i][j];  //�ұ� �ڶ���m[4][6-8]
            }
 
            if(j == 0)
            {
                sd[i][j + 4] = m[i][j];  //���� ��2�� = ��1�� m[0-2][4]
                sd[i + 6][j + 5] = m[i][j];  //���� ��3�� = ��1�� m[6-8][5]
            }
            else if(j == 1)
            {
                sd[i][j + 4] = m[i][j];  //���� ��3�� = ��2�� m[0-2][5]
                sd[i + 6][j + 2] = m[i][j];  //���� ��1�� = ��2�� m[6-8][3]
            }
            else
            {
                sd[i][j + 1] = m[i][j];  //���� ��1�� = ��3�� m[0-2][3]
                sd[i + 6][j + 2] = m[i][j];  //���� ��2�� = ��3�� m[6-8][4]
            }
        }
    }
 
    for(i = 3; i < 6; i++)  //��� 
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


