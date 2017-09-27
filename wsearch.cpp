#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Location
{
  Location()
  {
    row = -1;
    col = -1;
  }
  Location(int r, int c)
  {
    row = r;
    col = c;
  }
  int row;
  int col;
};

// @param[in] instream - Input (file) stream for the input file.  Opened in main()
// @param[out] grid Blank vector of vectors.  Should be updated with the
//                  contents of the grid from the input file
// @return true if successful, false otherwise (see HW writeup for details
//         about possible error cases to be checked)
bool readGrid(istream& instream, vector<vector<char> >& grid )
{
  /** You complete **/
	vector<char> oneLine;
	string myLine;
	bool sizeCheck = false;
	int sizeOfRow;

	//read the file in
	while (getline(instream, myLine))
	{
		stringstream ss(myLine);
		char inputChar;
		while (ss >> inputChar){
			oneLine.push_back(inputChar);
		}
		grid.push_back(oneLine);
		if (sizeCheck == false) //setting the size
		{
			sizeCheck = true;
			sizeOfRow = oneLine.size();
		}
		if (sizeCheck == true)
		{
			if ((unsigned int)sizeOfRow != oneLine.size()) //checks if all the rows are the same size
				return false;
		}
		oneLine.clear();
	}


	if (grid.size() < 1) //if there is not one character
		return false;

	return true;

}

// prototype - will be implemented below
bool findWordHelper(
   const vector<vector<char> >& grid, 
   Location currLoc,
   Location delta,
   string word,
   unsigned int currWordIndex);

// Do not change
void printSolution(const string& targetWord, const Location& start, string direction)
{
  cout << targetWord << " starts at (row,col) = (" << start.row << "," << start.col
       << ") and proceeds " << direction << "." << endl;
}

// Do not change
void printNoSolution(const string& targetWord)
{
  cout << targetWord << " does NOT occur." << endl;
}

// Complete - you should not need to change this.
void findWord(const vector<vector<char> >& grid, 
	      const string& targetWord)
{
  bool found = false;
  if(targetWord.size() < 2){
    cout << "Need a word of length 2 or more." << endl;
	return;
  }
  for(unsigned int r=0; r < grid.size(); r++){ //iterates through the list
	    for(unsigned int c=0; c < grid[r].size(); c++){
		      if(grid[r][c] == targetWord[0]){ //if grid equals first character
				Location loc(r,c); //create location with same coordinates
				if( findWordHelper(grid, Location(r-1,c), Location(-1, 0), targetWord, 1) ){
				  printSolution(targetWord, loc, "up");
				  found = true;
				}
				if( findWordHelper(grid, Location(r,c-1), Location(0,-1), targetWord, 1) ){
				  printSolution(targetWord, loc, "left");
				  found = true;
				}
				if( findWordHelper(grid, Location(r+1,c), Location(1, 0), targetWord, 1) ){
				  printSolution(targetWord, loc, "down");
				  found = true;
				}
				if( findWordHelper(grid, Location(r,c+1), Location(0,1), targetWord, 1) ){
				  printSolution(targetWord, loc, "right");
				  found = true;
				}
		      }      
	    }
  }
  if(!found){
    printNoSolution(targetWord);
  }
}

/**
 * @param[in] grid The 2D vector containing the entire search contents
 * @param[in] currLoc Current row and column location to try to match 
 *                    with the next letter
 * @param[in] delta   Indicates direction to move for the next search
 *                    by containing the *change* in row, col values
 *                    (i.e. 1,0 = down since adding 1 will move down 1 row)
 * @param[in] word The word for which you are searching
 * @param[in] currWordIndex The index to word indicating which letter must
 *                          be matched by this call
 */
bool findWordHelper(const vector<vector<char> >& grid, 
		 Location currLoc, //check
		 Location delta, //move for next search
		 string word,
		 unsigned int currWordIndex)
{
  /*** You complete ***/
	//base case
	if (currWordIndex == word.size()) //if the word has been fully traversed
		return true;
	else if (currLoc.row  < 0 ||currLoc.col < 0) //checks the bounds
		return false;
	else if ((unsigned int)currLoc.row >= grid.size() ||(unsigned int)currLoc.col >= grid[0].size())
		return false;
	else if (word[currWordIndex] != grid[currLoc.row][currLoc.col])
		return false;
	else
	{
		currLoc.row += delta.row;
		currLoc.col += delta.col;			
		return findWordHelper(grid, currLoc, delta, word, currWordIndex+1);
	}
}

int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Please provide a grid filename and targetWord" << endl;
    return 1;
  }
  ifstream ifile(argv[1]);
  string targetWord(argv[2]);
  if(ifile.fail()){
    cerr << "Unable to open input grid file" << endl;
    return 1;
  }

  vector<vector<char> > mygrid;
  if( ! readGrid(ifile, mygrid) ){
    cerr << "Error reading grid" << endl;
    ifile.close();
    return 1;
  }

  findWord(mygrid, targetWord);

  return 0;
}
