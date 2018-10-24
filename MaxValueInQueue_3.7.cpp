#if 0
#include <iostream>
#include <algorithm>  
#include <vector>  
using namespace std;  
  
// ��������ά�������еĽڵ�,�����õ������ʾ��ÿ���ڵ�������ݣ�  
// �������������ʾ,����Ԫ��Ϊ�ڵ��ָ��  
class Queue  
{  
public:  
    // ģ����е�����ڵ�  
    struct Node  
    {  
        Node(int d):data(d),next(0){}  
        int data;  
        Node *next;  
    };  
  
    Queue() {begin=end=0;vec.push_back(NULL);}  
    // O(logn)ʱ���ڽ��ڵ�������  
    void EnQueue(int data)  
    {  
        Node *nd = new Node(data);  
        // ��������û�нڵ�  
        if (vec.size() == 1)  
        {  
            begin = end = 1;  
            vec.push_back(nd);  
            return;  
        }  
        // �����������нڵ㣬�������ϵ�����  
        vec.push_back(nd);  
        vec[end]->next = nd;  
        // ��shift_up�ڴ󶥶���ȷ����λ��  
        end = vec.size()-1;  
        while (end>>1 >= 1)  
        {  
            if (nd->data <= vec[end>>1]->data)  
                break;  
            vec[end] = vec[end>>1];  
            // Ԫ���ƶ����ܻ�ʹ�����е�һ���ڵ��λ�÷����ı�  
            if (end>>1 == begin)  
                begin = end;  
            end >>= 1;  
        }  
        vec[end] = nd;  
    }  
    // O(n)ʱ���ڴӶ�����ɾȥ�ڵ�  
    int DeQueue()  
    {  
        // ��������û�нڵ�  
        if (vec.size() == 1)   
        {  
            begin = end = 0;  
            return 0;  
        }  
        // ����һ���ڵ�ɾȥ  
        int data = vec[begin]->data;  
        Node *nextnd = vec[begin]->next;  
        delete vec[begin];  
        // ��ɾ���Ľڵ��λ�ò���vec�����һ��Ԫ��  
        if (begin < vec.size()-1)  
        {  
            Node *nd = vec[vec.size()-1];  
            vec.pop_back();  
            // ִ��shift_downȷ��vec���һ��Ԫ����begin�����е�λ��  
            int nextbegin = begin<<1;  
            while (nextbegin <= vec.size()-1)    // �߽�Լ��  
            {  
                // �ҵ�������Ԫ���нϴ��Ԫ��  
                if (nextbegin+1 <= vec.size()-1 &&   
                    vec[nextbegin+1]->data > vec[nextbegin]->data)  
                    nextbegin++;  
                // ��vec���һ��Ԫ�رȽϴ�Ԫ�أ�������λ����begin  
                if (nd ->data >= vec[nextbegin]->data)  
                    break;  
                vec[begin] = vec[nextbegin];  
                // Ԫ�ص��ƶ����ܻ�ʹ���������һ���ڵ��λ�÷����ı�  
                if (nextbegin == end)  
                    end = begin;  
                begin = nextbegin;  
                nextbegin <<= 1;  
            }  
            vec[begin] = nd;  
            // ���vec���һ��Ԫ�������һ���ڵ��λ��,������Ϊbegin  
            if (end >= vec.size())  
                end = begin;  
        }  
        else  
            // ��ɾ���Ľڵ��λ����vec�����һ��Ԫ��  
            vec.pop_back();  
        // �ڴ󶥶����ҵ������еĵڶ���Ԫ�غ�ʱO(n),�����Ż�  
        int i;  
        for (i=1; i<vec.size(); ++i)  
            if (vec[i] == nextnd)  
                break;  
        begin = i;  
        return data;  
    }  
  
    // O(1)��ʱ���ڵõ����ֵԪ��  
    int maxElement()  
    {  
        return vec[1]->data;  
    }  
  
private:  
    vector<Node*> vec;    // ģ��󶥶ѵ�����(��1��ʼ)  
    int begin, end;     // ���еĵ�һ���ڵ�����һ���ڵ��������е�λ��  
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
        //���캯������ʼ����ջ��
        //|stackTop|ָ��ǰ��ջ�Ķ���Ԫ�أ�
        //|maxStackItemIndex|�洢��ǰ��ջ�����Ԫ�ص�index
        Stack(){
            stackTop = -1;
            maxStackItemIndex = -1;
        }
 
        //�жϵ�ǰ��ջ�Ƿ�Ϊ��
        bool isEmpty() {
            return stackTop == -1;
        }
 
        //�жϵ�ǰ��ջ�Ƿ���
        bool isFull() {
            return stackTop == MAXN - 1;
        }
 
        //���ջ��pushԪ�أ�
        void push(int x) {
            if(this->isFull()) {                //���ȼ���ջ�ռ��Ƿ���
                cout<<"the stack is full now."<<endl;
            }
            else {
                stackItem[++stackTop] = x;
                //���ѹ���ջ��ֵ��֮ǰ��¼�����ֵ����ô��֮ǰ�����ֵ��¼��
                //link2NextMaxItem[stackTop]��λ�ã��ѵ�ǰ���ֵ�ڶ�ջstackItem
                //�е�λ����maxStackItemIndex����
                if(x > maxValue()) {
                    link2NextMaxItem[stackTop] = maxStackItemIndex;  //��x��ջ֮ǰ���Ԫ�ص��±����link2NextMaxItem[stackTop]
                    maxStackItemIndex = stackTop;  //����±�maxStackItemIndex����Ϊx���±�stackTop
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
                //���pop����ֵ�ǵ�ǰ�����ֵ����ô����Ҫ��֮ǰ���浽link2NextMaxItem[stackTop]
                //�е����ֵȡ��������maxStackItemIndex��ֵ
                if( stackTop == maxStackItemIndex )
                {
                    maxStackItemIndex = link2NextMaxItem[stackTop];  //�����ֵ��ջ�������ֵ�±����Ϊlink2NextMaxItem[stackTop]�б���Ĵδ�ֵ�±�
                }
            }
            --stackTop;
            return ret;
        }
 
        //ȡ����ջ�е�ǰ�����ֵ
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
 
        //���ض��������ֵ
        int max() {
            return maxValue(stackA.maxValue(), stackB.maxValue());
        }
        
        void printQueue() {
            stackA.reversePrintItems();
            stackB.printItems();
            cout<<endl;
        }
 
        //�ڶ���ĩβ����Ԫ��
        void insertQueue(int x) {
            stackB.push(x);
        }
 
        //ɾ�������ض���Ԫ��,
        //���stackA���ǿգ����Ƚ�stackB�е�����Ԫ��pop��stackA�У�
        //����stackB���Ȳ����Ԫ�ؾͻ�pop��stackA�еĶ���
        int deQueue() {
            if(stackA.isEmpty()) {
                while(!stackB.isEmpty())
                    stackA.push(stackB.pop());
            }
            return stackA.pop();
        }
    private:
        Stack stackA;    //ά�������в���
        Stack stackB;    //ά������в���
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

