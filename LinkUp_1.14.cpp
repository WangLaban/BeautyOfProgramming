#include <stdio.h>

//
//����Point�ṹ
//
struct Point
{
    int x;
    int y;
};

//
//�趨һЩ����
//
#define M 19 //����
#define N 11 //���
#define BLANK 0 //�հ׸��ʶ
Point arr1[M*N];
int a1Len=0;
Point arr2[M*N];
int a2Len=0;
Point corner[2]; //�洢�յ�
int corNum=0; //��ʶ�յ�ĸ���
int map[M][N]; //��ʾÿ���������Ƿ����ͼƬ
Point nArr[M*N]; //���ڴ洢ĳ���ʮ�����ϵĿհ׵�

//
//��ʼ��map�Լ������յ�
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
//�ж������հ׵������Ƿ���ڹ����
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
//�ж������Ƿ���ֱ������
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
//���ظ���һ�����ˮƽ���봹ֱ���ϵĿհ׵������ĳ���
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
//�ж������Ƿ���ڷ�ֱ�ߵ�����
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
//�ж�����֮���Ƿ���ںϷ�������
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
