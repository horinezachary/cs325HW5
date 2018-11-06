#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <stdlib.h>
#include <cmath>
#include <vector>

using namespace std;

struct Wrestler {
  int id;
  vector<int> adj;
  string name;
};
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
  int V;
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
      V = stoi(parsedRow.at(0));
      cout << V << endl;
      firstCaseLine = false;
      wnum = 0;
    }
    else if (wnum < V){  //wrestler names
      Wrestler temp;
      temp.id = wnum;
      temp.name = removeNonLetters(parsedRow.at(0));
      cout << temp.id << " " << temp.name << endl;
      wrestlers.push_back(temp);
      wnum++;
    }
    else if (wnum == V){//number of rivalries
      wnum++;
      R = stoi(parsedRow.at(0));
      cout << R << endl;
      rnum = 0;
    }
    else if (rnum < R) {
    }

  }
  cout << fileout;

  //Write string to file
  ofstream outfile;
  outfile.open("act.out");
  if (!outfile) {  //make sure the file exists
    cout << "Unable to open act.out";
    exit(1);   // EXIT PROGRAM
  }
  outfile << fileout;
  outfile.close();

}
