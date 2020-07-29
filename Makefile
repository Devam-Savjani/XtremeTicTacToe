CC      = gcc
CFLAGS  = -Wall -g -D_DEFAULT_SOURCE -D_POSIX_SOURCE -std=c99 -Werror -pedantic

.SUFFIXES: .c .o

.PHONY: all clean

all: ultimateTicTacToe

ultimateTicTacToe: ultimateTicTacToe.o tictactoe_utils/gameState.o tictactoe_utils/makeMark.o tictactoe_utils/tictactoeAI.o tictactoe_utils/utils.o tictactoe_utils/output.o tictactoe_utils/minimax.o
		$(CC) $^ -o $@

ultimateTicTacToe.o: ultimateTicTacToe.c tictactoe_utils/ultimateTicTacToe.h
		$(CC) $(CFLAGS) $< -c

gameState.o: tictactoe_utils/gameState.c tictactoe_utils/ultimateTicTacToe.h
		$(CC) $(CFLAGS) $< -c

makeMark.o: tictactoe_utils/makeMark.c tictactoe_utils/ultimateTicTacToe.h
		$(CC) $(CFLAGS) $< -c

tictactoeAI.o: tictactoe_utils/tictactoeAI.c tictactoe_utils/ultimateTicTacToe.h
		$(CC) $(CFLAGS) $< -c

utils.o: tictactoe_utils/utils.c tictactoe_utils/ultimateTicTacToe.h
		$(CC) $(CFLAGS) $< -c

output.o: tictactoe_utils/output.c tictactoe_utils/ultimateTicTacToe.h
		$(CC) $(CFLAGS) $< -c

minimax.o: tictactoe_utils/minimax.c tictactoe_utils/ultimateTicTacToe.h
		$(CC) $(CFLAGS) $< -c


clean:
	rm -f $(wildcard *.o)
	rm -f ultimateTicTacToe
	rm -f tictactoe_utils/*.o
