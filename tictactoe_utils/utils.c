/*
 * GROUP 16 - Members: Aayush, Ayoob, Devam, Elijah
 * Inititalising of structures and other utils required by the game.
*/

#include "ultimateTicTacToe.h"

int returnRow(int i)
{
  return i / 3;
}

int returnColumn(int i)
{
  return i % 3;
}

// STRUCT BASED FUNCTIONS -- INITILIASE AND FREE
// intialises a cell and puts it in the heap
cell *initCell()
{
  cell *new = (cell *)calloc(1, sizeof(cell));
  CHECK_IF_NULL(new, "couldn't allocate cell");
  new->state = TBD;
  new->boxes = (int **)calloc(3, sizeof(int *));
  CHECK_IF_NULL(new->boxes, "couldn't allocate array of int arrays");
  for (int i = 0; i < 3; i++)
  {
    new->boxes[i] = (int *)calloc(3, sizeof(int));
    CHECK_IF_NULL(new->boxes[i], "couldn't allocate array of 3 ints");
  }
  return new;
}

potentialPath *initPotentialPath()
{
  potentialPath *new = (potentialPath *)calloc(1, sizeof(potentialPath));
  CHECK_IF_NULL(new, "couldnt allocate new path");
  return new;
}

pathArray *initPathArray(int length)
{
  pathArray *new = (pathArray *)calloc(1, sizeof(pathArray));
  CHECK_IF_NULL(new, "couldnt alloate new path array");
  potentialPath **array = (potentialPath **)calloc(length, sizeof(potentialPath *));
  CHECK_IF_NULL(new, "couldnt allocate array");
  for (int i = 0; i < length; i++)
  {
    array[i] = initPotentialPath();
  }
  new->array = array;
  new->total = length;
  return new;
}

// intiliases the board and all of its cells
board *initBoard()
{
  board *new = (board *)calloc(1, sizeof(board));
  CHECK_IF_NULL(new, "couldn't allocate board");
  new->cells = (cell ***)calloc(3, sizeof(cell **));
  CHECK_IF_NULL(new->cells, "couldn't allocate cell");
  for (int i = 0; i < 3; i++)
  {
    new->cells[i] = (cell **)calloc(3, sizeof(cell *));
    CHECK_IF_NULL(new->cells[i], "couldn't allocate row of cells");
  }
  for (int j = 0; j < 9; j++)
  {
    new->cells[returnRow(j)][returnColumn(j)] = initCell();
  }
  return new;
}

//creates a  copy of a cell
void deepCopyCell(cell *buffer, cell *actual)
{
  buffer->state = actual->state;
  for (int i = 0; i < 9; i++)
  {
    buffer->boxes[returnRow(i)][returnColumn(i)] = actual->boxes[returnRow(i)][returnColumn(i)];
  }
}

//creates a copy of a whole board (ONLY USED IN BEST MOVE FUNCTIONS)
void deepCopyBoard(board *buffer, board *actual)
{
  for (int i = 0; i < 9; i++)
  {
    deepCopyCell(buffer->cells[returnRow(i)][returnColumn(i)], actual->cells[returnRow(i)][returnColumn(i)]);
  }
}

//frees a cell from memory
void freeCell(cell *c)
{
  for (int i = 0; i < 3; i++)
  {
    free(c->boxes[i]);
  }
  free(c->boxes);
  free(c);
}

//frees the board from memory
void freeBoard(board *b)
{
  for (int i = 0; i < 9; i++)
  {
    freeCell(b->cells[returnRow(i)][returnColumn(i)]);
  }
  free(b->cells);
  free(b);
}

void freePaths(pathArray *p)
{
  for (int i = 0; i < p->total; i++)
  {
    free(p->array[i]);
  }
  free(p);
}

void askCellandPos(int *cell, int *position)
{
  char cellInput[15];
  char posInput[15];
  scanf("%s", cellInput);
  scanf("%s", posInput);
  if (cellInput[0] < '0' || cellInput[0] > '9' || posInput[0] < '0' || posInput[0] > '9')
  {
    *cell = 9;
    *position = 9;
  }
  else
  {
    *cell = atoi(cellInput);
    *position = atoi(posInput);
  }
}

void askPosition(int *position)
{
  char posInput[15];
  scanf("%s", posInput);
  if (posInput[0] < '0' || posInput[0] > '9')
  {
    *position = 9;
  }
  else
  {
    *position = atoi(posInput);
  }
}