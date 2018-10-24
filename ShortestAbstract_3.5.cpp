#if 0
#include<iostream>
#include<vector>
#include<string>
#include<set>

#define USE_CPLUSPLUS0x 1

#if USE_CPLUSPLUS0x
  #include<unordered_map>
#else
  #include<map>
#endif

#include<cassert>

using std::string;
using std::vector;
using std::cout;

/*      //----
#if USE_CPLUSPLUS0x
  struct Cmp{
    bool operator()(const string* a, const string* b) const { return *a == *b; }
  } ;
  
  struct Hash{
    size_t operator()(const string* a) const { return std::hash<string>()(*a);}
  } ; 
  
  typedef std::unordered_map<const string*, size_t, Hash, Cmp> Dict;
#else
  struct Cmp{
    bool operator()(const string* sa, const string * sb) const { return *sa < *sb; }
  } ;

  typedef std::map<const string*, size_t, Cmp> Dict;
#endif 
 */
 
#if USE_CPLUSPLUS0x
  typedef std::unordered_map<string, size_t> Dict;
#else
  typedef std::map<string, size_t> Dict;
#endif


template<typename T>
void output(T beg, T end, const char str[] = "", const char sep[] = "")
{
  cout << str;
  while (beg != end) cout << *beg++ << sep;
  cout << "\n";
}

void solve(const string str[], const size_t str_sz, 
           const string keyword[], const size_t keyword_sz)
{
  if (str_sz == 0 || keyword_sz == 0) return;
  
  Dict key_idx;          //�ؼ���ӳ��Ϊ���֣��Լ����ַ����Ƚ�            
  for (size_t i = 0; i < keyword_sz; ++i) {
    //key_idx.insert(Dict::value_type(&keyword[i], i)); //----
    key_idx.insert(Dict::value_type(keyword[i], i)); 
  }
  const size_t Pos_init = -1;
  vector<size_t> prev_pos(keyword_sz, Pos_init); //�ϴ������Ĺؼ��ַ�����λ��
  std::set<size_t> pos;        //�Թؼ��ַ�����λ�ý�����������
  
  vector<size_t> old_pos;      //�ִʺ���ַ�������ԭ�ַ����е�λ�� 
  old_pos.reserve(str_sz + 1);
  old_pos.push_back(0);
  for (size_t i = 0, sum = 0; i < str_sz; ++i) {
    sum += str[i].size();
    old_pos.push_back(sum);
  }
   
  size_t beg = 0, end = 0, len = -1, count = 0;  //��¼�����ע��len������ 
  for (size_t i = 0; i < str_sz; ++i) {
    //Dict::iterator it = key_idx.find(&str[i]); //----
    Dict::iterator it = key_idx.find(str[i]);

    if (it == key_idx.end()) continue;
    
    assert(it->second < prev_pos.size());
    size_t& last_pos = prev_pos[it->second];
    if (last_pos != Pos_init)  pos.erase(last_pos); //����ǰҪ��ɾ���ɵ�
    else ++count;  //��ƥ��ؼ��� ����1
    last_pos = i;
    
    pos.insert(pos.end(), i); 
    
    assert(count <= keyword_sz);
    if (count == keyword_sz) {     //�������йؼ���
      size_t pbeg = *pos.begin();
      //std::set<size_t>::iterator it = pos.end();
      //size_t pend = *--it + 1;
      size_t pend = i + 1;
      
      assert(pbeg < old_pos.size());
      assert(pend < old_pos.size());
     
      size_t plen =  old_pos[pend] - old_pos[pbeg];
      if (plen < len) {
        len = plen;
        beg = pbeg;
        end = pend;
      }
    }
  }
  
  output(&str[0], &str[str_sz], "words:    ");
  output(&keyword[0], &keyword[keyword_sz], "keywords: ", " ");
  
  if (beg == end && !pos.empty()) {      //û�ҵ����йؼ���
    cout << "(" << pos.size() << "/" << keyword_sz << " Matched) ";
    beg = *pos.begin();
    std::set<size_t>::iterator it = pos.end();
    end = *--it + 1;
  }
  output(&str[beg], &str[end], "result:   ");
  cout << "\n";
}


template<typename T, size_t sz> 
inline size_t getsz(T (&)[sz]) { return sz; }

int main()
{
  string keyword[] = { "΢��", "�����", "����", "�й�"};
  string str[] = { 
    "΢��","����","�о�Ժ","����","��","1998","��","��","����","��","ʹ��",
    "��","ʹ","δ��","��","�����","�ܹ�","��","��","��","��","ѧ","��",
    "��","��","��Ȼ����","��","����","����","����","��","��","��","����","��",
    "��","΢��","����","�о�Ժ","��","��","�ٽ�","�����","��","��̫","����",
    "��","�ռ�","��","����","��̫","�û�","��","����","����","��","��"
  };

  solve(str, getsz(str), keyword, getsz(keyword));   
}
#endif

