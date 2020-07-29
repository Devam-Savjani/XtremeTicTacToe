/*
 * GROUP 16 - Members: Aayush, Ayoob, Devam, Elijah
 * The minimax algorithms.
*/

#include "ultimateTicTacToe.h"

//the minimax algorithm when the pick is free
int minimaxFree(board *b, bool isMaximising, int alpha, int beta, int depth)
{
  gameState currState = returnGameState(b);
  int score;
  int childScore;
  if (currState != TBD)
  {
    int value = returnStateValue(currState);
    return value - depth;
  }
  if (isBoardFull(*b) || allCellsWon(b))
  {
    return -depth;
  }

  if (depth == MAXIMUM_DEPTH)
  {
    return evaluateBoard(b);
  }

  int potentialPaths = 0;
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      if (b->cells[returnRow(i)][returnColumn(i)]->boxes[returnRow(j)][returnColumn(j)] == 0)
      {
        potentialPaths++;
      }
    }
  }

  pathArray *paths = initPathArray(potentialPaths);
  int pathCounter = 0;
  for (int k = 0; k < 9; k++)
  {
    for (int l = 0; l < 9; l++)
    {
      if (b->cells[returnRow(k)][returnColumn(k)]->boxes[returnRow(l)][returnColumn(l)] == 0)
      {
        if (isMaximising)
        {
          AITestPlay(b, k, l);
        }
        else
        {
          playerTestPlay(b, k, l);
        }
        paths->array[pathCounter]->score = evaluateBoard(b);
        paths->array[pathCounter]->position = l;
        paths->array[pathCounter]->cell = k;
        pathCounter++;
        resetCell(b, k, l);
      }
    }
  }

  sortPaths(paths, isMaximising);
  int halfOfPaths = paths->total / 2;

  if (isMaximising)
  {

    for (int i = 0; i < halfOfPaths; i++)
    {
      int cell = paths->array[i]->cell;
      int position = paths->array[i]->position;
      AITestPlay(b, cell, position);
      if (!cellWon(b, position) && !isCellFull(*b->cells[returnRow(position)][returnColumn(position)]))
      {
        childScore = minimaxRestricted(b, false, position, alpha, beta, depth + 1);
      }
      else
      {
        childScore = minimaxFree(b, false, alpha, beta, depth + 1);
      }
      resetCell(b, cell, position);
      score = MAX(score, childScore);
      alpha = MAX(score, alpha);
      if (alpha <= beta)
      {
        break;
      }
    }
    freePaths(paths);
    return score;
  }
  else
  {
    for (int i = 0; i < halfOfPaths; i++)
    {
      int cell = paths->array[i]->cell;
      int position = paths->array[i]->position;
      playerTestPlay(b, cell, position);
      if (!cellWon(b, position) && !isCellFull(*b->cells[returnRow(position)][returnColumn(position)]))
      {
        childScore = minimaxRestricted(b, true, position, alpha, beta, depth + 1);
      }
      else
      {
        childScore = minimaxFree(b, true, alpha, beta, depth + 1);
      }
      resetCell(b, cell, position);
      score = MIN(score, childScore);
      beta = MIN(score, beta);
      if (alpha <= beta)
      {
        break;
      }
    }
    freePaths(paths);
    return score;
  }
}

