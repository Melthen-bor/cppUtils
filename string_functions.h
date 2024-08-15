#ifndef STRING_FUNCTIONS_LOADED
#define STRING_FUNCTIONS_LOADED
#include <string>
#include <vector>
vector<string> split(string& text,char delimiter){
	vector<string> out;
	unsigned count = 0;
	string temp = "";
	while (count < text.size()) {
		if (text[count] == delimiter) {
			out.push_back(temp);
			temp.clear();
		}
		else {
			temp.push_back(text[count]);
		}
		count++;
	}
  return out;
}
string join(vector<string>& list,char with){
  string out=list.at(0);
  unsigned count=1;
  while(count<list.size()){
    out.push_back(with);
    out+=list.at(count);
    count++;
  }
  return out;
}
#ifdef UNICODE_STRING
typedef basic_string<wchar_t> ustring;
vector<ustring> split(ustring& text,wchar_t delimiter){
  vector<ustring> out;
  unsigned count=0;
  ustring temp;
  while(count<text.size()){
    if(text[count]==delimiter){
      out.push_back(temp);
      temp.clear();
    } else{
      temp.push_back(text[count]);
    }
    count++;
  }
  return out;
}
ustring join(vector<ustring>& list,wchar_t with){
  ustring out=list.at(0);
  unsigned count=1;
  while(count<list.size()){
    out.push_back(with);
    out+=list.at(count);
    count++;
  }
  return out;
}
#endif
#endif