#include<iostream>
#include<string>
#include<map>
#include<deque>
using namespace std;

void find_min_len_abstract(string str[], string keyword[], int len_str, int len_keyword) {
// ��ʼ��map 
  map<string,int> record;
  for(int i=0; i<len_keyword; i++) {
    record[keyword[i]] = 0;
  }
  // ƥ�����
  deque<int> store; // �洢����str�йؼ��ʵ��±� 
  int min_len = 0;
  int min_index_first = -1;
  int min_index_last = -1;
  int find_key_num = 0;
  int index = 0;
  while(find_key_num < len_keyword && index < len_str) {
    if(record.find(str[index]) == record.end()) { // str[index]���ǹؼ��� 
       index++;
    }
    else { // str[index]�ǹؼ��� 
      if(record[str[index]] == 0) // ��һ���ҵ�����ؼ���
        find_key_num ++;
      record[str[index]] = record[str[index]] + 1; // ������1
      store.push_back(index); 
      index++;
    }
  }
  if(find_key_num < len_keyword) { // һ�������ժҪ��û�ҵ� 
    cout << "abstract not found " << endl;
  }
  else { // �ҵ�һ���ˣ��������Ҹ��õ� 
    min_len = store.back()- store.front() + 1;   
    min_index_first = store.front();
    min_index_last = store.back();
    // ��һ��ժҪ 
    cout << "��һ��ժҪ" << endl; 
    cout << "min len: " << min_len << endl;
    for(int i=min_index_first; i<=min_index_last; i++)
      cout << str[i] << " ";
    cout << endl; 
    cout << "---------------------------------------------" << endl;
    string need_key;
    bool already_found = true;
    while(true) {   
      if(already_found == true) { // �պ��ҵ�һ����ժҪ 
        string first_key = str[store.front()];
        record[first_key]--; // ���ٵ�ǰ��ǰ��Ĺؼ��� 
        store.pop_front(); // �ؼ��ʳ��� 
        if(record[first_key] == 0) { // ����ùؼ���û�� 
          already_found = false;
          need_key = first_key; // ��¼��ҪѰ�ҵĹؼ��� 
        }               
        else { // ���˴�����ǻ��������йؼ��ʣ�˵������һ�����̵�ժҪ 
          min_len--;
          min_index_first ++;
          cout << "���̵�ժҪ" << endl;
          cout << "min len: " << min_len << endl;
          for(int i=min_index_first; i<=min_index_last; i++)
            cout << str[i] << " ";
          cout << endl; 
          cout << "---------------------------------------------" << endl;
        }
      }
      else { // ��Ҫ����������������Ĺؼ��� 
        if(index >= len_str) { // �������ҵ���Ҫ�Ĺؼ����� 
          break;
        }
        else if(record.find(str[index]) == record.end()) { // ���ǹؼ��� 
          index++;
        }
        else { // �ǹؼ��� 
          record[str[index]] = record[str[index]]+1;
          store.push_back(index); 
          if(str[index] == need_key) { // ���û�����Ҫ�ҵ��Ĺؼ���
             already_found = true;
             if((store.back()-store.front() + 1) < min_len) { // �µ�ժҪ���� 
               min_len = store.back() - store.front() + 1;
               min_index_first = store.front();
               min_index_last = store.back();
               // ���̵�ժҪ
               cout << "���̵�ժҪ" << endl;
               cout << "min len: " << min_len << endl;
               for(int i=min_index_first; i<=min_index_last; i++)
                 cout << str[i] << " ";
               cout << endl; 
               cout << "---------------------------------------------" << endl;
             }
             else {
               cout << "���Ǹ��̵�ժҪ" << endl;
               cout << "min len: " << store.back() - store.front() + 1 << endl;
               for(int i=store.front(); i<=store.back(); i++)
                 cout << str[i] << " ";
               cout << endl; 
               cout << "---------------------------------------------" << endl;
             }
          }
          index++; 
        } // else
      } // else
    } // while
  } // else
  // ������
}

int main() {  
  //string keyword[] = { "΢��", "�����", "����", "�й�"};
  string keyword[] = { "΢��", "�����", "����"};
  string str[] = { 
    "΢��","����","�о�Ժ","����","��","1998","��","��","����","��","ʹ��",
    "��","ʹ","δ��","��","�����","�ܹ�","��","��","��","��","ѧ","��",
    "��","��","��Ȼ����","��","����","����","����","��","��","��","����","��",
    "��","΢��","����","�о�Ժ","��","��","�ٽ�","�����","��","��̫","����",
    "��","�ռ�","��","����","��̫","�û�","��","����","����","��","��"
  };
  int len_keyword = sizeof(keyword)/sizeof(string);
  int len_str = sizeof(str)/sizeof(string);
  find_min_len_abstract(str, keyword, len_str, len_keyword);
  
  system("PAUSE");
  return 0;
}
