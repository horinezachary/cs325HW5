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
    }
    else if (wnum < V){  //wrestler names
    }
    else if (wnum == V){//number of rivalries
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
