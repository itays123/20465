/* 
* Program will validate a given c code sequence of parenthesis.
*/
#include <stdio.h>

#define maxRowLen 100
#define false 0
#define true 1
#define commentMarker #
#define rowEndMarker 101

/* Add a char to a row in a specified length.
* Ignores white chars.
* returns the new row length. If line ends, will return 101 (max row length is 100) */
int addCharToRow(char, char[], int);

/* Prints a formatted message to the user */
void notifyLineBalanced(int , char [], int );

/* Prints a formatted message to the user */
void notifyTextBalance(int );

/* Checks if a line has a single { or } */
int checkSingleBraket(char []);

/* Checks if a line is balanced. 
* Handle differently if line starts with a comment */
int checkLineBalance(char [], int );

int main() {
    char currentRow[maxRowLen];
    int currentRowLength;

    return 0;
}