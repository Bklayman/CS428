#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Read and format data from given input file
vector<vector<int>> getData(char* fileName){
  vector<vector<int>> result;
  ifstream file;
  string line;
  file.open(fileName);

  //Check if file is open, give error otherwise
  if(!file.is_open()){
    cout << "Error opening file: " << fileName << endl;
    exit(1);
  }

  int numNodes = 0;

  //Make sure that first line of file is a number, give error otherwise
  getline(file, line);
  try{
    numNodes = stoi(line);
  } catch(exception& e){
    cout << "Error: First line of input file is not a number" << endl;
    exit(1);
  }

  //Iterate through each line of the input data
  for(int i = 0; i < numNodes; i++){
    getline(file, line);
    vector<int> curNode;

    //Iterate through each number in current input line
    for(int j = 0; j < numNodes; j++){
      string curDistance = line.substr(0, line.find(" "));
      line.erase(0, line.find(" ") + 1);

      //Try to turn each distance value to an int, gives error otherwise
      int curDistanceNum = -1;
      try{
        curDistanceNum = stoi(curDistance);
      } catch(exception& e){
        cout << "Error: Distance matrix value is not a number" << endl;
        exit(1);
      }

      curNode.push_back(curDistanceNum);
    }

    result.push_back(curNode);
  }

  return result;
}

int main(int argc, char** argv){
  //Make sure that input has the correct number of values, give error otherwise
  if(argc != 2){
    cout << "Usage: ./Dijkstras [Input File]" << endl;
    exit(1);
  }

  vector<vector<int>> data = getData(argv[1]);

  
}
