#include <stdio.h>

//
//定义Point结构
//
struct Point
{
    int x;
    int y;
};

//
//设定一些常量
//
#define M 19 //长度
#define N 11 //宽度
#define BLANK 0 //空白格标识
Point arr1[M*N];
int a1Len=0;
Point arr2[M*N];
int a2Len=0;
Point corner[2]; //存储拐点
int corNum=0; //标识拐点的个数
int map[M][N]; //表示每个坐标上是否存在图片
Point nArr[M*N]; //用于存储某点的十字线上的空白点

//
//初始化map以及两个拐点
//
void Initial(int nmap[M][N])
{
    for(int i=0;i<M;i++)
        for(int j=0;j<N;j++)
        {
            map[i][j]=nmap[i][j];
        }
    for(int i=0;i<2;i++)
    {
        corner[i].x=0;
        corner[i].y=0;
    }
}

//
//判断两个空白点数组是否存在共享点
//
bool IsShare(Point arr1[],int a1Len,Point arr2[],int a2Len)
{
    bool result=false;
    for(int i=0;i<a1Len;i++)
        for(int j=0;j<a2Len;j++)
        {
            if((arr1[i].x==arr2[j].x)&&(arr1[i].y==arr2[j].y))
            {
                corner[0]=arr1[i];
                result=true;
            }
        }
        return result;
}


//
//判断两点是否是直线相连
//
bool IsDirectLink(int x1,int y1,int x2,int y2)
{
    if(x1==x2)
    {
        if(y1==y2) return false;
        else
        {
            int ysmaller=y1>y2?y2:y1;
            int ybigger=y1>y2?y1:y2;
            int var1=ysmaller+1;
            while((map[x1][var1]==BLANK)&&var1<N)
            {
                var1++;
            }
            if(var1==ybigger) return true;
            else return false;            
        }
    }
    if(y1==y2)
    {
        if(x1==x2) return false;
        else
        {
            int xsmaller=x1>x2?x2:x1;
            int xbigger=x1>x2?x1:x2;
            int var2=xsmaller+1;
            while((map[var2][y1]==BLANK)&&(var2<M))
            {
                var2++;
            }
            if(var2==xbigger) return true;
            else return false;
        }
    }
    return false;
}

//
//返回给定一个点的水平线与垂直线上的空白点的数组的长度
//
int FindEmpty(int x,int y)
{
    int count=0;
    int pos;

    pos=x-1;
    while((0<=pos&&pos<M)&&map[pos][y]==BLANK)
    {
        nArr[count].x=pos;
        nArr[count].y=y;
        count++;
        pos--;
    }

    pos=x+1;
    while((0<=pos&&pos<M)&&map[pos][y]==BLANK)
    {
        nArr[count].x=pos;
        nArr[count].y=y;
        count++;
        pos++;
    }

    pos=y-1;
    while((0<=pos&&pos<N)&&map[x][pos]==BLANK)
    {
        nArr[count].x=x;
        nArr[count].y=pos;
        count++;
        pos--;
    }

    pos=y+1;
    while((0<=pos&&pos<N)&&map[x][pos]==BLANK)
    {
        nArr[count].x=x;
        nArr[count].y=pos;
        count++;
        pos++;
    }

    return count;
}

//
//判断两点是否存在非直线的连线
//
bool IndirectLink(int x1,int y1,int x2,int y2)
{
    int pos=0;

    pos=y1-1;
    while((0<=pos&&pos<N)&&(map[x1][pos]==BLANK))
    {
        a1Len=FindEmpty(x1,pos);
        for(int i=0;i<a1Len;i++)
        {
            arr1[i]=nArr[i];
        }
        a2Len=FindEmpty(x2,y2);
        for(int i=0;i<a2Len;i++)
        {
            arr2[i]=nArr[i];
        }
        if(IsShare(arr1,a1Len,arr2,a2Len))
        {
            corNum=2;
            corner[1].x=x1;
            corner[1].y=pos;
            return true;
        }
        pos--;
    }

    pos=y1+1;
    while((0<=pos&&pos<N)&&(map[x1][pos]==BLANK))
    {
        a1Len=FindEmpty(x1,pos);
        for(int i=0;i<a1Len;i++)
        {
            arr1[i]=nArr[i];
        }
        a2Len=FindEmpty(x2,y2);
        for(int i=0;i<a2Len;i++)
        {
            arr2[i]=nArr[i];
        }
        if(IsShare(arr1,a1Len,arr2,a2Len))
        {
            corNum=2;
            corner[1].x=x1;
            corner[1].y=pos;
            return true;
        }
        pos++;
    }

    pos=x1-1;
    while((0<=pos&&pos<M)&&(map[pos][y1]==BLANK))
    {
        a1Len=FindEmpty(pos,y1);
        for(int i=0;i<a1Len;i++)
        {
            arr1[i]=nArr[i];
        }
        a2Len=FindEmpty(x2,y2);
        for(int i=0;i<a2Len;i++)
        {
            arr2[i]=nArr[i];
        }
        if(IsShare(arr1,a1Len,arr2,a2Len))
        {
            corNum=2;
            corner[1].x=pos;
            corner[1].y=y1;
            return true;
        }
        pos--;
    }

    pos=x1+1;
    while((0<=pos&&pos<M)&&(map[pos][y1]==BLANK))
    {
        a1Len=FindEmpty(pos,y1);
        for(int i=0;i<a1Len;i++)
        {
            arr1[i]=nArr[i];
        }
        a2Len=FindEmpty(x2,y2);
        for(int i=0;i<a2Len;i++)
        {
            arr2[i]=nArr[i];
        }
        if(IsShare(arr1,a1Len,arr2,a2Len))
        {
            corNum=2;
            corner[1].x=pos;
            corner[1].y=y1;
            return true;
        }
        pos++;
    }
    return false;
}

//
//判断两点之间是否存在合法的连线
//
bool IsLink(int x1,int y1,int x2,int y2)
{
    if(x1==x2&&y1==y2)
        return false;
    if(map[x1][y1]==map[x2][y2])
    {
        if(IsDirectLink(x1,y1,x2,y2))
        {
            corNum=0;
            return true;
        }
        else
        {
            a1Len=FindEmpty(x1,y1);
            for(int i=0;i<a1Len;i++)
            {
                arr1[i]=nArr[i];
            }

            a2Len=FindEmpty(x2,y2);
            for(int i=0;i<a2Len;i++)
            {
                arr2[i]=nArr[i];
            }

            if(IsShare(arr1,a1Len,arr2,a2Len))
            {
                corNum=1;
                return true;
            }
            else
            {
                return IndirectLink(x1,y1,x2,y2);
            }
        }
    }
    return false;
}

int main()
{    
    int nmap[M][N]={{0,0,0,0},{0,1,1,1},{0,1,0,0},{0,1,1,0},{0,0,0,0},{1,0,0,1},{0,1,0,1}};
    Initial(nmap);
    if(IsLink(1,1,3,1))
    {
        for(int i=0;i<corNum;i++)
            printf("(%d,%d)\n",corner[i].x,corner[i].y);
    }
    return 0;
}
