#if 0
// Solution1:
#include<iostream>
#include<cstring>
using namespace std;

int find_M(int N) {
  // �߽����� 
  if(N == 1)
    return 1;
  // ��ʼ���������� 
  int *A = new int[N]; // ��¼���е�������A[i]��ʾ��N������Ϊi����С������������ֵ
  int *B = new int[N]; // ��¼���µ�����
  memset(A, -1, N*sizeof(int));
  A[1] = 1;
  // Ѱ�ҹ��� 
  int factor = 10;
  bool not_found = true;
  while(not_found) {
    memset(B, -1, N*sizeof(int));
    int x = factor % N; // ��λ��ֵ��N������
    // ��λ��ֵ + 0 ����� 
    if(A[x] == -1) {
      B[x] = factor;
      if(x == 0)
        break;
    }
    // ��λ��ֵ + ��λ����������� 
    for(int i=1; i<N; i++) { // ����ÿ�����ܵ�����
      if(A[i] == -1)
        continue;
      int new_x = (x + i) % N; // �����������
      if(A[new_x] == -1 && B[new_x] == -1) { // �����һ���µ�����������
        B[new_x] = factor + A[i]; 
        if(new_x == 0) { // �պ��ҵ����µ�������0 
          not_found = false;
          break;
        }// if         
      }// if      
    }//for
    factor *= 10;
    for(int i=0; i<N; i++) {
      if(A[i]==-1 && B[i]!=-1) {
        A[i] = B[i];
      }
    }
  }// while
  int result = B[0];
  delete[] A;
  delete[] B;
  return result;
}

int main() {
  int N;
  while(true) {
    cout << "N��";
    cin >> N;
    if(N < 1)
      break;
    cout << "M��" << find_M(N)/N << endl;
    cout << "������Ϊ��" << find_M(N)/N*N << endl;
  }
  
  return 0;
}
#endif

// Solution2: 
#include <iostream>
#include <vector>
using namespace std;

typedef unsigned char uchar;

//BigInt�д洢M * N�Ľ���� 1��λ��
void GetSmallestM(int N, vector<vector<uchar>>& BigInt)
{
    int i , j;
    vector<uchar> init;
    init.clear();
    //��ʼ�� ÿһ��������յ�
    for(i = 0; i < N; i++)
    {
        BigInt.push_back(init);
    }
    BigInt[1].push_back('0'); //����Ϊ1����С�����϶���1 ��0λ��1

    int NoUpdate = 0;
    //i ��ʾ��ǰ���λ�� 10^i �η�   j��ʾ 10^i % N��ֵ 100 % N = ((10 % N) * 10) % N ע�� j�����ʾ�����ķ���
    for(i = 1, j = 10 % N; ; i++, j = (j * 10) % N) 
    {
        bool flag = false;
        //�����µ����� �洢
        if(BigInt[j].size() == 0)
        {
            flag = true;
            BigInt[j].clear();
            BigInt[j].push_back(i + '0');
        }
        //�Ե�ǰ���е��������� �ж� (j + k) % N�Ƿ����������
        for(int k = 1; k < N; k++)
        {
            if(BigInt[j].size() > 0 && 
                (BigInt[k].size() > 0 && i > (BigInt[k][BigInt[k].size() - 1] - '0')) //���������ʾ��ǰ�������ǿ� �� ��ǰ������������Ϊ��ǰi�� ��Щ��kѭ�������в����� BigInt��ÿһ���в�������ͬ������
                && BigInt[(k + j) % N].size() == 0)
            {
                flag = true;
                BigInt[(k + j) % N] = BigInt[k];
                BigInt[(k + j) % N].push_back(i + '0');
            }
        }
        if(flag == false)
            NoUpdate++;
        else
            NoUpdate = 0;

        //�������һ��ѭ����û�и��� ���޽� ���� ��Ϊѭ��N�ζ�û�г����µ����� ��N������һ������N��
        //�ҵ�����Ҳ����
        if(NoUpdate == N || BigInt[0].size() > 0)
            break;
    }
    if(BigInt[0].size() == 0)
    {
        cout << "M not exist" << endl;
    }
    else
    {
        return;
    }
}

int main()
{
    vector<vector<uchar>>  BigInt;
    GetSmallestM(99, BigInt);
    if(BigInt[0].size() == 0)
        cout<<"M not exist."<<endl;
    else
    {
    	for(int i = 0; i < BigInt[0].size(); i++)
    	    cout<<(BigInt[0][i] - '0');
    	cout<<endl;
    }
    return 0;
}
