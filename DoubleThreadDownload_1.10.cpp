#define BUFFER_COUNT 100  //定义数据队列中数据块的数目。
//每一个数据块将是下载线程和存储线程操作的基本的单元
BLOCK g_buffer[BUFFER_COUNT];//数据缓冲区队列

Thread g_ThreadA(ProcA);//下载线程
Thread g_ThreadB(ProcB);//存储线程
//信号量，表示现在在数据队列中已经存放满数据的数据块的数量
Semaphore g_seFull(0,BUFFER_COUNT);
//信号量，表示现在在数据队列中空数据块的数量
Semaphore g_seEmpty(BUFFER_COUNT,BUFFER_COUNT);
bool g_downloadComplete = false;
int in_index = 0;//表示当前下载线程正在处理的数据块的编号
int out_index = 0;//表示当前存储线程正在处理的数据块的编号

void main()
{
     g_ThreadA.start();//启动下载线程
     g_ThreadB.start();//启动存储线程
     Wait();
}

//下载线程的工作函数
void ProcA()
{
     while(true)
     {
           //申请一个空的数据块的资源
          g_seEmpty.Unsignal();  
          //申请到空的数据块，向in_index指向的BLOCK下载数据
          g_downloadComplete = GetBlockFromNet(g_buffer + in_index);
          //in_index更新
          in_index = (in_index + 1) % BUFFER_CONUT;  
          g_seFull.Signal();//报告又有一个新的数据块已经下载完毕，可以指向写入操作...
         if(g_downloadComplete)
                break;
     }
}

//存储线程的工作函数
void ProcB()
{
     while(true)
     {
           //申请一个满的数据块的资源
          g_seFull.Unsignal();  
          //申请到满的数据块，从out_index指向的BLOCK获取数据，写入Disk。
          WriteBlockToDisk(g_buffer + out_index);
          //out_index更新
          out_index = (out_index + 1) % BUFFER_CONUT;  
          g_seEmpty.Signal();//报告又有一个新的数据块已经写入完毕，可以下载覆盖其数据...
         if(g_downloadComplete && out_index == in_index)
               break;
     }
}
