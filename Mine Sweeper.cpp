//Victor Manuel Rojas Trejos 
//minesweeper
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <utility> 
using namespace std;

pair<int, int> ReadDimensions(ifstream &inputFile) 
{
    int rowCount, columnCount;
    inputFile >> rowCount >> columnCount;

    if (rowCount < 1 || columnCount < 1 || rowCount > 200 || columnCount > 200) 
    {
        cerr << "Error: Rows and columnumns must be between 1 and 200." << endl;
        exit(1);
    }
    return {rowCount, columnCount};
}

vector<vector<int>> ReadBoardFromFile(const string &fileName) 
{
    ifstream inputFile(fileName);
    if (!inputFile.is_open()) 
    {
        cerr << "Error: Could not open file " << fileName << endl;
        exit(1);
    }

    pair<int,int> dims = ReadDimensions(inputFile);
    int rowCount = dims.first;
    int columnCount = dims.second;

    vector<vector<int>> mineBoard(rowCount, vector<int>(columnCount));

    for (int row = 0; row < rowCount; row++) 
    {
        for (int column = 0; column < columnCount; column++) 
        {
            int cellValue;
            if (!(inputFile >> cellValue) || (cellValue != 0 && cellValue != 1)) 
            {
                cerr << "Error: The file must contain only 0 or 1." << endl;
                exit(1);
            }
            mineBoard[row][column] = cellValue;
        }
    }
    return mineBoard;
}

// Prints the board
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
}

void IncrementNeighbors(vector<vector<int>> &adjacentMinesBoard, int mineRow, int minecolumn) 
{
    int rowCount = static_cast<int>(adjacentMinesBoard.size());
    int columnCount = static_cast<int>(adjacentMinesBoard[0].size());

    for(int rowOffset = -1; rowOffset <= 1; rowOffset++) 
    {
        for(int columnOffset = -1; columnOffset <= 1; columnOffset++) 
        {
            int neighborRow = mineRow + rowOffset;
            int neighborcolumn = minecolumn + columnOffset;
            if((neighborRow >= 0) && (neighborRow < rowCount) && (neighborcolumn >= 0) && (neighborcolumn < columnCount)) 
            {
                adjacentMinesBoard[neighborRow][neighborcolumn]++;
            }
        }
    }
}

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
}

int main() 
{
    string fileName;
    
    cout << "\tMinesweeper\n";
    cout << "This program simule the game MineSweeper\n";
    cout << "Reads a board from a file and calculates the number of adjacent mines.\n";
    
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
