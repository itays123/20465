/* 
* Program will validate a given c code sequence of parenthesis.
*/
#include <stdio.h>

#define maxRowLen 100
#define FALSE 0
#define TRUE 1
#define START_OF_BLOCK '{'
#define END_OF_BLOCK '}'

/* Add a char to a row in a specified length.
* Ignores white chars.
* returns the new row length. If line ends, will return 101 (max row length is 100) */
int addCharToRow(char, char[], int);

/* Prints a formatted message to the user */
void notifyLineBalanced(int , char [], int );

/* Prints a formatted message to the user depending on the input */
void notifyTextBalance(int , int );

/* Checks if a line has a single { or }, and returns TRUE/FALSE*/
int isStartOfBlock(char []);
int isEndOfBlock(char []);

/* Checks if a line is balanced. 
* Returns TRUE if line is balanced, FALSE otherwise (excluding block start/end) */
int checkLineBalance(char []);

/* GLOBAL VARIABLES */
int insideComment = FALSE; /* Handles the special case of multi-line comments */

int main() {
    char currentRow[maxRowLen];
    int currentRowLength;
    int blockDepth = 0; /* Handles the special case of implanced "{" and "}" lines */
    int anyImbalanced = FALSE; /* Will change to TRUE if an imbalanced line, that does not start\end a block, will be found */
    int currentLineBalanced;
    
    notifyTextBalance(anyImbalanced, blockDepth);
    return 0;
}

/* Add a char to a row in a specified length.
* Ignores white chars.
* returns the new row length. If line ends, will return 101 (max row length is 100) */
int addCharToRow(char ch, char row[], int rowLength) {
    switch (char)
    {
    case ' ':
    case '\t':
        return rowLength; /* Ignoring white char functionality - return everything as is */
    
    case '\n':
        row[rowLength] = '\0'; 
        return maxRowLen + 1; /* Notify the caller that a line has ended */
    
    default:
        row[rowLength] = ch;
        return rowLength + 1; /* Default case - add char to row */
    }
}

/* Prints a formatted message to the user */
void notifyLineBalanced(int lineNum, char line[], int isBalanced) {
    printf("Line %d: `%s` - ", lineNum, line);
    if (isBalanced)
        puts("balanced.");
    else
        puts("IMBALANCED!")
}

/* Prints a formatted message to the user depending on the input. 
* A text is imbalanced if either of lines is imbalanced (excluding block start/end), or if block depth is imbalanced */
void notifyTextBalance(int anyImbalanced, int blockDepth) {
    if (anyImbalanced || blockDepth != 0) 
        printf("Your code is imbalanced");
    else
        printf("Your code is well balanced. Good Job!");
}

/* Checks if a line has a single { in the beginning, assuming white chars are already missing */
int isStartOfBlock(char row[]) {
    if (row[0] == START_OF_BLOCK)
        return TRUE;
    return FALSE;
}

/* Checks if a line has a single } in the beginning, assuming white chars are already missing */
int isEndOfBlock(char row[]) {
    if (row[0] == END_OF_BLOCK)
        return TRUE;
    return FALSE;
}

/* Checks if a line is balanced. 
* Returns TRUE if line is balanced, FALSE otherwise (excluding block start/end) */
int checkLineBalance(char row[]) {
    char parenthesisCharacters[maxRowLen];
    int currentPosition = 0; /* If position !=0 at the end, it means that there are unclosed parenthesis. */
    int insideString = FALSE;
    int i;

    for (i=0; row[i]; i++) {
        switch (row[i])
        {
            /* Check start of comment */
            case '*': 
                if (i>=1 && row[i-1] == '/')
                    insideComment = TRUE;
                break;
            
            /* Check end of comment */
            case '/':
                if (i>=1 && row[i-1] == '/')
                    insideComment = FALSE;
                break;
            
            /* Check start/end of string */
            case '"':
                if (insideString)
                    insideString = FALSE;
                else
                    insideString = TRUE;
                break;
            
            /* Check parenthesis start */
            case '{': /* Excluding start/end of block */
            case '[':
            case '(':
                if (!insideComment && !insideString) {
                    parenthesisCharacters[currentPosition] = row[i];
                    currentPosition++;
                }
                break;
            
            /* Check parenthesis end */
            case '}': /* Excluding start/end of block */
            case ']':
            case ')':
                if (!insideComment && !insideString) {
                    if (currentPosition = 0 /* No opening parenthesis at all */) 
                        return FALSE;
                    if ((row[i] == '}' && parenthesisCharacters[currentPosition-1] != '{')
                        || (row[i] == ']' && parenthesisCharacters[currentPosition-1] != '[')
                        || (row[i] == ')' && parenthesisCharacters[currentPosition-1] != '('))
                        return FALSE;
                    
                    /* Everything is OK, closing bracket is matching */
                    currentPosition--;
                }
                break;
            
            default:
                break;
        }
    }

    if (currentPosition != 0) /* There are opening parenthesis with no closing */
        return FALSE;
    return TRUE;
}