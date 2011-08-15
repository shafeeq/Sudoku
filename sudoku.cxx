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
#include <stdlib.h>
#define ORDER 9

using namespace std;

int sudoku[ORDER][ORDER];
int Check (int y[]);
int temp[ORDER];

int RowCheck ( int x[ORDER][ORDER]) {
  int i;
  int l;
	
  for (i=0; i<ORDER; i++) {
    for (l= 0; l<ORDER;l++)
      temp[l] = x[i][l];
			
    if ( Check (temp) == 0 )
      return 0;
  }
  return 1;
}
									
int Check (int y[ORDER]) {
  int lineartemp;
  for (int i=0; i<ORDER; i++) {
    lineartemp = y[i];
    for (int j=i+1; j<ORDER; j++) {
      if (y[j] ==  lineartemp)
	return 0
	  }
  }
  return 1;
}

int ColumnCheck ( int x[ORDER][ORDER]) {
  int i;
  int l;
  for (i=0; i<ORDER; i++) {
    for (l= 0; l<ORDER;l++)
      temp[l] = x[l][i];
		
    if ( Check (temp) == 0 )
      return 0;
  }
  return 1;
}			

int SquaresCheck (int x[ORDER][ORDER]) {
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
			

	
int main() {
  int i;
  int j;
	
  for ( i=0; i<ORDER; i++) {
    for ( j=0; j<ORDER; j++)
      cin >> sudoku[i][j];
  }
	
  if ( RowCheck(sudoku) == 0 || ColumnCheck(sudoku)==0 || SquaresCheck(sudoku)==0) {
    cout<<"\nSudoku is incorrect\n";
    return 0;
  }
	
  cout<<"\nSudoku is correct\n";
  return 0;
}

