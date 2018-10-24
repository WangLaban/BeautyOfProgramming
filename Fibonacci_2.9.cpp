#include<iostream>
using namespace std;

// Solution1:
unsigned long long fibonacci(int n)
{
	if(n <= 0)
	    return 0;
	if(n == 1)
	    return 1;
	unsigned long long f1 = 0, f2 = 1;
	while(n-- >= 2)
	{
		f2 += f1;
		f1 = f2 - f1;
	}
	return f2;
}
// Solution2: 矩阵
//矩阵乘法
void matrixMulti(long long matrix[2][2],long long matrix2[2][2]){
    long long a = matrix[0][0] * matrix2[0][0] +  matrix[0][1] * matrix2[1][0];
    long long b = matrix[0][0] * matrix2[0][1] +  matrix[0][1] * matrix2[1][1];
    long long c = matrix[1][0] * matrix2[0][0] +  matrix[1][1] * matrix2[1][0];
    long long d = matrix[1][0] * matrix2[0][1] +  matrix[1][1] * matrix2[1][1];
    matrix[0][0] = a;
    matrix[0][1] = b;
    matrix[1][0] = c;
    matrix[1][1] = d;
}
//Fibonacci数列
long long fibonacci2(int value){
    if(value == 0){
        return 0;
    }
    long long A[2][2] = {1,1,1,0};
    //初始化为单位矩阵
    long long Matrix[2][2] = {1,0,1,0};
    int n = value - 1;
    for(; n ;n >>= 1){
        //奇偶
        if(n&1){
            matrixMulti(Matrix,A);
        }//if
        matrixMulti(A,A);
    }//for
    return Matrix[0][0];
}

int main()
{
	for(int i = 0; i <= 10; i++)
	cout<<fibonacci2(i)<<endl;
	
	return 0;
}
