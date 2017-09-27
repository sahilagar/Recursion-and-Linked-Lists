#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// *You* are not allowed to use global variables
//  but for just the output portion *we* will. ;>
int combo = 1;

// @brief Prints a single combination of teams
//
// @param[in] team1 Array containing the names of team 1
// @param[in] team2 Array containing the names of team 2
// @param[in] len Size of each array
void printSolution(const string* team1, 
		   const string* team2,
		   int len)
{
  cout << "\nCombination " << combo++ << endl;
  cout << "T1: ";
  for(int i=0; i < len; i++){
    cout << team1[i] << " ";
  }
  cout << endl;
  cout << "T2: ";
  for(int i=0; i < len; i++){
    cout << team2[i] << " ";
  }
  cout << endl;
}

// You may add additional functions here
void sort(string* names, int len, string* team1, string* team2, int t1, int t2, int index)
{

  if (t1 == len/2 && t2 == len/2) //if both the teams are full
  {
    printSolution(team1, team2, len/2);
    return;
  }
  else
  {
    if (t1 < len/2) //fill up team 1 first
    {
      team1[t1] = names[index];
      sort(names, len, team1, team2, t1 +1 , t2, index + 1);
    }
    if (t2 < len/2) //then team 2
    {
      team2[t2] = names[index];
      sort(names, len, team1, team2, t1, t2 + 1, index  +1);
    }    
  }
}


int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please provide a file of names" << endl;
    return 1;
  }
  // Complete the rest of main
  ifstream infile(argv[1]);

  int numNames;
  infile >> numNames;
  if (infile.fail()){
    cout << "Error" << endl;
    return 1;
  }

  string* names = new string[numNames]; //putting all the names in an array
  string* team1 = new string[numNames/2];
  string* team2 = new string[numNames/2];
  for (int i=0; i < numNames; i++)
  {
    string temp;
    infile >> temp;
    if (infile.fail())
    {
      cout << "Error " << endl;
      return 1;
    }

    names[i] = temp;
  }

  sort(names, numNames, team1, team2, 0, 0, 0);

  //deletion code
  delete[] names;
  delete[] team1;
  delete[] team2;
  return 0;
}
