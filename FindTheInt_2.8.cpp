#if 0
// Solution1:
#include<iostream>
#include<cstring>
using namespace std;

int find_M(int N) {
  // 边界条件 
  if(N == 1)
    return 1;
  // 初始化余数数组 
  int *A = new int[N]; // 记录已有的余数，A[i]表示对N的余数为i的最小满足条件的数值
  int *B = new int[N]; // 记录更新的余数
  memset(A, -1, N*sizeof(int));
  A[1] = 1;
  // 寻找过程 
  int factor = 10;
  bool not_found = true;
  while(not_found) {
    memset(B, -1, N*sizeof(int));
    int x = factor % N; // 高位数值对N的余数
    // 高位数值 + 0 的情况 
    if(A[x] == -1) {
      B[x] = factor;
      if(x == 0)
        break;
    }
    // 高位数值 + 低位正整数的情况 
    for(int i=1; i<N; i++) { // 遍历每个可能的余数
      if(A[i] == -1)
        continue;
      int new_x = (x + i) % N; // 计算出的余数
      if(A[new_x] == -1 && B[new_x] == -1) { // 如果是一个新的余数，保存
        B[new_x] = factor + A[i]; 
        if(new_x == 0) { // 刚好找到的新的余数是0 
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
    cout << "N：";
    cin >> N;
    if(N < 1)
      break;
    cout << "M：" << find_M(N)/N << endl;
    cout << "正整数为：" << find_M(N)/N*N << endl;
  }
  
  return 0;
}
#endif

// Solution2: 
#include <iostream>
#include <vector>
using namespace std;

typedef unsigned char uchar;

//BigInt中存储M * N的结果中 1的位置
void GetSmallestM(int N, vector<vector<uchar>>& BigInt)
{
    int i , j;
    vector<uchar> init;
    init.clear();
    //初始化 每一个都存个空的
    for(i = 0; i < N; i++)
    {
        BigInt.push_back(init);
    }
    BigInt[1].push_back('0'); //余数为1的最小的数肯定是1 第0位是1

    int NoUpdate = 0;
    //i 表示当前最高位是 10^i 次方   j表示 10^i % N的值 100 % N = ((10 % N) * 10) % N 注意 j避免表示大数的方法
    for(i = 1, j = 10 % N; ; i++, j = (j * 10) % N) 
    {
        bool flag = false;
        //出现新的余数 存储
        if(BigInt[j].size() == 0)
        {
            flag = true;
            BigInt[j].clear();
            BigInt[j].push_back(i + '0');
        }
        //对当前已有的余数遍历 判断 (j + k) % N是否出现新余数
        for(int k = 1; k < N; k++)
        {
            if(BigInt[j].size() > 0 && 
                (BigInt[k].size() > 0 && i > (BigInt[k][BigInt[k].size() - 1] - '0')) //这个条件表示当前的余数非空 且 当前的余数不是因为当前i下 早些的k循环处理中产生的 BigInt的每一项中不能有相同的数字
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

        //如果经过一个循环节没有更新 则无解 跳出 因为循环N次都没有出现新的余数 而N的余数一共最多就N种
        //找到答案了也跳出
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
