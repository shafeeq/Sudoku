#include <iostream>
#include <fstream>
#include "checkfns.h"
#define ORDER 9

using namespace std;

int sudoku[ORDER][ORDER] = {0};
int isClueGiven[ORDER][ORDER] = {0};
int prevPosition[ORDER][ORDER][2];
int placeNum(int row, int column);


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


void storePositions()
{
  int temprow, tempcolumn;
  temprow = -1;
  tempcolumn = -1;
    
  for (int row = 0; row < 9; row++) {
    for (int column = 0; column < 9; column++) {
      if (isClueGiven[row][column] == 0) {
	prevPosition[row][column][0] = temprow;
	prevPosition[row][column][1] = tempcolumn;
	temprow = row;
	tempcolumn = column;
      }
    }
  }
}


int goBack(int &row, int &column)
{
  int trow, tcolumn;
  
  if (row == 0 && column == 0)
    return 0;
  sudoku[row][column] = 0;
    
  trow = prevPosition[row][column][0];
  tcolumn = prevPosition[row][column][1];
  tcolumn -= 1;
    
  row = trow;
  column = tcolumn;
    
  return 1;
}


int placeNum(int row, int column)
{
  if(isClueGiven[row][column] == 1)
    return 1;
    
  for (int num = sudoku[row][column] + 1; num <= 9; num++) {
    if (checkRow(row,num) && checkColumn(column, num) && checkSquare(row,column,num) ) {
      sudoku[row][column] = num;
      return 1;
    }
  }
    
  sudoku[row][column] = 0;
    
  return 0;
}


int solveSudoku()
{
  for (int row = 0; row < 9; row++) {
    for (int column = 0; column < 9; column++) {
      if (!placeNum(row, column)) {
	sudoku[row][column] = 0;
	if (!goBack(row, column))
	  return 0;
      }
    }
  }
    
  return 1;
}


int main(int argc, char* argv[])
{
  fstream file;
   
  if (argc == 2) 
    {
      file.open(argv[1], ios::in);
    
      if (file.is_open()) 
	{
	  for (int row = 0; row < ORDER; row++) {
	    for (int column = 0; column < ORDER; column++) {
	      file >> sudoku[row][column];
	      if (sudoku[row][column] !=0)
		isClueGiven[row][column] = 1;
	    }
	  }
	  print (sudoku);
	}  else
    cout << "Could not locate file ' " << argv[1] << "'. Enter elements manually" << endl;
    }
  
  if (argc > 2)
    cout << "More than one arguments. Enter elements manually\n";

  if (!file.is_open() ) {
    cout <<"Enter 81  elements (0s for cells without clues) :" << endl;

    for ( int row = 0; row < ORDER; row++) {
      for ( int column = 0; column < ORDER; column++) {
	cin >> sudoku[row][column];
	if (sudoku[row][column] !=0)
	  isClueGiven[row][column] = 1;
      }
    }

    print (sudoku);
  }
  
    storePositions();
    solveSudoku();
    print(sudoku); 
     return 0;
}
