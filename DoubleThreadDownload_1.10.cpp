#define BUFFER_COUNT 100  //�������ݶ��������ݿ����Ŀ��
//ÿһ�����ݿ齫�������̺߳ʹ洢�̲߳����Ļ����ĵ�Ԫ
BLOCK g_buffer[BUFFER_COUNT];//���ݻ���������

Thread g_ThreadA(ProcA);//�����߳�
Thread g_ThreadB(ProcB);//�洢�߳�
//�ź�������ʾ���������ݶ������Ѿ���������ݵ����ݿ������
Semaphore g_seFull(0,BUFFER_COUNT);
//�ź�������ʾ���������ݶ����п����ݿ������
Semaphore g_seEmpty(BUFFER_COUNT,BUFFER_COUNT);
bool g_downloadComplete = false;
int in_index = 0;//��ʾ��ǰ�����߳����ڴ�������ݿ�ı��
int out_index = 0;//��ʾ��ǰ�洢�߳����ڴ�������ݿ�ı��

void main()
{
     g_ThreadA.start();//���������߳�
     g_ThreadB.start();//�����洢�߳�
     Wait();
}

//�����̵߳Ĺ�������
void ProcA()
{
     while(true)
     {
           //����һ���յ����ݿ����Դ
          g_seEmpty.Unsignal();  
          //���뵽�յ����ݿ飬��in_indexָ���BLOCK��������
          g_downloadComplete = GetBlockFromNet(g_buffer + in_index);
          //in_index����
          in_index = (in_index + 1) % BUFFER_CONUT;  
          g_seFull.Signal();//��������һ���µ����ݿ��Ѿ�������ϣ�����ָ��д�����...
         if(g_downloadComplete)
                break;
     }
}

//�洢�̵߳Ĺ�������
void ProcB()
{
     while(true)
     {
           //����һ���������ݿ����Դ
          g_seFull.Unsignal();  
          //���뵽�������ݿ飬��out_indexָ���BLOCK��ȡ���ݣ�д��Disk��
          WriteBlockToDisk(g_buffer + out_index);
          //out_index����
          out_index = (out_index + 1) % BUFFER_CONUT;  
          g_seEmpty.Signal();//��������һ���µ����ݿ��Ѿ�д����ϣ��������ظ���������...
         if(g_downloadComplete && out_index == in_index)
               break;
     }
}
