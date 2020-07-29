/*
 * GROUP 16 - Members: Aayush, Ayoob, Devam, Elijah
 * Functions that represent the board in terminal.
*/

#include "ultimateTicTacToe.h"

//converts an integer into a character representation
char cellRep(int i)
{
  switch (i)
  {
  case 1:
    return 'X';
    break;
  case 2:
    return 'O';
    break;
  default:
    return '-';
    break;
  }
}

//creates a string and puts it on the heap
char *createRow()
{
  char *new = (char *)calloc(ITEMS_IN_ROW, sizeof(char));
  CHECK_IF_NULL(new, "couldn't allocate string");
  return new;
}
//creates an array of strings and puts them on the heap
char **createRowArray()
{
  char **new = (char **)calloc(9, sizeof(char *));
  CHECK_IF_NULL(new, "couldn't allocate string array");
  for (int i = 0; i < 9; i++)
  {
    new[i] = createRow();
  }
  return new;
}

//frees the created string array
void freeRowArray(char **arr)
{
  for (int i = 0; i < 9; i++)
  {
    free(arr[i]);
  }
  free(arr);
}

//converts a whole row of the board into a string and stores it in a string buffer
void printRow(board *b, int i, char *buffer)
{
  int cellRow = i < 3 ? 0 : (i < 6 ? 1 : 2);
  int rowInCell = i % 3;
  int counter = 0;
  cell **rowOfCells = b->cells[cellRow];
  cell *currCell;
  for (int i = 0; i < 3; i++)
  {
    currCell = rowOfCells[i];
    for (int j = 0; j < 3; j++)
    {
      buffer[counter] = cellRep(currCell->boxes[rowInCell][j]);
      counter++;
      if (j != 2)
      {
        buffer[counter] = '|';
        counter++;
      }
      else
      {
        buffer[counter] = ' ';
        buffer[counter + 1] = ' ';
        counter += 2;
      }
    }
  }
}

//prints out the whole board
void printBoard(board *b)
{
  char **rowArr = createRowArray();
  for (int i = 0; i < 9; i++)
  {
    printRow(b, i, rowArr[i]);
  }

  for (int j = 0; j < 9; j++)
  {
    printf("%s", rowArr[j]);
    if (j == 2 || j == 5)
    {
      printf("\n");
    }
    printf("\n");
  }
  freeRowArray(rowArr);
}