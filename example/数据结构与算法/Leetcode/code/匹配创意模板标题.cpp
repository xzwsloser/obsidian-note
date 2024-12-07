#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> get_templates(string& template_);
bool has_prefix(string& template_);
bool has_lastfix(string& template_);
bool match_title(vector<string>& templates , string& titles , bool& prefix , bool& suffix);  // 匹配标题

std::string solution(int n, std::string template_,
                     std::vector<std::string> titles) {
  // Please write your code here
  vector<string> templates = get_templates(template_);
  for(auto& ch : templates) cout << ch << " " ;
  cout << endl;
  bool prefix = has_prefix(template_);
  bool suffix = has_lastfix(template_);

  vector<string> result;
  for(int i = 0 ; i < titles.size() ; i ++) {
    if(match_title(templates, titles[i], prefix, suffix)) {
        result.push_back("True");
    } else {
        result.push_back("False");
    }
  }
  
  // 开始匹配
  
  string res;
  for(int i = 0 ; i < result.size() - 1 ; i ++) {
    res += result[i];
    res += ",";
  }
  res += result.back();
  return res;
}

vector<string> get_templates(string& template_) {
  // 首先可以提取模板字符串中的字符
  vector<string> templates;
  string str;
  for(int i = 0 ; i < template_.size() ; i ++) {
    if(str.empty()) {
        str.push_back(template_[i]);
    } else {
        if(str.back() == '{' && template_[i] == '}') {
            str.pop_back();
            templates.push_back(str);
            str.clear();
        } else if(str.back() == '{') {
            continue;
        } else {
            str.push_back(template_[i]);
        }
    }
  }
  templates.push_back(str);
  return templates;
}

bool has_prefix(string& template_) {
    return template_[0] == '{';
}

bool has_lastfix(string& template_) {
    return template_.back() == '}';
}

bool match_title(vector<string>& templates , string& titles , bool& prefix , bool& suffix) {
    int start = 0;
    for(int index = 0 ; index < templates.size() ; index ++) {
        int pos = 0;
        if(index == 0 && !prefix) {
            pos = titles.find(templates[index]);
            if(pos != 0) {
                return false;
            } else {
                start = pos + templates[index].size();
            }
        } else if(index == templates.size() - 1 && !suffix) {
            pos = titles.rfind(templates[index]);
            if(pos < start) return false;
            if(pos == string::npos || pos + templates[index].size() != titles.size()) {
                return false;
            }
        } else {
            pos = titles.find(templates[index] , start);
            if(pos == string::npos) {
                return false;
            } else {
                start = pos + templates[index].size();
            }
        }
    }
    return true;
}

int main() {
  //  You can add more test cases here
  std::vector<std::string> testTitles1 = {"adcdcefdfeffe", "adcdcefdfeff",
                                          "dcdcefdfeffe", "adcdcfe"};
  std::vector<std::string> testTitles2 = {
      "CLSomGhcQNvFuzENTAMLCqxBdj", "CLSomNvFuXTASzENTAMLCqxBdj",
      "CLSomFuXTASzExBdj",          "CLSoQNvFuMLCqxBdj",
      "SovFuXTASzENTAMLCq",         "mGhcQNvFuXTASzENTAMLCqx"};
  std::vector<std::string> testTitles3 = {"abcdefg", "abefg", "efg"};

  std::cout << (solution(4, "ad{xyz}cdc{y}f{x}e", testTitles1) ==
                "True,False,False,True")
            << std::endl;
  std::cout << (solution(4, "ad{xyz}cdc{y}f{x}e", testTitles1)) << std::endl;
  std::cout << (solution(6, "{xxx}h{cQ}N{vF}u{XTA}S{NTA}MLCq{yyy}",
                         testTitles2) == "False,False,False,False,False,True")
            << std::endl;
  std::cout << (solution(3, "a{bdc}efg", testTitles3) == "True,True,False")
            << std::endl;

  return 0;
}