/*
 * GROUP 16 - Members: Aayush, Ayoob, Devam, Elijah
 * The main function of the game which deals with user interactions.
*/

#include "tictactoe_utils/ultimateTicTacToe.h"

int main()
{
  bool firstTry = true;
  bool isPlayer = false;
  int *AIFreePickCell = (int *)calloc(1, sizeof(int));
  int *AIFreePickPosition = (int *)calloc(1, sizeof(int));
  int *AIRestPick = (int *)calloc(1, sizeof(int));
  int *holdsNext = (int *)calloc(1, sizeof(int));
  CHECK_IF_NULL(AIFreePickCell, "could not allocate integer for saving the AI's cell choice");
  CHECK_IF_NULL(AIFreePickPosition, "could not allocate integer for saving the position that the AI chooses in free pick)");
  CHECK_IF_NULL(AIRestPick, "could not allocate space for posiiton that AI chose in restricted pick");
  CHECK_IF_NULL(holdsNext, "couldnt allocate space for holding the next cell position");
  board *b = initBoard();
  int cell;
  int position;
  char *response = (char *)calloc(4, sizeof(char));
  printf("Greetings! Welcome to ULTIMATE Tic Tac Toe. Would you like to go first? (y or n)\n");
  fgets(response, 2, stdin);
  isPlayer = strcmp("y", response) == 0;
  free(response);
  if (firstTry)
  {
    if (isPlayer)
    {
      printf("You make the first move. You will be X. Firstly pick the cell you would like to play in, numbered from 0 to 8 where 0 is the top left and 8 is the bottom right and then pick a position inside the cell (separated by a space or RETURN):\n");
      cell = 9;
      position = 9;
      askCellandPos(&cell, &position);
      freePick(b, holdsNext, cell, position, isPlayer);
    }
    else
    {
      printf("The CPU will go first. It is O.\n");
      bestMoveFree(b, AIFreePickCell, AIFreePickPosition);
      printf("The CPU has chosen to play in cell %i and position %i \n", *AIFreePickCell, *AIFreePickPosition);
      freePick(b, holdsNext, *AIFreePickCell, *AIFreePickPosition, isPlayer);
    }
    printf("\n");
    firstTry = false;
    isPlayer = !isPlayer;
    printBoard(b);
    printf("\n");
  }
  while (!gameWon(b) && !isBoardFull(*b))
  {
    if (isPlayer)
    {
      if (!cellWon(b, *holdsNext) && !isCellFull(*b->cells[returnRow(*holdsNext)][returnColumn(*holdsNext)]))
      {
        printf("You have to play in cell %i. Please pick a position\n", *holdsNext);
        askPosition(&position);
        restrictedPick(b, holdsNext, position, isPlayer);
      }
      else
      {
        printf("You have a free choice of a cell to play in. Pick a cell and a position (separated by a space or RETURN):\n");
        askCellandPos(&cell, &position);
        freePick(b, holdsNext, cell, position, isPlayer);
      }
    }
    else
    {
      printf("The CPU is thinking...\n");
      sleep(1);
      if (!cellWon(b, *holdsNext) && !isCellFull(*b->cells[returnRow(*holdsNext)][returnColumn(*holdsNext)]))
      {
        printf("The CPU has to play in cell %i \n", *holdsNext);
        bestMoveRestricted(b, AIRestPick, *holdsNext);
        printf("The CPU has chosen to play in position %i\n", *AIRestPick);
        restrictedPick(b, holdsNext, *AIRestPick, isPlayer);
      }
      else
      {
        printf("The CPU has a free pick\n");
        bestMoveFree(b, AIFreePickCell, AIFreePickPosition);
        printf("The CPU has chosen to play in cell %i and position %i \n", *AIFreePickCell, *AIFreePickPosition);
        freePick(b, holdsNext, *AIFreePickCell, *AIFreePickPosition, isPlayer);
      }
    }
    printf("\n");
    printBoard(b);
    printf("\n");
    isPlayer = !isPlayer;
  }
  if (!gameWon(b))
  {
    printf("This is a DRAW. You fought well!\n");
  }
  else
  {
    if (!isPlayer)
    {
      printf("CONGRATULATIONS! You have won!");
    }
    else
    {
      printf("Unfortunately the CPU has won this time. Better luck next time...\n");
    }
  }

  freeBoard(b);
  free(AIFreePickCell);
  free(AIFreePickPosition);
  free(AIRestPick);
  free(holdsNext);
  return 0;
}
