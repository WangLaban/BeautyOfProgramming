#include<iostream>
#include<queue>
using namespace std;

struct Node {
    Node *pLeft;
    Node *pRight;
    int data;
};

// Solution1:
void PrintNodeByLevel(Node* root) {
     vector<Node*> vec; // ��������ʹ��STL �е�vector���������飬�����õ��䶯̬��չ������
     vec.push_back(root);
     int cur = 0;
     int last = 1;
     while(cur < vec.size()) {
          last = vec.size(); // �µ�һ�з��ʿ�ʼ�����¶�λlast�ڵ�ǰ�����һ���ڵ����һ��λ��
          while(cur < last) {
               cout << vec[cur] -> data << " "; // ���ʽڵ�
               if(vec[cur] -> pLeft) // ��ǰ���ʽڵ����ڵ㲻Ϊ����ѹ��
                   vec.push_back(vec[cur] -> pLeft);
               if(vec[cur] -> pRight) // ��ǰ���ʽڵ���ҽڵ㲻Ϊ����ѹ�룬ע�����ҽڵ�ķ���˳���ܵߵ�
                   vec.push_back(vec[cur] -> pRight);
               cur++;
          }
          cout << endl; // ��cur == lastʱ,˵���ò���ʽ�����������з�
     }
}

// Solution2:
void PrintNodeByLevel2(Node* root) {
    deque<Node*> Q1, Q2;
    Q1.push_back(root);
    do {
        do {
            Node* node = Q1.front();
            Q1.pop_front();
            cout << node->data << " ";
            if (node->pLeft)
                Q2.push_back(node->pLeft);
            if (node->pRight)
                Q2.push_back(node->pRight);
        } while (!Q1.empty());
        cout << endl;
        Q1.swap(Q2); 
    } while(!Q1.empty());
}

// Solution3:
void PrintNodeByLevel3(Node* root) {
    queue<Node*> Q;
    Q.push(root);
    Q.push(0);
    do {
        Node* node = Q.front();
        Q.pop();
        if (node) {
            cout << node->data << " ";
            if (node->pLeft)
                Q.push(node->pLeft);
            if (node->pRight)
                Q.push(node->pRight);
        }
        else if (!Q.empty()) {
            Q.push(0);
            cout << endl;
        }
    } while (!Q.empty());
}

void Link(Node* nodes, int parent, int left, int right) {
    if (left != -1)
        nodes[parent].pLeft = &nodes[left]; 
 
    if (right != -1)
        nodes[parent].pRight = &nodes[right];
}

void PrintBFS(Node* root) {
    queue<Node*> Q;
    Q.push(root);
    do {
        Node *node = Q.front();
        Q.pop();
        cout << node->data << " ";
        if (node->pLeft)
            Q.push(node->pLeft);
        if (node->pRight)
            Q.push(node->pRight);
    }
    while (!Q.empty());
}

int main()
{
    Node test1[9] = { 0 };
     
    for (int i = 1; i < 9; i++)
        test1[i].data = i;
 
    Link(test1, 1, 2, 3);
    Link(test1, 2, 4, 5);
    Link(test1, 3, 6, -1);
    Link(test1, 5, 7, 8);
 
    PrintBFS(&test1[1]);
    cout << endl << endl;
 
    PrintNodeByLevel3(&test1[1]);
    cout << endl;
    
    return 0;
} 
