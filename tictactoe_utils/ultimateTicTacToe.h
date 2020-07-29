/*
 * GROUP 16 - Members: Aayush, Ayoob, Devam, Elijah
 * The constants and structs required by the program.
*/

#ifndef boardConstants
#define boardConstant

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#define ITEMS_IN_ROW 21
#define ITEMS_IN_ROW 21
#define A_BIG_NUMBER 32000
#define A_SMALL_NUMBER -32000
#define CHECK_IF_NULL(ptr, msg) \
  if (!(ptr))                   \
  perror(msg), exit(EXIT_FAILURE)
#define MAX(a, b) (a < b) ? b : a
#define MIN(a, b) (a < b) ? a : b
#define MAXIMUM_DEPTH 10

typedef enum
{
  TBD,
  DRAWN,
  PLAYERWIN,
  AIWIN
} CELLSTATE;

typedef struct
{
  CELLSTATE state;
  int **boxes;
} cell;

typedef struct board
{
  cell ***cells;
} board;

typedef struct
{
  int score;
  int position;
  int cell;
} potentialPath;

typedef struct
{
  potentialPath **array;
  int total;
} pathArray;

typedef CELLSTATE gameState;

int returnRow(int);
int returnColumn(int);
cell *initCell();
potentialPath *initPotentialPath();
pathArray *initPathArray(int);
board *initBoard();
void deepCopyCell(cell *, cell *);
void deepCopyBoard(board *, board *);
void freeCell(cell *);
void freeBoard(board *);
void freePaths(pathArray *);
int evaluateBoard(board *);
int evaluateCell(board *, int);
int almostFinishedDiagonals(cell, bool);
int almostFinishedColumns(cell, bool);
int almostFinishedRows(cell, bool);
int returnStateValue(gameState);
void playerTestPlay(board *, int, int);
void AITestPlay(board *, int, int);
void resetCell(board *, int, int);
void sortPaths(pathArray *, bool);
void swap(potentialPath *, potentialPath *);
bool checkDiagonals(board *, int, bool);
bool checkStraightLines(board *, int, bool);
bool cellFinished(board *, int, bool);
bool cellWon(board *, int);
bool allCellsWon(board *);
bool gameFinished(board *, bool);
bool gameWon(board *);
bool isCellFull(cell);
bool isBoardFull(board);
gameState returnGameState(board *);
char cellRep(int);
char *createRow();
char **createRowArray();
void freeRowArray(char **);
void printRow(board *, int, char *);
void printBoard(board *);
void freePick(board *, int *, int, int, bool);
void restrictedPick(board *, int *, int, bool);
int minimaxFree(board *, bool, int, int, int);
int minimaxRestricted(board *, bool, int, int, int, int);
void askCellandPos(int *, int *);
void askPosition(int *);
void bestMoveFree(board *, int *, int *);
void bestMoveRestricted(board *, int *, int);

#endif // boardConstants
