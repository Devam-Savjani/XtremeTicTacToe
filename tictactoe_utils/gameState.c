/*
 * GROUP 16 - Members: Aayush, Ayoob, Devam, Elijah
 * Functions that get the state of the game.
*/

#include "ultimateTicTacToe.h"

//this is to check that the diagonal is one player - if cell is -1 it is looking at the whole board and if it is a normal number then it is looking at the cell it describes
bool checkDiagonals(board *b, int cell, bool isPlayer)
{
  bool diag1 = true;
  bool diag2 = true;
  if (cell == -1)
  {
    CELLSTATE targetState = isPlayer ? PLAYERWIN : AIWIN;
    for (int i = 0; i < 3; i++)
    {
      diag1 &= b->cells[i][i]->state == targetState;
      diag2 &= b->cells[i][2 - i]->state == targetState;
    }
    return diag1 || diag2;
  }
  else
  {
    int targetValue = isPlayer ? 1 : 2;
    for (int i = 0; i < 3; i++)
    {
      diag1 &= b->cells[returnRow(cell)][returnColumn(cell)]->boxes[i][i] == targetValue;
      diag2 &= b->cells[returnRow(cell)][returnColumn(cell)]->boxes[i][2 - i] == targetValue;
    }
    return diag1 || diag2;
  }
}

bool checkStraightLines(board *b, int cell, bool isPlayer)
{
  bool horizontal = true;
  bool vertical = true;
  if (cell == -1)
  {
    CELLSTATE targetState = isPlayer ? PLAYERWIN : AIWIN;
    for (int i = 0; i < 3; i++)
    {
      for (int j = 0; j < 3; j++)
      {
        horizontal &= b->cells[i][j]->state == targetState;
        vertical &= b->cells[j][i]->state == targetState;
      }
      if (horizontal || vertical)
      {
        return true;
      }
      horizontal = true;
      vertical = true;
    }
    return false;
  }
  else
  {
    int targetValue = isPlayer ? 1 : 2;
    for (int i = 0; i < 3; i++)
    {
      for (int j = 0; j < 3; j++)
      {
        horizontal &= b->cells[returnRow(cell)][returnColumn(cell)]->boxes[i][j] == targetValue;
        vertical &= b->cells[returnRow(cell)][returnColumn(cell)]->boxes[j][i] == targetValue;
      }
      if (horizontal || vertical)
      {
        return true;
      }
      horizontal = true;
      vertical = true;
    }
    return false;
  }
}

//sees if a cell has already been won by either the AI or player
bool cellFinished(board *b, int cell, bool isPlayer)
{
  bool diagonals = checkDiagonals(b, cell, isPlayer);
  bool straightLines = checkStraightLines(b, cell, isPlayer);
  if (diagonals || straightLines)
  {
    if (b->cells[returnRow(cell)][returnColumn(cell)]->state != TBD)
    {
      return true;
    }
    b->cells[returnRow(cell)][returnColumn(cell)]->state = isPlayer ? PLAYERWIN : AIWIN;
    return true;
  }
  else
  {
    b->cells[returnRow(cell)][returnColumn(cell)]->state = TBD;
    return false;
  }
}

//sees if a player has won the cell so no one should play in it
bool cellWon(board *b, int cell)
{
  return cellFinished(b, cell, true) || cellFinished(b, cell, false);
}

//checks if all cells have been won
bool allCellsWon(board *b)
{
  for (int i = 0; i < 9; i++)
  {
    if (!cellWon(b, i))
      return false;
  }
  return true;
}

//sees if the game has been won by a certain player
bool gameFinished(board *b, bool isPlayer)
{
  bool diagonals = checkDiagonals(b, -1, isPlayer);
  bool straightLines = checkStraightLines(b, -1, isPlayer);
  return diagonals || straightLines;
}

//sees if someone has won the game
bool gameWon(board *b)
{
  return gameFinished(b, true) || gameFinished(b, false);
}

//checks if a cell is completely filled
bool isCellFull(cell c)
{
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (c.boxes[i][j] == 0)
      {
        return false;
      }
    }
  }
  return true;
}
//checks if there are no more places to play on the board
bool isBoardFull(board b)
{
  for (int i = 0; i < 9; i++)
  {
    if (!isCellFull(*b.cells[returnRow(i)][returnColumn(i)]))
    {
      return false;
    }
  }
  return true;
}

//returns the state of the game
gameState returnGameState(board *b)
{
  if (gameFinished(b, true))
    return PLAYERWIN;
  else if (gameFinished(b, false))
    return AIWIN;
  else if (isBoardFull(*b))
    return DRAWN;
  else
    return TBD;
}