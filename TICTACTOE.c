#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

#define SIDE 3
#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

// Structure to store the move

struct Move {
    int row, col;
};

// Create functions for each individual prototype

void gameboard(char board[][SIDE]);
void instructions();
void initialization(char board[][SIDE], int moves[]);
void winner(int turn);
bool rowcrossed(char board[][SIDE]);
bool columncrossed(char board[][SIDE]);
bool diagonalcrossed(char board[][SIDE]);
bool gameover(char board[][SIDE]);
void playTICTACTOE(int turn);
int evaluate(char b[][SIDE]);
int minimax(char board[][SIDE], int depth, bool isMax);
struct Move findBestMove(char board[][SIDE]);

// Coding the function to show the gameboard

void gameboard(char board[][SIDE]) {
    printf("\n\n");
    printf("\t\t\t %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("\t\t\t--------------\n");
    printf("\t\t\t %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("\t\t\t--------------\n");
    printf("\t\t\t %c | %c | %c \n\n", board[2][0], board[2][1], board[2][2]);
}

//  Coding the function to show the instructions of the game

void instructions() {
    printf("\t\t\t Tic-Tac-Toe\n\n");
    printf("Choose a number from 1-9 within the boxes below.\n\n");
    printf("\t\t\t 1 | 2 | 3 \n");
    printf("\t\t\t--------------\n");
    printf("\t\t\t 4 | 5 | 6 \n");
    printf("\t\t\t--------------\n");
    printf("\t\t\t 7 | 8 | 9 \n\n");
    printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n");
}

// Coding the function to start or display the game

void initialization(char board[][SIDE], int moves[]) {
    // Board is empty
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++)
            board[i][j] = ' ';
    }

    // Fill the board with numbers for each move
    for (int i = 0; i < SIDE * SIDE; i++)
        moves[i] = i;

    // Moves are randomized
    for (int i = 0; i < SIDE * SIDE; i++) {
        int randIndex = rand() % (SIDE * SIDE);
        int temp = moves[i];
        moves[i] = moves[randIndex];
        moves[randIndex] = temp;
    }
}

// Coding the function to display or initalize a winner

void winner(int turn) {
    if (turn == COMPUTERMOVE)
        printf("You won!\n");
    else
        printf("COMPUTER has won!\n");
}

// Coding the function to check if row is crossed with same player's moveset

bool rowcrossed(char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return true;
    }
    return false;
}

// Coding the function to check if column is crossed with the same player's moveset

bool columncrossed(char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return true;
    }
    return false;
}

// Coding the function to check if diagonal is crossed with same player's moveset

bool diagcrossed(char board[][SIDE]) {
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' '))
        return true;
    return false;
}

// Coding the function to check if the game has ended

bool gameover(char board[][SIDE]) {
    return rowcrossed(board) || columncrossed(board) || diagcrossed(board);
}

// Using evaluation function for minimax algorithm
int evaluate(char b[][SIDE]) {
    // X or O win for rows
    for (int row = 0; row < SIDE; row++) {
        if (b[row][0] == b[row][1] && b[row][1] == b[row][2]) {
            if (b[row][0] == COMPUTERMOVE)
                return +10;
            else if (b[row][0] == HUMANMOVE)
                return -10;
        }
    }

    // X or O win for columns
    for (int col = 0; col < SIDE; col++) {
        if (b[0][col] == b[1][col] && b[1][col] == b[2][col]) {
            if (b[0][col] == COMPUTERMOVE)
                return +10;
            else if (b[0][col] == HUMANMOVE)
                return -10;
        }
    }

    // X or O win for diagonal
    if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
        if (b[0][0] == COMPUTERMOVE)
            return +10;
        else if (b[0][0] == HUMANMOVE)
            return -10;
    }

    if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
        if (b[0][2] == COMPUTERMOVE)
            return +10;
        else if (b[0][2] == HUMANMOVE)
            return -10;
    }

    // Else if none of them have won then return 0
    return 0;
}

// Minimax algorithm for AI move

int minimax(char board[][SIDE], int depth, bool isMax) {
    int score = evaluate(board);

    // if maximizer wins, return evaluated score
    if (score == 10)
        return score;

    // if minimizer wins, return evaluated score
    if (score == -10)
        return score;

    // if there are no more moves left whilst having no winner, it is a draw
    if (!gameover(board))
        return 0;

    // if it is the maximizer's move
    if (isMax) {
        int best = INT_MIN;

        // move all cells
        for (int i = 0; i < SIDE; i++) {
            for (int j = 0; j < SIDE; j++) {
                // check if the cell is empty
                if (board[i][j] == ' ') {
                    // Making the move
                    board[i][j] = COMPUTERMOVE;
                    // call minimax recursively and choose the maximum value possible
                    best = (best, minimax(board, depth + 1, !isMax));
                    // undoing the move
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        int best = INT_MAX;

        // move all cells
        for (int i = 0; i < SIDE; i++) {
            for (int j = 0; j < SIDE; j++) {
                // check if the cell is empty
                if (board[i][j] == ' ') {
                    // Making the move
                    board[i][j] = HUMANMOVE;
                    // call minimax recursively and choose the maximum value possible
                    best = (best, minimax(board, depth + 1, !isMax));
                    // undoing the move
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

// Coding the function to find the best move for the AI using minimax

struct Move findBestMove(char board[][SIDE]) {
    int bestPlay = INT_MIN;
    struct Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    // move all cells, evaluate minimax function, return the cell with optimal value
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            // check if the cell is empty 
            if (board[i][j] == ' ') {
                // making the move
                board[i][j] = COMPUTERMOVE;

                // Computing the evaluation set function for this move
                int movePlay = minimax(board, 0, false);

                // undoing the move
                board[i][j] = ' ';

                // if value of the current move is more than the best value, update the best
                if (movePlay > bestPlay) {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestPlay = movePlay;
                }
            }
        }
    }

    return bestMove;
}

// Coding the function to play TICTACTOE
void playTICTACTOE(int turn) {
    // Initialize a 3x3 board
    char board[SIDE][SIDE];
    int moves[SIDE * SIDE];

    // start the game
    initialization(board, moves);

    // Show instructions
    instructions();

    int moveIndex = 0, x, y;

    // playing until game has ended
    while (!gameover(board)) {
        if (turn == COMPUTERMOVE) {
            struct Move bestMove = findBestMove(board);
            board[bestMove.row][bestMove.col] = COMPUTERMOVE;
            printf("The Computer has put %c in cell %d\n", COMPUTERMOVE, bestMove.row * 3 + bestMove.col + 1);
            gameboard(board);
            moveIndex++;
            turn = HUMANMOVE;
        } else if (turn == HUMANMOVE) {
            printf("Your Nove: ");
            scanf("%d", &moveIndex);
            x = --moveIndex / SIDE;
            y = moveIndex % SIDE;
            if (board[x][y] == ' ') {
                board[x][y] = HUMANMOVE;
                gameboard(board);
                moveIndex++;
                turn = COMPUTERMOVE;
            } else
                printf("Invalid move! Please try again.\n");
        }
    }

    // If the game has ended
    if (gameover(board))
        winner(turn);
    else
        printf("It is a draw.\n");
}

// Main function
int main() {
    // Choose the first turn randomly
    srand(time(NULL));
    int turn = rand() % 2 ? COMPUTERMOVE : HUMANMOVE;
    playTICTACTOE(turn);
    return 0;
}
