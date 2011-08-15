//      sudoku.cpp
//      
//      Copyright 2011 Shafeeq K <shafeeq94@gmail.com>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.


#include <iostream>
#include <fstream>
#define ORDER 9

using namespace std;

int sudoku[ORDER][ORDER];
int Check (int y[]);
int temp[ORDER];

void print(int matrix[ORDER][ORDER]) {
  for (int i = 0; i < ORDER; i++){
    for (int j = 0; j < ORDER; j++)
      cout << matrix[i][j] << " ";
    cout << endl;
  }
  return;
}
// All the *check functions read the respective elements to a linear array and 
//pass it to the check() function. Check function searches for multiple
//occurences of numbers, starting from the first element.

//Checks for duplications in each row 
int RowCheck ( int x[ORDER][ORDER]) {
  for (int i=0; i<ORDER; i++) {
    for (int j= 0; j<ORDER; j++)
      temp[j] = x[i][j];
			
    if ( Check (temp) == 0 )
      return 0;
  }
  return 1;
}

//Main Check function								
int Check (int y[ORDER]) {
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
int ColumnCheck ( int x[ORDER][ORDER]) {
  for (int i=0; i<ORDER; i++) {
    for (int j= 0; j<ORDER; j++)
      temp[j] = x[j][i];
		
    if ( Check (temp) == 0 )
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
      if (Check(temp) ==0)
	return 0;		
    }
  }
	
  return 1;
}
			

	
int main(int argc, char* argv[]) {
  //program can read a file and check for sudoku contained in it.

  fstream file;
  if(argc == 2) {
    file.open(argv[1], ios::in);
    if (file.is_open() ) {
      for (int i=0; i<ORDER; i++)
	for (int j=0; j<ORDER; j++)
	  file >> sudoku[i][j];  //reads integers from files

      print(sudoku); //prints the sudoku read and stored
    }
    else //if file couldn't be opened
      cout << "Could not locate file ' " << argv[1] << "'. Enter elements manually" << endl;
  }
  else if (argc > 2) //More than 1 arguments
    cout <<"More than one arguments. Enter elements manually\n";    

  //Asks for user input of all elements,
  //if opening the file fails or if more than two args were passed.
  if(!file.is_open() ){
    cout <<"Enter " << ORDER * ORDER << " elements " << endl;
    for ( int i=0; i<ORDER; i++) {
      for ( int j=0; j<ORDER; j++)
	cin >> sudoku[i][j];
    }
  }
	
  if ( RowCheck(sudoku) == 0 || ColumnCheck(sudoku)==0 || SquaresCheck(sudoku)==0) {
    cout<<"\nSudoku is incorrect\n";

    return 0;
  }
	
  cout<<"\nSudoku is correct\n";
  return 0;
}

