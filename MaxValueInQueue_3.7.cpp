#if 0
#include <iostream>
#include <algorithm>  
#include <vector>  
using namespace std;  
  
// 用最大堆来维护队列中的节点,队列用单链表表示，每个节点包含数据，  
// 而最大堆用数组表示,数组元素为节点的指针  
class Queue  
{  
public:  
    // 模拟队列的链表节点  
    struct Node  
    {  
        Node(int d):data(d),next(0){}  
        int data;  
        Node *next;  
    };  
  
    Queue() {begin=end=0;vec.push_back(NULL);}  
    // O(logn)时间内将节点加入队列  
    void EnQueue(int data)  
    {  
        Node *nd = new Node(data);  
        // 若队列中没有节点  
        if (vec.size() == 1)  
        {  
            begin = end = 1;  
            vec.push_back(nd);  
            return;  
        }  
        // 若队列中已有节点，将其连上单链表  
        vec.push_back(nd);  
        vec[end]->next = nd;  
        // 用shift_up在大顶堆中确定其位置  
        end = vec.size()-1;  
        while (end>>1 >= 1)  
        {  
            if (nd->data <= vec[end>>1]->data)  
                break;  
            vec[end] = vec[end>>1];  
            // 元素移动可能会使队列中第一个节点的位置发生改变  
            if (end>>1 == begin)  
                begin = end;  
            end >>= 1;  
        }  
        vec[end] = nd;  
    }  
    // O(n)时间内从队列中删去节点  
    int DeQueue()  
    {  
        // 若队列中没有节点  
        if (vec.size() == 1)   
        {  
            begin = end = 0;  
            return 0;  
        }  
        // 将第一个节点删去  
        int data = vec[begin]->data;  
        Node *nextnd = vec[begin]->next;  
        delete vec[begin];  
        // 若删除的节点的位置不是vec的最后一个元素  
        if (begin < vec.size()-1)  
        {  
            Node *nd = vec[vec.size()-1];  
            vec.pop_back();  
            // 执行shift_down确定vec最后一个元素在begin子树中的位置  
            int nextbegin = begin<<1;  
            while (nextbegin <= vec.size()-1)    // 边界约束  
            {  
                // 找到两个子元素中较大的元素  
                if (nextbegin+1 <= vec.size()-1 &&   
                    vec[nextbegin+1]->data > vec[nextbegin]->data)  
                    nextbegin++;  
                // 若vec最后一个元素比较大元素，则它的位置是begin  
                if (nd ->data >= vec[nextbegin]->data)  
                    break;  
                vec[begin] = vec[nextbegin];  
                // 元素的移动可能会使队列中最后一个节点的位置发生改变  
                if (nextbegin == end)  
                    end = begin;  
                begin = nextbegin;  
                nextbegin <<= 1;  
            }  
            vec[begin] = nd;  
            // 如果vec最后一个元素是最后一个节点的位置,则将其设为begin  
            if (end >= vec.size())  
                end = begin;  
        }  
        else  
            // 若删除的节点的位置是vec的最后一个元素  
            vec.pop_back();  
        // 在大顶堆中找到队列中的第二个元素耗时O(n),还需优化  
        int i;  
        for (i=1; i<vec.size(); ++i)  
            if (vec[i] == nextnd)  
                break;  
        begin = i;  
        return data;  
    }  
  
    // O(1)的时间内得到最大值元素  
    int maxElement()  
    {  
        return vec[1]->data;  
    }  
  
private:  
    vector<Node*> vec;    // 模拟大顶堆的数组(从1开始)  
    int begin, end;     // 队列的第一个节点和最后一个节点在数组中的位置  
};  
  
  
int main()  
{  
    const int n = 11;  
    int data[] = {7, 4, 15, 9, 5, 10, 13, 3, 20, 17, 19};  
    int i;  
    Queue q;  
    for (i=0; i<n/2; i++)  
        q.EnQueue(data[i]); 
    cout<<"maxValue = "<<q.maxElement()<<endl;
    int d = q.DeQueue();  
    d = q.DeQueue();  
    d = q.DeQueue();  
    d = q.DeQueue();  
    d = q.DeQueue();  
    d = q.DeQueue();  
    d = q.DeQueue();  
    for (; i<n; i++)  
        q.EnQueue(data[i]);
    cout<<"maxValue = "<<q.maxElement()<<endl;
    
    return 0;
}
#endif

