//      checks.cpp
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
//      
//      
#include "checkfns.h"
#define ORDER 9
extern int sudoku[ORDER][ORDER];
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
