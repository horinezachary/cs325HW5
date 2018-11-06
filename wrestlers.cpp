#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <stdlib.h>
#include <cmath>
#include <vector>

using namespace std;

const int NONE = 0;
const int HEEL = 1;
const int BABY = 2;

struct Wrestler {
  int id;
  vector<int> adj;
  string name;
  int team;
  int length;
  bool visited;
};

vector<Wrestler> BreadthFirstSearch(vector<Wrestler> wrestlers, int W, int start);
vector<Wrestler> sortTeams(vector<Wrestler> wrestlers, int W);
bool checkTeams(vector<Wrestler> wrestlers, int W, vector<int> rivA, vector<int> rivB);
string removeNonLetters(string str);

int main(){
  string filename;
  cout << "Plese enter the file you would like to load: ";
  cin >> filename;

  ifstream inFile;  //set up the file reader and attempt to read the file
  inFile.open(filename);
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
  vector<int> rivA;
  vector<int> rivB;

  int linecount = 1;
  string fileout = "";
  while(getline(inFile,line)){ //gets one line
    linecount++;
    stringstream lineStream(line);
    string cell;
    vector<string> parsedRow;
    while(getline(lineStream,cell,' ')){  //parses line and puts numbers into string vector
      parsedRow.push_back(cell);
    }
    if (firstCaseLine){  //number of wrestlers
      W = stoi(parsedRow.at(0));
      firstCaseLine = false;
      wnum = 0;
    }
    else if (wnum < W){  //wrestler names and set up struct
      Wrestler temp;
      temp.id = wnum;
      temp.name = removeNonLetters(parsedRow.at(0));
      temp.team = NONE;
      temp.length = 0;
      temp.visited = false;
      wrestlers.push_back(temp);
      wnum++;
    }
    else if (wnum == W){//number of rivalries
      wnum++;
      R = stoi(parsedRow.at(0));
      rnum = 0;
    }
    else if (rnum < R) {  //read in rivalries, set them in each of the wrestler structs
      string x = removeNonLetters(parsedRow.at(0));
      string y = removeNonLetters(parsedRow.at(1));
      int wx;
      int wy;
      for (int i = 0; i < W; i++){
        if (wrestlers.at(i).name.compare(x) == 0){wx = i;}
        if (wrestlers.at(i).name.compare(y) == 0){wy = i;}
      }
      rivA.push_back(wx); //save the lists for later
      rivB.push_back(wy);
      wrestlers.at(wx).adj.push_back(wy);
      wrestlers.at(wy).adj.push_back(wx);
      rnum++;
    }
  }

  wrestlers = BreadthFirstSearch(wrestlers, W, 0);
  wrestlers = sortTeams(wrestlers, W);

  if (checkTeams(wrestlers, W, rivA, rivB)){ //the check has passed, print out the teams
      fileout.append("Possible: YES");
      string bstr = "\nBABYFACES:";
      string hstr = "\nHEELS:";
      for (int i = 0; i < W; i++){
        if (wrestlers.at(i).team == BABY){
          bstr.append(" ");
          bstr.append(wrestlers.at(i).name);
        }
        else if (wrestlers.at(i).team == HEEL){
          hstr.append(" ");
          hstr.append(wrestlers.at(i).name);
        }
      }
      fileout.append(bstr);
      fileout.append(hstr);
  }
  else {fileout.append("\nPossible: NO");}  //the check did not pass, print out not possible
  cout << fileout << endl;

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
  queue.push_back(start); //add first value to the queue
  wrestlers.at(start).length = 1;

  while(!queue.empty()) { //work through all of the rivalries of the current wrestler becore going deeper.
    int currentindex = queue.front();
    queue.erase(queue.begin()); //pop the top index off of the stack
    Wrestler current = wrestlers.at(currentindex);

    for (int i = 0; i < current.adj.size(); i++) {  //check if the rival has already been visited, otherwise add to the stack
      int test = current.adj.at(i);
      if (wrestlers.at(test).visited == false) {
        wrestlers.at(test).visited = true;
        queue.push_back(test);
        wrestlers.at(test).length = current.length+1; //add length to the rival
      }
    }
  }
  return wrestlers;
}

vector<Wrestler> sortTeams(vector<Wrestler> wrestlers, int W){
  for (int i = 0; i < W; i++) {
    if (wrestlers.at(i).visited == false){  //reruns the BFS for chains of wrestlers that were not connected to the main chain
      wrestlers = BreadthFirstSearch(wrestlers, W, i);
    }
    if (wrestlers.at(i).length != 0){
      wrestlers.at(i).team = (wrestlers.at(i).length % 2) +1; //Gives 1 if the length is even, and 2 if the length is odd
    }
    else {  //no rivalry for this wrestler, so add them to the first team.
      wrestlers.at(i).team = BABY;
    }
  }
  return wrestlers;
}

bool checkTeams(vector<Wrestler> wrestlers, int W, vector<int> rivA, vector<int> rivB){ //checks wether the teams are valid
  for (int i = 0; i < rivA.size(); i++){
    //cout << wrestlers.at(rivA.at(i)).team << " " << wrestlers.at(rivB.at(i)).team << endl;
    if (wrestlers.at(rivA.at(i)).team == wrestlers.at(rivB.at(i)).team){
      return false; //teams are not valid
    }
  }
  return true;  //teams are valid
}

string removeNonLetters(string str) { //ensures that theere aren't carriage returns on the end of the strings coming in
  while (str.back() == '\n' || str.back() == '\r'){
    str.pop_back();
  }
  return str;
}
