/* 
 * NOTE: At this stage, the program makes no use of the functions defined in this file.
 * This file and the functions within can be used to check if the solution created by 
 * the solver is correct, ie according to the constraints in each row, column, and squares
 *  -> no duplications.
 * 
 */

#include <iostream>
#include "checkfns.h"
#define ORDER 9

using namespace std;

extern int sudoku[ORDER][ORDER];
int check (int y[]);
int temp[ORDER];


// All the *check functions read the respective elements to a linear array and 
//pass it to the check() function. Check function searches for multiple
//occurences of numbers, starting from the first element.

//Checks for duplications in each row 
int rowCheck ( int x[ORDER][ORDER]) {
  for (int i=0; i<ORDER; i++) {
    for (int j= 0; j<ORDER; j++)
      temp[j] = x[i][j];
			
    if ( check (temp) == 0 )
      return 0;
  }
  return 1;
}

//Main Check function								
int check (int y[ORDER]) {
  int lineartemp;
  for (int i=0; i<ORDER; i++) {
    lineartemp = y[i];
    for (int j=i+1; j<ORDER; j++) { //searches for duplications
      if (y[j] ==  lineartemp)
	return 0;
	  }
  }
  return 1;
}

//Checks for duplications in each column
int columnCheck ( int x[ORDER][ORDER]) {
  for (int i=0; i<ORDER; i++) {
    for (int j= 0; j<ORDER; j++)
      temp[j] = x[j][i];
		
    if ( check (temp) == 0 )
      return 0;
  }
  return 1;
}			

//Checks for duplaication in all 9 subsquares
int SquaresCheck (int x[ORDER][ORDER]) {
  //column and row loops set the starting index for each subsquare.
  //ie (since I put column loop first),
  //[0][0], [3][0], [6][0], [0][3], [3][3], [6][3], [0][6],[3][6], [6][6]
  // i and j  are usual iterators to create the linear array,
  // and k iterates index of linear array (temp).   

  int i;
  int j;
  int column;
  int row;
  int k;
	
  for (column=0; column <= 6; column += 3) {
    for (row=0; row <= 6; row += 3) {
      for (k=0, i=0; i<3; i++) {
	for (j=0; j<3; j++)
	  temp[k++] = x[row+i][column+j];
      }
      if (check(temp) ==0)
	return 0;		
    }
  }
	
  return 1;
}

int checkSolution() 
{
  if ( !rowCheck(sudoku) || !columnCheck(sudoku) || !SquaresCheck(sudoku) )
     return 0;
  else
     return 1;
}