#include<iostream>
using namespace std;


#define MAXN    100
class Stack
{
    public:
        //构造函数，初始化堆栈：
        //|stackTop|指向当前堆栈的顶部元素，
        //|maxStackItemIndex|存储当前堆栈中最大元素的index
        Stack(){
            stackTop = -1;
            maxStackItemIndex = -1;
        }
 
        //判断当前堆栈是否为空
        bool isEmpty() {
            return stackTop == -1;
        }
 
        //判断当前堆栈是否满
        bool isFull() {
            return stackTop == MAXN - 1;
        }
 
        //向堆栈中push元素，
        void push(int x) {
            if(this->isFull()) {                //首先检测堆栈空间是否满
                cout<<"the stack is full now."<<endl;
            }
            else {
                stackItem[++stackTop] = x;
                //如果压入堆栈的值比之前记录的最大值大，那么那之前的最大值记录在
                //link2NextMaxItem[stackTop]的位置，把当前最大值在堆栈stackItem
                //中的位置用maxStackItemIndex保存
                if(x > maxValue()) {
                    link2NextMaxItem[stackTop] = maxStackItemIndex;  //将x入栈之前最大元素的下标存入link2NextMaxItem[stackTop]
                    maxStackItemIndex = stackTop;  //最大下标maxStackItemIndex更新为x的下标stackTop
                }
                else
                    link2NextMaxItem[stackTop] = -1;
            }
        }
 
        int pop(){
            int ret;
            if(this->isEmpty()) {
                cout<<"the stack is empty."<<endl;
            }
            else {
                ret = stackItem[stackTop];
                //如果pop出的值是当前的最大值，那么则需要将之前保存到link2NextMaxItem[stackTop]
                //中的最大值取出，更新maxStackItemIndex的值
                if( stackTop == maxStackItemIndex )
                {
                    maxStackItemIndex = link2NextMaxItem[stackTop];  //若最大值出栈，则将最大值下标更新为link2NextMaxItem[stackTop]中保存的次大值下标
                }
            }
            --stackTop;
            return ret;
        }
 
        //取出堆栈中当前的最大值
        int maxValue(){
            if(maxStackItemIndex >= 0)
                return stackItem[maxStackItemIndex];
            else{
                return INT_MIN;
            }
        }
        void printItems() {
            for (int i = 0; i <= stackTop; ++i) {
                cout<<" "<<stackItem[i];
            }
        }
        void reversePrintItems() {
            for (int i = stackTop; i >= 0; --i) {
                cout<<" "<<stackItem[i];
            }
        }
    private:
        int stackItem[MAXN];
        int stackTop;
        int link2NextMaxItem[MAXN];
        int maxStackItemIndex;
};
class Queue
{
    public:
        int maxValue(int x, int y) {
            if(x>y)
                return x;
            else
                return y;
        }
 
        //返回队列中最大值
        int max() {
            return maxValue(stackA.maxValue(), stackB.maxValue());
        }
        
        void printQueue() {
            stackA.reversePrintItems();
            stackB.printItems();
            cout<<endl;
        }
 
        //在队列末尾插入元素
        void insertQueue(int x) {
            stackB.push(x);
        }
 
        //删除并返回队首元素,
        //如果stackA中是空，则先将stackB中的所有元素pop到stackA中，
        //这样stackB中先插入的元素就会pop到stackA中的顶部
        int deQueue() {
            if(stackA.isEmpty()) {
                while(!stackB.isEmpty())
                    stackA.push(stackB.pop());
            }
            return stackA.pop();
        }
    private:
        Stack stackA;    //维护出队列操作
        Stack stackB;    //维护入队列操作
};
int main()
{
    Queue queue;
    int a[] = {909, 2, 3, 4, 9, 4, 5, 10, 6};
    for(int i = 0; i < sizeof(a)/sizeof(int); ++i) {
        queue.insertQueue(a[i]);
    }
    queue.insertQueue(101);
    cout<<"queue maxvalue = "<<queue.max()<<endl;
    queue.insertQueue(590);
    cout<<"queue maxvalue = "<<queue.max()<<endl;
    queue.printQueue();
    int deq = queue.deQueue();
    cout<<"deq = "<<deq<<endl;
    cout<<"queue maxvalue = "<<queue.max()<<endl;
}