//the minimax algorithm when the pick is restricted
int minimaxRestricted(board *b, bool isMaximising, int cell, int alpha, int beta, int depth)
{
  gameState currState = returnGameState(b);
  int score;
  int childScore;

  if (depth == MAXIMUM_DEPTH)
  {
    return evaluateBoard(b);
  }

  if (currState != TBD)
  {
    int value = returnStateValue(currState);
    return value;
  }

  if (isBoardFull(*b) || allCellsWon(b))
  {
    return 0;
  }

  if (isCellFull(*b->cells[returnRow(cell)][returnColumn(cell)]))
  {
    return minimaxFree(b, isMaximising, alpha, beta, depth);
  }

  int potentialPaths = 0;
  for (int j = 0; j < 9; j++)
  {
    if (b->cells[returnRow(cell)][returnColumn(cell)]->boxes[returnRow(j)][returnColumn(j)] == 0)
    {
      potentialPaths++;
    }
  }

  pathArray *paths = initPathArray(potentialPaths);
  int pathCounter = 0;
  for (int x = 0; x < 9; x++)
  {
    if (b->cells[returnRow(cell)][returnColumn(cell)]->boxes[returnRow(x)][returnColumn(x)] == 0)
    {
      if (isMaximising)
      {
        AITestPlay(b, cell, x);
      }
      else
      {
        playerTestPlay(b, cell, x);
      }
      int score = evaluateCell(b, cell);
      paths->array[pathCounter]->score = score;
      paths->array[pathCounter]->position = x;
      pathCounter++;
      resetCell(b, cell, x);
    }
  }

  sortPaths(paths, isMaximising);

  int halfOfPaths = paths->total / 2;
  if (isMaximising)
  {
    score = A_SMALL_NUMBER;
    for (int i = 0; i < halfOfPaths + 1; i++)
    {
      int nextPos = paths->array[i]->position;
      AITestPlay(b, cell, nextPos);
      if (!cellWon(b, i) && !isCellFull(*b->cells[returnRow(i)][returnColumn(i)]))
      {
        childScore = minimaxRestricted(b, false, nextPos, alpha, beta, depth + 1);
      }
      else
      {
        childScore = minimaxFree(b, false, alpha, beta, depth + 1);
      }
      score = MAX(score, childScore);
      alpha = MAX(alpha, score);
      resetCell(b, cell, nextPos);
      if (alpha <= beta)
      {
        break;
      }
    }

    freePaths(paths);
    return score;
  }
  else
  {
    score = A_BIG_NUMBER;
    for (int i = 0; i < halfOfPaths; i++)
    {
      int nextPos = paths->array[i]->position;
      playerTestPlay(b, cell, nextPos);
      if (!cellWon(b, i) && !isCellFull(*b->cells[returnRow(i)][returnColumn(i)]))
      {
        childScore = minimaxRestricted(b, true, nextPos, alpha, beta, depth + 1);
      }
      else
      {
        childScore = minimaxFree(b, true, alpha, beta, depth + 1);
      }
      score = MIN(score, childScore);
      beta = MIN(alpha, score);
      resetCell(b, cell, i);
      if (beta >= alpha)
      {
        break;
      }
    }
    freePaths(paths);
    return score;
  }
}

//the AI works out the best move when it is a free move
void bestMoveFree(board *b, int *cellResult, int *positionResult)
{
  board *copy = initBoard();
  deepCopyBoard(copy, b);
  int minimaxScore = 0;
  int score = A_SMALL_NUMBER;
  for (int i = 0; i < 9; i++)
  {
    if (!cellWon(copy, i))
    {
      for (int j = 0; j < 9; j++)
      {
        if (b->cells[returnRow(i)][returnColumn(i)]->boxes[returnRow(j)][returnColumn(j)] == 0)
        {
          AITestPlay(copy, i, j);
          minimaxScore = minimaxRestricted(copy, false, i, A_SMALL_NUMBER, A_BIG_NUMBER, 0);
          if (score < minimaxScore)
          {
            score = minimaxScore;
            *cellResult = i;
            *positionResult = j;
          }
          resetCell(copy, i, j);
        }
      }
    }
  }
  freeBoard(copy);
}

//the AI works out the best move when it is a restricted move and stores that value in positionResult
void bestMoveRestricted(board *b, int *positionResult, int cell)
{
  board *copy = initBoard();
  deepCopyBoard(copy, b);
  int minimaxScore = 0;
  int score = A_SMALL_NUMBER;
  for (int i = 0; i < 9; i++)
  {
    if (b->cells[returnRow(cell)][returnColumn(cell)]->boxes[returnRow(i)][returnColumn(i)] == 0)
    {
      AITestPlay(copy, cell, i);
      minimaxScore = minimaxRestricted(copy, false, i, A_SMALL_NUMBER, A_BIG_NUMBER, 0);
      if (score < minimaxScore)
      {
        score = minimaxScore;
        *positionResult = i;
      }
      resetCell(copy, cell, i);
    }
  }

  freeBoard(copy);
}