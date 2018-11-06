#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <stdlib.h>
#include <cmath>
#include <vector>

using namespace std;

const int NONE = 0;
const int BABY = 1;
const int HEEL = 2;

struct Wrestler {
  int id;
  vector<int> adj;
  string name;
  int team;
  int length;
  bool visited;
};

vector<Wrestler> BreadthFirstSearch(vector<Wrestler> wrestlers, int W, int start);
string removeNonLetters(string str);

int main(){
  ifstream inFile;  //set up the file reader and attempt to read the file
  inFile.open("wrestler.txt");
  if (!inFile) {  //make sure the file exists
    cout << "Unable to open wrestler.txt" << endl;
    exit(1);   // EXIT PROGRAM
  }
  string line;
  bool firstCaseLine = true;

  vector<Wrestler> wrestlers;
  int W;
  int wnum;
  int R;
  int rnum;
  int linecount = 1;
  string fileout = "";
  while(getline(inFile,line)){ //gets one line
    linecount++;
    stringstream lineStream(line);
    string cell;
    vector<string> parsedRow;
    while(getline(lineStream,cell,' ')){  //parses line and puts numbers into string vector
      parsedRow.push_back(cell);
      //cout << cell;
    }
    if (firstCaseLine){  //number of wrestlers
      W = stoi(parsedRow.at(0));
      cout << W << endl;
      firstCaseLine = false;
      wnum = 0;
    }
    else if (wnum < W){  //wrestler names
      Wrestler temp;
      temp.id = wnum;
      temp.name = removeNonLetters(parsedRow.at(0));
      cout << temp.id << " " << temp.name << endl;
      temp.team = NONE;
      temp.length = 0;
      temp.visited = false;
      wrestlers.push_back(temp);
      wnum++;
    }
    else if (wnum == W){//number of rivalries
      wnum++;
      R = stoi(parsedRow.at(0));
      cout << R << endl;
      rnum = 0;
    }
    else if (rnum < R) {
      string x = removeNonLetters(parsedRow.at(0));
      string y = removeNonLetters(parsedRow.at(1));
      cout <<"---"<< x.at(0) << " " << y.at(0) << endl;
      int wx;
      int wy;
      for (int i = 0; i < W; i++){
        cout << i << " " << wrestlers.at(i).name;
        //printf("%d\n", wrestlers.at(i).name.at(1));
        if (wrestlers.at(i).name.compare(x) == 0){
          wx = i;
          cout <<" "<< wx;
        }
        if (wrestlers.at(i).name.compare(y) == 0){
          wy = i;
          cout <<" "<< wy;
        }
        cout << endl;
      }
      wrestlers.at(wx).adj.push_back(wrestlers.at(wy).id);
      wrestlers.at(wy).adj.push_back(wrestlers.at(wx).id);
      rnum++;
    }
  }

  wrestlers = BreadthFirstSearch(wrestlers, W, 0);

  cout << fileout;

  //Write string to file
  ofstream outfile;
  outfile.open("wrestlers.out");
  if (!outfile) {  //make sure the file exists
    cout << "Unable to open wrestlers.out";
    exit(1);   // EXIT PROGRAM
  }
  outfile << fileout;
  outfile.close();

}

vector<Wrestler> BreadthFirstSearch(vector<Wrestler> wrestlers, int W, int start){
  vector<int> queue;
  wrestlers.at(start).visited = true;
  queue.push_back(start);
  wrestlers.at(start).length = 1;

  while(!queue.empty()) {
    int currentindex = queue.front();
    cout << currentindex << " ";
    queue.erase(queue.begin());
    Wrestler current = wrestlers.at(currentindex);

    for (int i = 0; i < current.adj.size(); i++) {
      int test = current.adj.at(i);
      if (wrestlers.at(test).visited == false) {
        wrestlers.at(test).visited = true;
        queue.push_back(test);
        wrestlers.at(test).length = current.length+1;
      }
    }
  }
  return wrestlers;
}



string removeNonLetters(string str) {
  while (str.back() == '\n' || str.back() == '\r'){
    str.pop_back();
  }
  return str;
}
