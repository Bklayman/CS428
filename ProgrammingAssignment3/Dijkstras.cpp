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

vector<int> calcDistances(vector<vector<int>> data, int index){
  vector<int> result;

  return result;
}

void printNodeTable(vector<vector<string>> nodeTable){
  for(int i = 0; i < nodeTable.size(); i++){
    for(int j = 0; j < nodeTable[i].size(); j++){
      while(nodeTable[i][j].size() < 9){
        nodeTable[i][j] = nodeTable[i][j] + " ";
      }
      cout << nodeTable[i][j] << " ";
    }
    cout << endl;
  }
}

void calcNodeTable(vector<vector<int>> data, int index){
  if(index < 0 || index >= data.size()){
    cout << "Error: Invalid node index" << endl;
    exit(1);
  }

  //Initializes result table
  vector<vector<string>> result;
  vector<string> labels;
  labels.push_back("step");
  labels.push_back("N'");
  for(int i = 0; i < data[index].size(); i++){
    labels.push_back("D(" + to_string(i) + ")");
  }
  result.push_back(labels);

  //Initializes each line in the result table
  for(int i = 0; i < data.size(); i++){
    vector<string> curLine;
    curLine.push_back(to_string(i));
    curLine.push_back("");
    for(int j = 0; j < data.size(); j++){
      curLine.push_back("");
    }
    result.push_back(curLine);
  }

  //Initializes distances for each node and node distance is calculated from for each node
  vector<int> distances = data[index];
  vector<string> foundFrom;
  for(int i = 0; i < distances.size(); i++){
    if(distances[i] == 999){
      foundFrom.push_back("");
    } else {
      foundFrom.push_back(to_string(index));
    }
  }

  //Runs for data.size() steps
  for(int i = 0; i < data.size(); i++){
    int nextMin = -1;
    int minDistance = -1;
    result[i + 1][0] = to_string(i);

    //Gets the closest un-traversed node and the distance of that node
    for(int j = 0; j < data.size(); j++){
      if(distances[j] != -1 && distances[j] != 999 && (nextMin == -1 || (minDistance != -1 && minDistance > distances[j]))){
        nextMin = j;
        minDistance = distances[j];
      }
    }

    //Updates the distance vector and N' for the current line of the result table
    if(i == 0){
      result[i + 1][1] = to_string(nextMin);
    } else {
      result[i + 1][1] = result[i][1] + to_string(nextMin);
    }
    distances[nextMin] = -1;

    for(int j = 0; j < data.size(); j++){
      if(data[nextMin][j] != 999){
        if(distances[j] != -1 && distances[j] > minDistance + data[nextMin][j]){
          distances[j] = minDistance + data[nextMin][j];
          foundFrom[j] = to_string(nextMin);
        }
      }
      if(distances[j] != -1){
        if(distances[j] == 999){
          result[i+1][j+2] = "N/A";
        } else {
          result[i + 1][j + 2] = to_string(distances[j]) + "," + foundFrom[j];
        }
      }
    }

  }

  printNodeTable(result);

}

//Prints the results within the input vector with each element taking exactly 4 characters
void printResults(vector<vector<int>> results){
  for(int i = 0; i < results.size(); i++){
    for(int j = 0; j < results[i].size(); j++){
      cout << results[i][j];
      while(results[i][j] < 1000){
        cout << " ";
        results[i][j]*= 10;
      }
    }
    cout << endl;
  }
}

int main(int argc, char** argv){
  //Make sure that input has the correct number of values, give error otherwise
  if(argc != 2 && argc != 3){
    cout << "Usage: ./Dijkstras [Input File] [Optional Node Number]" << endl;
    exit(1);
  }

  vector<vector<int>> data = getData(argv[1]);

  if(argc == 2){
    //If no node specified, print entire table, giving distances for all nodes
    vector<vector<int>> result;
    for(int i = 0; i < data.size(); i++){
      result.push_back(calcDistances(data, i));
    }
    printResults(result);
  } else {
    //If a node is specified, show that node's table
    int chosenNode = -1;
    try{
      chosenNode = stoi(argv[2]);
    } catch(exception& e){
      cout << "Error: Chosen node is not an integer" << endl;
      exit(1);
    }
    calcNodeTable(data, chosenNode);
  }

}
