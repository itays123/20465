/* 
* Program will validate a given c code sequence of parenthesis.
* Assertations - 
* - A line consists of 100 characters at most
* - There are no nested comments, and any comment must end
* - Any quotation mark will have a matching one in the same line.
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_ROW_LEN 101
#define FALSE 0
#define TRUE 1
#define START_OF_BLOCK '{'
#define END_OF_BLOCK '}'

/* Add a char to a row in a specified length.
* returns the new row length. If line ends, will return 101 (max row length is 100) */
int addCharToRow(char, char[], int);

/* Prints a formatted message to the user */
void notifyLineBalanced(int , char [], int );

/* Prints a formatted message to the user depending on the input */
void notifyTextBalance(int , int );

/* Handles all checks for a full row, and modifies global variables accordingly 
* Returns the result of the check. Balanced - TRUE, imbalanced (including block start/end) - FALSE*/
int checkRow(char []);

/* Checks if a line has only a character and white chars, and returns TRUE/FALSE*/
int lineContainsOnly(char [], char );

/* Checks if a line is balanced. 
* Returns TRUE if line is balanced, FALSE otherwise (excluding block start/end) */
int checkLineBalance(char []);

/* GLOBAL VARIABLES */
int insideComment = FALSE; /* Handles the special case of multi-line comments */
int blockDepth = 0; /* Handles the special case of implanced "{" and "}" lines */
int anyImbalanced = FALSE; /* Will change to TRUE if an imbalanced line, that does not start\end a block, will be found */

int main() 
{
    char currentRow[MAX_ROW_LEN];
    int currentRowLength = 0;
    char current;
    int currentLineBalanced;
    int lineNum = 1;

    printf("Please enter your code to check (^D to stop)\n");

    while((current = getchar()) != EOF) 
    {
        currentRowLength = addCharToRow(current, currentRow, currentRowLength);
        if (currentRowLength > MAX_ROW_LEN) 
        {
            currentLineBalanced = checkRow(currentRow);
            notifyLineBalanced(lineNum, currentRow, currentLineBalanced);
            currentRowLength = 0;
            lineNum++;
        }
    }

    /* Check last line my mimiking another '\n' char */
    addCharToRow('\n', currentRow, currentRowLength);
    if (currentRowLength != 0) 
    {
        currentLineBalanced = checkRow(currentRow);
        notifyLineBalanced(lineNum, currentRow, currentLineBalanced);
    }
    
    notifyTextBalance(anyImbalanced, blockDepth);
    return 0;
}

/* Add a char to a row in a specified length.
* returns the new row length. If line ends, will return 102 (max row length is 101) */
int addCharToRow(char ch, char row[], int rowLength) 
{
    switch (ch)
    {
    
    case '\n':
        row[rowLength] = '\0'; 
        return MAX_ROW_LEN + 1; /* Notify the caller that a line has ended */
    
    default:
        row[rowLength] = ch;
        return rowLength + 1; /* Default case - add char to row */
    }
}

/* Prints a formatted message to the user */
void notifyLineBalanced(int lineNum, char line[], int isBalanced) 
{
    printf("\n\t> Line %d: `%s` - ", lineNum, line);
    if (isBalanced)
        puts("balanced.");
    else
        puts("IMBALANCED!");
}

/* Prints a formatted message to the user depending on the input. 
* A text is imbalanced if either of lines is imbalanced (excluding block start/end), or if block depth is imbalanced */
void notifyTextBalance(int anyImbalanced, int blockDepth) 
{
    if (anyImbalanced || blockDepth != 0) 
        printf("Your code is imbalanced\n");
    else
        printf("Your code is well balanced. Good Job!\n");
}

/* Handles all checks for a full row, and modifies global variables accordingly
* Returns TRUE if line is balanced, FALSE otherwise (including block start/end) */
int checkRow(char row[]) 
{
    if (strlen(row) == 0) /* Empty row */
        return TRUE;
    if (lineContainsOnly(row, START_OF_BLOCK)) 
    {
        blockDepth++;
        return FALSE; 
        /* Do NOT modify anyImbalanced. Distinguish between start/end of block and truly imbalanced lines */
    }
    if (lineContainsOnly(row, END_OF_BLOCK))
    {
        blockDepth--;
        return FALSE; 
        /* Do NOT modify anyImbalanced. Distinguish between start/end of block and truly imbalanced lines */
    }
    if(!checkLineBalance(row)) 
    {
        anyImbalanced = TRUE;
        return FALSE;
    }
    return TRUE;
}

/* Checks if a line has only a character and white chars, and returns TRUE/FALSE*/
int lineContainsOnly(char line[], char ch)
{
    int i=0;

    /* Skip white chars in the beginning */
    while (isspace(line[i]))
        i++;
    
    if (strlen(line) < i) /* Skipped entire line, char not found */
        return FALSE;
    
    if (line[i] != ch) /* There is a charcater that isn't a white char and isn't the specified character */
        return FALSE;
    
    for(i++; line[i]; i++)
        if (!isspace(line[i])) /* if after the character was found there is another non-white char */
            return FALSE;
    
    return TRUE;
}

/* Checks if a line is balanced. 
* Returns TRUE if line is balanced, FALSE otherwise (excluding block start/end) */
int checkLineBalance(char row[]) 
{
    char parenthesisCharacters[MAX_ROW_LEN];
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
                    if (currentPosition == 0 /* No opening parenthesis at all */) 
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
