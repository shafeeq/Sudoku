#include <iostream>
using namespace std;
#define ORDER 9
int sudoku[ORDER][ORDER] = {0};
void print(int matrix[ORDER][ORDER]) 
{
  for (int i = 0; i < ORDER; i++) {
    for (int j = 0; j < ORDER; j++)
      cout << matrix[i][j] << " ";
    cout << endl;
  }
  cout << endl;
  return;
}
int checkRow(int row, int num) 
{
  int foundnum = 0;
  for (int i = 0; i < 9; i++) {
    if (sudoku[row][i] == num) {
      foundnum = 1;
      break;
    }
  }
  if (foundnum == 1)
    return 0;
  else
    return 1;
}
int checkColumn(int column, int num) 
{
  int foundnum = 0;
  for (int i = 0; i < 9; i++) {
    if (sudoku[i][column] == num) {
      foundnum = 1;
      break;
    }
  }
  if (foundnum == 1)
    return 0;
  else
    return 1;
}
int checkSquare(int row, int column, int num) 
{
  int foundnum = 0;
  int startIndexRow = (row / 3) * 3;
  int startIndexColumn = (column / 3) * 3;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (sudoku[startIndexRow + i][startIndexColumn + j] == num ){
        foundnum = 1;
        break;
      }
    }
  }
  if (foundnum == 1)
    return 0;
  else
    return 1; 
}
int placeNum(int row, int column)
{
  int placednum = 0;
  for (int num = sudoku[row][column] + 1; num <= 9; num++) {
    if (checkRow(row,num) && checkColumn(column,num) && checkSquare(row,column,num)) {
      placednum = 1;
      sudoku[row][column] = num;
      break;
    } else {
      continue;
    }
  }
  if (placednum == 1)
    return 1;
  else 
    return 0;
}
int goBack(int &row, int &column) {
  if (row == 0 && column == 0)
    return 0;
  else {    
    if (column != 0)
      column = column - 2;
    else {
      row = row - 1;
      column = 7;
    }
    
    return 1;
  }
}
void solveSudoku()
{
  for (int row = 0; row < 9; row++) {
    for (int column = 0; column < 9; column++) {
      if (!placeNum(row, column)) {
	sudoku[row][column] = 0;
	if (!goBack(row, column))
	  return ;
      }
    }
  }
}

int main()
{
  solveSudoku();
  print (sudoku);
  return 0;
}
