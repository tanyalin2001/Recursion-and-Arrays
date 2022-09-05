#include <iostream>
#include <fstream>
#include "ArgumentManager.h"
#include <vector>
#include <algorithm>
#include <string>
using namespace std;    

void search(const vector<string> &list,int l, int r, string storedcommand, int level, ofstream &out) {
  int mid = (r+l)/2;
  if (r == l){
    vector<string> newlist;
    for(int i=0; i<list.size(); i++){
      newlist.push_back(list.at(l));
    }
    transform(newlist.at(l).begin(), newlist.at(l).end(), newlist.at(l).begin(), ::toupper);
    transform(storedcommand.begin(), storedcommand.end(), storedcommand.begin(), ::toupper);  
    if(newlist.at(l).find(storedcommand) != string::npos){   
      cout << "Level " << level << ": " << list.at(l) << endl;
      out << "Level " << level << ": " << list.at(l) << endl;
    }
  }
  else if((r-l) > 0){  
    search(list,l,mid,storedcommand,level+1, out);
    search(list,mid+1,r,storedcommand,level+1, out);
  }
}

void split(string s, vector<string> &v){
	string temp = "";
	for(int i=0;i<s.length();++i){	
		if(s[i] == ' '){
			v.push_back(temp);
			temp = "";
		}
		else{
			temp.push_back(s[i]);
		}		
	}

	v.push_back(temp);
}

void replace(string& s,string const& toReplace,string const& replaceWith) {
  ostringstream oss;
  size_t pos = 0;
  size_t prevPos = pos;

  while (true) {
    prevPos = pos;
    pos = s.find(toReplace, pos);
    if (pos == string::npos)
      break;
    oss << s.substr(prevPos, pos - prevPos);
    oss << replaceWith;
    pos += toReplace.size();
  }

  oss << s.substr(prevPos);
  s = oss.str();
}

int main(int argc, char* argv[]){
  ArgumentManager am(argc, argv);
  string infile = am.get("input");
  string outfile = am.get("output");
  string incommand = (am.get("command"));
  ifstream input(infile);
  ifstream command(incommand);
  ofstream output(outfile);
  
  vector<string> data;
  string line;
  vector<string> lines;
  string storedcommand;
  string newline;

  if(input.is_open()){
    while(getline(input,line)){
      line.erase(remove_if(line.begin(), line.end(), (int(*)(int))iscntrl), line.end());
      newline += line;
    }
  }

  newline.erase(remove(newline.begin(), newline.end(), ' '), newline.end());
  replace(newline, "},{", "} {");
  split(newline, data);

  getline(command, storedcommand);
  if(storedcommand != "")
    search(data,0,data.size()-1,storedcommand,0, output);
  return 0;
}
