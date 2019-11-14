#include"Scoreboard.h"

vector<string> Scoreboard::readFromFile()
{
    ifstream myReadFile;
    myReadFile.open("scores.txt");
    vector<string> output;
    string tmp;
    if (myReadFile.is_open())
    {
        while (!myReadFile.eof())
        {
            myReadFile >> tmp;
            output.push_back(tmp);
        }
    }
myReadFile.close();
return output;
}

 Scoreboard::Scoreboard(){
    vector<string> input=readFromFile();
    for(unsigned i=0;i<10;i++){
        push_back(atoi(input[i].c_str()));
    }
    sort();
}

void Scoreboard::addScore(int score){
  ofstream myfile ("scores.txt");
  if (myfile.is_open())
  {
    myfile <<score <<"\n";
    myfile.close();
  }
  else cout << "Unable to open file";
}

void Scoreboard::showScoreboard(){
list<int>::const_iterator it=begin();
int i=0;
while(i<10){
    cout<<*it<<endl;
    it++;
    i++;    
}
}