//Victor Manuel Rojas Trejos 
// Minesweeper
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <utility> 
using namespace std;
// Maximum size of a row or column
#define MAXN 200

// Opens the file and returns the ifstream
ifstream OpenInputFile(const string& fileName) 
{
    ifstream file(fileName);
    // Flag for problems opening the file
    int fileError = 1;
    
    if (!file.is_open()) 
    {
        cerr << "Error: Could not open file " << fileName << endl;
        exit(fileError);
    }
    return file;
}// end OpenInputFile

// Reads board dimensions from an open file and validates them
pair<int, int> ReadDimensions(ifstream &inputFile) 
{
    int rowCount, columnCount;
    inputFile >> rowCount >> columnCount;
    
    // Flag for error in the dimensions
    int dimensionsError = 2;

    // Validate dimensions range
    if ((rowCount < 1) || (columnCount < 1) || 
        (rowCount > MAXN) || (columnCount > MAXN)) 
    {
        cerr << "Error: Rows and columns must be between 1 and " << MAXN << "." << endl;
        exit(dimensionsError);
    }
    return pair<int, int>(rowCount, columnCount);
}// end ReadDimensions

// Reads the board cell values from an open file and validates them
vector<vector<int>> ReadBoardCells(ifstream &inputFile, int rowCount, int columnCount) 
{
    vector<vector<int>> mineBoard(rowCount, vector<int>(columnCount));

    // Flags for error in the cell value
    int cellError = 3;
    
    // Read cell values and validate
    for (int row = 0; row < rowCount; row++) 
    {
        for (int column = 0; column < columnCount; column++) 
        {
            int cellValue;
            if (!(inputFile >> cellValue) || (cellValue != 0 && cellValue != 1)) 
            {
                cerr << "Error: The file must contain only 0 or 1." << endl;
                exit(cellError);
            }
            mineBoard[row][column] = cellValue;
        }
    }
    return mineBoard;
}// end ReadBoardCells

// Reads the complete board from a file
vector<vector<int>> ReadBoardFromFile(const string &fileName) 
{
    ifstream inputFile = OpenInputFile(fileName);
    
    pair<int, int> dims = ReadDimensions(inputFile);
    
    int rowCount = dims.first;
    int columnCount = dims.second;
    
    return ReadBoardCells(inputFile, rowCount, columnCount);
}// end ReadBoardFromFile

// Prints the board as integers
void PrintBoard(const vector<vector<int>> &board) 
{
    for (size_t row = 0; row < board.size(); row++) 
    {
        for (size_t column = 0; column < board[row].size(); column++) 
        {
            cout << board[row][column] << " ";
        }
        cout << "\n";
    }
}// end PrintBoard

// Increments mine count in all neighbor cells (excluding the mine cell itself)
void IncrementNeighbors(vector<vector<int>> &adjacentMinesBoard, int mineRow, int mineColumn) 
{
    int rowCount = static_cast<int>(adjacentMinesBoard.size());
    int columnCount = static_cast<int>(adjacentMinesBoard[0].size());

    // loop through all positions around a cell
    for (int rowOffset = -1; rowOffset <= 1; rowOffset++) 
    {
        for (int columnOffset = -1; columnOffset <= 1; columnOffset++) 
        {
            // Skip the mine cell itself
            if (rowOffset == 0 && columnOffset == 0) 
                continue;

            int neighborRow = mineRow + rowOffset;
            int neighborColumn = mineColumn + columnOffset;

            // Check if the neighbor is inside board limits
            if ((neighborRow >= 0) && (neighborRow < rowCount) && (neighborColumn >= 0) && (neighborColumn < columnCount)) 
            {
                adjacentMinesBoard[neighborRow][neighborColumn]++;
            }
        }
    }
}// end IncrementNeighbors

// Calculates adjacent mine counts (keeps original mine positions as in the previous behavior)
vector<vector<int>> CalculateAdjacentMines(const vector<vector<int>> &mineBoard) 
{
    int rowCount = static_cast<int>(mineBoard.size());
    int columnCount = static_cast<int>(mineBoard[0].size());
    vector<vector<int>> adjacentMinesBoard(rowCount, vector<int>(columnCount, 0));

    for (int row = 0; row < rowCount; row++) 
    {
        for (int column = 0; column < columnCount; column++) 
        {
            if (mineBoard[row][column] == 1) 
            {
                IncrementNeighbors(adjacentMinesBoard, row, column);
            }
        }
    }
    return adjacentMinesBoard;
}// end CalculateAdjacentMines

int main() 
{
    string fileName;
    
    cout << "\tMinesweeper\n";
    cout << "This program simulates the game Minesweeper.\n";
    cout << "It reads a board from a file and calculates adjacent mine counts.\n";
    
    cout << "Enter the file name: ";
    cin >> fileName;

    vector<vector<int>> mineBoard = ReadBoardFromFile(fileName);

    cout << "\nOriginal board:\n";
    PrintBoard(mineBoard);

    vector<vector<int>> adjacentMinesBoard = CalculateAdjacentMines(mineBoard);

    cout << "\nBoard with adjacent mine counts:\n";
    PrintBoard(adjacentMinesBoard);

    return 0;
}
