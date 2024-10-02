//Victor Manuel Rojas Trejos 
//minesweeper
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> EnterMatrix(){
  unsigned int row, column;
  bool valid = false;  
  do{
    cout << "Enter the number of rows: ";
    cin >> row;
    cout << "Enter the number of columns: ";
    cin >> column;

    if((column < 1 || row) < 1 && (column > 200 || row > 200)){
      cout << "The number of rows and columns is vey big, try again\n";
    }
    else{
      valid = true;
    }
  }while(valid != true);
  vector<vector<int>> matrix(row, vector<int>(column));

  for(int i = 0; i < row; i++){
    for(int j = 0; j < column; j++){
      int num;
      cout << "Enter the value of the position [" << i << "][" << j << "]: ";
      cin >> num;
      if(num == 0 || num == 1){
        matrix[i][j] = num;
      }
      else{
        cout << "The value must be 0 or 1, try again\n";
        j--;
      }
    }
  }
  return matrix;
}//end EnterMatrix

void PrintMatrix(vector<vector<int>>& matrix){
  for(int i = 0; i < matrix.size(); i++){
    for(int j = 0; j < matrix[0].size(); j++){
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
}//end PrintMatrix

vector<vector<int>> MinesWanted(vector<vector<int>>& originalMatrix){
  vector<vector<int>> newMatrix(originalMatrix.size(), vector<int>(originalMatrix[0].size()));
  for(int i = 0; i < newMatrix.size(); i++){
    for(int j = 0; j < newMatrix[0].size(); j++){
      newMatrix[i][j] = originalMatrix[i][j];
      if(i > 0){
        newMatrix[i][j] += originalMatrix[i-1][j];
        if(j > 0){
          newMatrix[i][j] += originalMatrix[i-1][j-1];
        }
        if(j < newMatrix[0].size()-1){
          newMatrix[i][j] += originalMatrix[i-1][j+1];
        }
      }

      if(i < newMatrix.size()-1){
        newMatrix[i][j] += originalMatrix[i+1][j];  
        if(j > 0){
          newMatrix[i][j] += originalMatrix[i+1][j-1];
        }
        if(j < newMatrix[0].size()-1){
          newMatrix[i][j] += originalMatrix[i+1][j+1];
        }
      }
      
      if(j > 0){
        newMatrix[i][j] += originalMatrix[i][j-1];
      }
      if(j < newMatrix[0].size()-1){
        newMatrix[i][j] += originalMatrix[i][j+1];
      }
      
    }
  }
  return newMatrix;
}//end MinesWanted

int main(){
  cout << "MineSweeper\n";
  cout << "This program simule the game MineSweeper\n";
  cout << "Enter 0 or 1, to indicate if the position is a mine(1) or not(0)\n";
  vector<vector<int>> matrix = EnterMatrix();
  cout << "The minefield is:\n";
  PrintMatrix(matrix);
  vector<vector<int>> resultMatrix = MinesWanted(matrix);
  cout << "The minefield with the mines around the positions is:\n";
  PrintMatrix(resultMatrix);
  return 0;
}