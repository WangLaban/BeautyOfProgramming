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
  
  Dict key_idx;          //关键字映射为数字，以减少字符串比较            
  for (size_t i = 0; i < keyword_sz; ++i) {
    //key_idx.insert(Dict::value_type(&keyword[i], i)); //----
    key_idx.insert(Dict::value_type(keyword[i], i)); 
  }
  const size_t Pos_init = -1;
  vector<size_t> prev_pos(keyword_sz, Pos_init); //上次碰到的关键字符串的位置
  std::set<size_t> pos;        //对关键字符串的位置进行升序排列
  
  vector<size_t> old_pos;      //分词后的字符串，在原字符串中的位置 
  old_pos.reserve(str_sz + 1);
  old_pos.push_back(0);
  for (size_t i = 0, sum = 0; i < str_sz; ++i) {
    sum += str[i].size();
    old_pos.push_back(sum);
  }
   
  size_t beg = 0, end = 0, len = -1, count = 0;  //记录结果，注意len的类型 
  for (size_t i = 0; i < str_sz; ++i) {
    //Dict::iterator it = key_idx.find(&str[i]); //----
    Dict::iterator it = key_idx.find(str[i]);

    if (it == key_idx.end()) continue;
    
    assert(it->second < prev_pos.size());
    size_t& last_pos = prev_pos[it->second];
    if (last_pos != Pos_init)  pos.erase(last_pos); //更新前要先删除旧的
    else ++count;  //已匹配关键字 数加1
    last_pos = i;
    
    pos.insert(pos.end(), i); 
    
    assert(count <= keyword_sz);
    if (count == keyword_sz) {     //包含所有关键字
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
  
  if (beg == end && !pos.empty()) {      //没找到所有关键字
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
  string keyword[] = { "微软", "计算机", "亚洲", "中国"};
  string str[] = { 
    "微软","亚洲","研究院","成立","于","1998","年","，","我们","的","使命",
    "是","使","未来","的","计算机","能够","看","、","听","、","学","，",
    "能","用","自然语言","与","人类","进行","交流","。","在","此","基础","上",
    "，","微软","亚洲","研究院","还","将","促进","计算机","在","亚太","地区",
    "的","普及","，","改善","亚太","用户","的","计算","体验","。","”"
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
// 初始化map 
  map<string,int> record;
  for(int i=0; i<len_keyword; i++) {
    record[keyword[i]] = 0;
  }
  // 匹配过程
  deque<int> store; // 存储的是str中关键词的下标 
  int min_len = 0;
  int min_index_first = -1;
  int min_index_last = -1;
  int find_key_num = 0;
  int index = 0;
  while(find_key_num < len_keyword && index < len_str) {
    if(record.find(str[index]) == record.end()) { // str[index]不是关键字 
       index++;
    }
    else { // str[index]是关键字 
      if(record[str[index]] == 0) // 第一次找到这个关键字
        find_key_num ++;
      record[str[index]] = record[str[index]] + 1; // 计数加1
      store.push_back(index); 
      index++;
    }
  }
  if(find_key_num < len_keyword) { // 一个满足的摘要都没找到 
    cout << "abstract not found " << endl;
  }
  else { // 找到一个了，试着找找更好的 
    min_len = store.back()- store.front() + 1;   
    min_index_first = store.front();
    min_index_last = store.back();
    // 第一个摘要 
    cout << "第一个摘要" << endl; 
    cout << "min len: " << min_len << endl;
    for(int i=min_index_first; i<=min_index_last; i++)
      cout << str[i] << " ";
    cout << endl; 
    cout << "---------------------------------------------" << endl;
    string need_key;
    bool already_found = true;
    while(true) {   
      if(already_found == true) { // 刚好找到一个新摘要 
        string first_key = str[store.front()];
        record[first_key]--; // 减少当前最前面的关键词 
        store.pop_front(); // 关键词出队 
        if(record[first_key] == 0) { // 如果该关键词没了 
          already_found = false;
          need_key = first_key; // 记录需要寻找的关键词 
        }               
        else { // 少了词语，但是还包含所有关键词，说明这是一个更短的摘要 
          min_len--;
          min_index_first ++;
          cout << "更短的摘要" << endl;
          cout << "min len: " << min_len << endl;
          for(int i=min_index_first; i<=min_index_last; i++)
            cout << str[i] << " ";
          cout << endl; 
          cout << "---------------------------------------------" << endl;
        }
      }
      else { // 需要向后面找满足条件的关键词 
        if(index >= len_str) { // 不可能找到需要的关键词了 
          break;
        }
        else if(record.find(str[index]) == record.end()) { // 不是关键词 
          index++;
        }
        else { // 是关键词 
          record[str[index]] = record[str[index]]+1;
          store.push_back(index); 
          if(str[index] == need_key) { // 正好还是需要找到的关键词
             already_found = true;
             if((store.back()-store.front() + 1) < min_len) { // 新的摘要更短 
               min_len = store.back() - store.front() + 1;
               min_index_first = store.front();
               min_index_last = store.back();
               // 更短的摘要
               cout << "更短的摘要" << endl;
               cout << "min len: " << min_len << endl;
               for(int i=min_index_first; i<=min_index_last; i++)
                 cout << str[i] << " ";
               cout << endl; 
               cout << "---------------------------------------------" << endl;
             }
             else {
               cout << "并非更短的摘要" << endl;
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
  // 输出结果
}

int main() {  
  //string keyword[] = { "微软", "计算机", "亚洲", "中国"};
  string keyword[] = { "微软", "计算机", "亚洲"};
  string str[] = { 
    "微软","亚洲","研究院","成立","于","1998","年","，","我们","的","使命",
    "是","使","未来","的","计算机","能够","看","、","听","、","学","，",
    "能","用","自然语言","与","人类","进行","交流","。","在","此","基础","上",
    "，","微软","亚洲","研究院","还","将","促进","计算机","在","亚太","地区",
    "的","普及","，","改善","亚太","用户","的","计算","体验","。","”"
  };
  int len_keyword = sizeof(keyword)/sizeof(string);
  int len_str = sizeof(str)/sizeof(string);
  find_min_len_abstract(str, keyword, len_str, len_keyword);
  
  system("PAUSE");
  return 0;
}
