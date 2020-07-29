/*
 * GROUP 16 - Members: Aayush, Ayoob, Devam, Elijah
 * Functions used in the AI of the game.
*/

#include "ultimateTicTacToe.h"

void swap(potentialPath *a, potentialPath *b)
{
  potentialPath temp = *a;
  *a = *b;
  *b = temp;
}

void sortPaths(pathArray *p, bool ascending)
{
  int size = p->total;
  if (ascending)
  {
    for (int i = 0; i < size; i++)
    {
      for (int j = i + 1; j < size; j++)
      {
        if (p->array[i]->score < p->array[j]->score)
        {
          swap(p->array[i], p->array[j]);
        }
      }
    }
  }
  else
  {
    for (int i = 0; i < size; i++)
    {
      for (int j = i + 1; j < size; j++)
      {
        if (p->array[i]->score > p->array[j]->score)
        {
          swap(p->array[i], p->array[j]);
        }
      }
    }
  }
}

//resets a cell (ONLY USED IN MINIMAX FUNCTIONS)
void resetCell(board *b, int cell, int pos)
{
  b->cells[returnRow(cell)][returnColumn(cell)]->boxes[returnRow(pos)][returnColumn(pos)] = 0;
}

// sets a cell to an AI play (ONLY USED IN MINIMAX FUNCTIONS)
void AITestPlay(board *b, int cell, int pos)
{
  b->cells[returnRow(cell)][returnColumn(cell)]->boxes[returnRow(pos)][returnColumn(pos)] = 2;
}

// sets a cell to an user play (ONLY USED IN MINIMAX FUNCTIONS)
void playerTestPlay(board *b, int cell, int pos)
{
  b->cells[returnRow(cell)][returnColumn(cell)]->boxes[returnRow(pos)][returnColumn(pos)] = 1;
}

//returns an integer value of the state of the game
int returnStateValue(gameState state)
{
  if (state == AIWIN)
    return 100;
  if (state == PLAYERWIN)
    return -100;
  else
    return 0;
}

//works out how many almost completed rows there are for either the CPU or player
int almostFinishedRows(cell c, bool isPlayer)
{
  int targetValue = isPlayer ? 1 : 2;
  int result = 0;
  for (int i = 0; i < 3; i++)
  {
    bool pair1 = c.boxes[i][0] == c.boxes[i][1] && c.boxes[i][0] == targetValue && c.boxes[i][2] == 0;
    bool pair2 = c.boxes[i][0] == c.boxes[i][2] && c.boxes[i][0] == targetValue && c.boxes[i][1] == 0;
    bool pair3 = c.boxes[i][1] == c.boxes[i][2] && c.boxes[i][1] == targetValue && c.boxes[i][0] == 0;
    if (pair1 || pair2 || pair3)
    {
      result++;
    }
  }
  return result;
}
// works out how many almost completed columns there are for either CPU or player
int almostFinishedColumns(cell c, bool isPlayer)
{
  int targetValue = isPlayer ? 1 : 2;
  int result = 0;
  for (int i = 0; i < 3; i++)
  {
    bool pair1 = c.boxes[0][i] == c.boxes[1][i] && c.boxes[1][i] == targetValue && c.boxes[2][i] == 0;
    bool pair2 = c.boxes[0][i] == c.boxes[2][i] && c.boxes[0][i] == targetValue && c.boxes[1][i] == 0;
    bool pair3 = c.boxes[1][i] == c.boxes[2][i] && c.boxes[1][i] == targetValue && c.boxes[0][i] == 0;
    if (pair1 || pair2 || pair3)
    {
      result++;
    }
  }
  return result;
}
//sees if there are any almost finished diagonals for eith er the CPU or player
int almostFinishedDiagonals(cell c, bool isPlayer)
{
  int targetValue = isPlayer ? 1 : 2;
  int result = 0;
  bool diag1 = c.boxes[0][0] == c.boxes[1][1] && c.boxes[0][0] == targetValue && c.boxes[2][2] == 0;
  bool diag2 = c.boxes[0][0] == c.boxes[2][2] && c.boxes[0][0] == targetValue && c.boxes[1][1] == 0;
  bool diag3 = c.boxes[1][1] == c.boxes[2][2] && c.boxes[1][1] == targetValue && c.boxes[0][0] == 0;
  if (diag1 || diag2 || diag3)
  {
    result++;
  }
  diag1 = c.boxes[0][2] == c.boxes[1][1] && c.boxes[0][2] == targetValue && c.boxes[2][0] == 0;
  diag2 = c.boxes[0][2] == c.boxes[2][0] && c.boxes[0][2] == targetValue && c.boxes[1][1] == 0;
  diag3 = c.boxes[1][1] == c.boxes[2][0] && c.boxes[1][1] == targetValue && c.boxes[0][2] == 0;
  if (diag1 || diag2 || diag3)
  {
    result++;
  }
  return result;
}

//returns an int for how "good" the board is for the AI
int evaluateCell(board *b, int i)
{
  cell c = *b->cells[returnRow(i)][returnColumn(i)];
  if (b->cells[returnRow(i)][returnColumn(i)]->state == AIWIN)
    return 10;
  if (b->cells[returnRow(i)][returnColumn(i)]->state == PLAYERWIN)
    return -10;
  if (isCellFull(*b->cells[returnRow(i)][returnColumn(i)]))
    return 0;
  int AIPairs = 2 * (almostFinishedRows(c, false) + almostFinishedColumns(c, false) + almostFinishedDiagonals(c, false));
  int playerPairs = 2 * (almostFinishedRows(c, true) + almostFinishedColumns(c, true) + almostFinishedDiagonals(c, true));

  int powerPositions = 0;
  if (c.boxes[1][1] == 1)
    powerPositions -= 2;
  if (c.boxes[1][1] == 2)
    powerPositions += 2;
  for (int k = 0; k < 3; k++)
  {
    if (k % 2 == 0)
    {
      if (c.boxes[k][k] == 2)
        powerPositions++;
      if (c.boxes[k][k] == 1)
        powerPositions--;
      if (c.boxes[k][2 - k] == 1)
        powerPositions--;
      if (c.boxes[k][2 - k] == 2)
        powerPositions++;
    }
  }
  return AIPairs - playerPairs + powerPositions;
}

int evaluateBoard(board *b)
{
  int result = 0;
  for (int i = 0; i < 9; i++)
  {
    result += evaluateCell(b, i);
  }
  return result;
}