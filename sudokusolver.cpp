/*  
 *  sudokusolver.cpp
 *  
 *  Copyright 2011 Shafeeq K <shafeeq94@gmail.com>
 *  
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1301, USA.
 */


/* Solves a sudoku puzzle
 * , supposedly. It can handle an empty puzzle or that with a few cells 
 * to be filled very well. But it takes a loong time to slve 'real' puzzles.
 * In fact, I gave up trying all of them when it was about 10 minutes.
 * If anyone has a bit more time than that (say, a day? a week?)
 * please  try it and mail me.
 * 
 * Classic bruteforce (backtracking) method is used, but no recursions.
 */ 
#include <iostream>
#include <fstream>
using namespace std;
#define ORDER 9
int sudoku[ORDER][ORDER] = {0};
int isClueGiven[ORDER][ORDER] = {0};

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
  int startIndexRow = (row / 3) *   3;
  int startIndexColumn = (column / 3) *   3;
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
  if (isClueGiven[row][column] == 1)
    return 1;

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
  /* The function sets the values of 'row' and 'column' to go back the the
   * immediate prevois fillable position
   *  
   * The below 'if' sees if fn is  asked to go to previous element from [0][0],
   * which shows that sudoku cannot be solved (really?) and returns 0*/
  if (row == 0 && column == 0)
    return 0;
 
  /* REVERSE ITERATOR
   * finds the immediate previous element that can be changed by iterating
   * backwards through the sudoku */

  int flag = 0, i, j, found = 0;

  for(i = row; i >= 0; i--) {
    /* To start from given column at first, but later when row changes,
     * column should be set to 9  to check all elements*/

    if (flag == 0){
      j = column;
      flag = 1;
    }
    else
      j = 8;

    /*  iterator:*/
    for (; j >= 0; j--) {
      if (isClueGiven[i][j] == 0) {
	found = 1;
	break;
      }
    }
    if (found == 1)
      break;
  }

  /* The iterator returns the exact positon, but while returning, it has to be
   * modified so that the column++ of solving function doesnt affect it
   * so if not the first element in row, column is decreased by 2 
   *  ==> in effect, (-2)++ = -1  (bingo!) and if it is the first element,
   * row is decreased by 1 and column is set to 7
   *  ==> 7+1 = 8 (last element) of previos (row-1) row */

  if( i < 0)
    return 0;
  else {
    if ( j != 0)
      column = j - 2;
    else {
      row = i - 1;
      column = 7;
    }
    return 1;
  }
}
 

void solveSudoku()
{
  /* Iterates through all elements, asks placeNum() to fill
   * but if placeNum() fails, goBack() is called,
   * goBack() will make sure that controlling variables' (row, column) values are
   * set accordingly to previous fillable position. 
   * But if goBack() fails, that'd be the end of story*/
  
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

int main(int argc, char* argv[])
{
  /* File handling part. The user is expected to give zeroes where
   * clues are not available. */
  fstream file;
  if (argc == 2) {
    file.open(argv[1], ios::in);
    if (file.is_open()) {
      for (int row = 0; row < ORDER; row++) {
	for (int column = 0; column < ORDER; column++) {
	  file >> sudoku[row][column];
	  if (sudoku[row][column] !=0)
	    isClueGiven[row][column] = 1;
	}
      }
      print (sudoku);
      print (isClueGiven);
    } else
      cout << "Could not locate file ' " << argv[1] << "'. Enter elements manually" << endl;
  }
  else if (argc > 2)
    cout << "More than one arguments. Enter elements manually\n";
  
  
  /* User input part */
  if(!file.is_open() ){
    cout <<"Enter 81  elements (0s for cells without clues) :" << endl;
    for ( int row = 0; row < ORDER; row++) {
      for ( int column = 0; column < ORDER; column++) {
	cin >> sudoku[row][column];
	if (sudoku[row][column] !=0)
	  isClueGiven[row][column] = 1;
      }
    }
    cout << endl;
    /* DEBUG print(isClueGiven); */
  }
  
  
  solveSudoku();
  print (sudoku);
  return 0;
}
