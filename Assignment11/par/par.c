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

/* Add a char to a line in a specified length.
* returns the new line length. If line ends, will return 101 (max line length is 100) */
int addCharToLine(char, char[], int);

/* Prints a formatted message to the user */
void notifyLineBalanced(int , char [], int );

/* Prints a formatted message to the user depending on the input */
void notifyTextBalance(int , int );

/* Handles all checks for a full line, and modifies global variables accordingly 
* Returns the result of the check. Balanced - TRUE, imbalanced (including block start/end) - FALSE*/
int checkLine(char []);

/* Checks if a line has only a character and white chars, and returns TRUE/FALSE*/
int lineContainsOnly(char [], char );

/****** PARENTHESIS STACK METHODS *******/

/* compares the parenthesis balance of a line with a stack
* returns TRUE if balanced, FALSE otherwise */
int checkMatchWithStack(char []);

/* Push a new value to the stack, returns the new stack position */
int pushChar(char [], int, char);

/* Checks if a given character is the closing parenthesis of the stack top, and pops it 
* returns TRUE if the character matches, FALSE otherwise */
int compareAndPop(char [], int, char);

/* Compares the previous character of a given string, in a given positon, to a given char.
* Returns TRUE if equal, FALSE if not */
int previousCharEq(char [], int, char);

/******* GLOBAL VARIABLES ********/
int insideComment = FALSE; /* Handles the special case of multi-line comments */
int blockDepth = 0; /* Handles the special case of implanced "{" and "}" lines */
int anyImbalanced = FALSE; /* Will change to TRUE if an imbalanced line, that does not start\end a block, will be found */

int main() 
{
    char currentLine[MAX_ROW_LEN];
    int currentLineLength = 0;
    char current;
    int currentLineBalanced;
    int lineNum = 1;

    printf("Please enter your code to check (^D to stop)\n");

    while((current = getchar()) != EOF) 
    {
        currentLineLength = addCharToLine(current, currentLine, currentLineLength);
        if (currentLineLength > MAX_ROW_LEN) 
        {
            currentLineBalanced = checkLine(currentLine);
            notifyLineBalanced(lineNum, currentLine, currentLineBalanced);
            currentLineLength = 0;
            lineNum++;
        }
    }

    /* Check last line my mimiking another '\n' char */
    addCharToLine('\n', currentLine, currentLineLength);
    if (currentLineLength != 0) 
    {
        currentLineBalanced = checkLine(currentLine);
        notifyLineBalanced(lineNum, currentLine, currentLineBalanced);
    }
    
    notifyTextBalance(anyImbalanced, blockDepth);
    return 0;
}

/* Add a char to a line in a specified length.
* returns the new line length. If line ends, will return 102 (max line length is 101) */
int addCharToLine(char ch, char line[], int rowLength) 
{
    switch (ch)
    {
    
    case '\n':
        line[rowLength] = '\0'; 
        return MAX_ROW_LEN + 1; /* Notify the caller that a line has ended */
    
    default:
        line[rowLength] = ch;
        return rowLength + 1; /* Default case - add char to line */
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

/* Handles all checks for a full line, and modifies global variables accordingly
* Returns TRUE if line is balanced, FALSE otherwise (including block start/end) */
int checkLine(char line[]) 
{
    if (strlen(line) == 0) /* Empty line */
        return TRUE;
    if (lineContainsOnly(line, START_OF_BLOCK)) 
    {
        blockDepth++;
        return FALSE; 
        /* Do NOT modify anyImbalanced. Distinguish between start/end of block and truly imbalanced lines */
    }
    if (lineContainsOnly(line, END_OF_BLOCK))
    {
        blockDepth--;
        return FALSE; 
        /* Do NOT modify anyImbalanced. Distinguish between start/end of block and truly imbalanced lines */
    }
    if(!checkMatchWithStack(line)) 
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

/* compares the parenthesis balance of a line with a stack
* returns TRUE if balanced, FALSE otherwise */
int checkMatchWithStack(char line[])
{
    char stack[MAX_ROW_LEN];
    int pos = 0; /* If position !=0 at the end, it means that there are unclosed parenthesis. */
    int insideString = FALSE;
    int i;

    for (i=0; line[i]; i++) 
    {
        switch (line[i])
        {
            /* Check start of comment */
            case '*': 
                if (previousCharEq(line, i, '/') && !insideString) /* Edge case of " + / + * + " combination prevented */
                    insideComment = TRUE;
                break;
            
            /* Check end of comment */
            case '/':
                if (previousCharEq(line, i, '*') && !insideString) /* Edge case of " + * + / + " combination prevented */
                    insideComment = FALSE;
                break;
            
            /* Check start/end of string */
            case '"':
                /* Edge case of " char inside comment or "\"" combination */
                if (insideComment || previousCharEq(line, i, '\\')) 
                    break;
                if (insideString)
                    insideString = FALSE;
                else
                    insideString = TRUE;
                break;
            
            /* Check parenthesis start */
            case '{': /* Excluding start/end of block */
            case '[':
            case '(':
                if (!insideComment && !insideString) 
                    pos = pushChar(stack, pos, line[i]);
                break;
            
            /* Check parenthesis end */
            case '}': /* Excluding start/end of block */
            case ']':
            case ')':
                if (!insideComment && !insideString) {
                    if (compareAndPop(stack, pos, line[i]))
                        pos--;
                    else /* No match !! */
                        return FALSE;
                }
                break;
            
            default:
                break;
        }
    }

    if (pos != 0) /* There are opening parenthesis with no closing */
        return FALSE;
    return TRUE;
}

/* Push a new value to the stack, returns the new stack position */
int pushChar(char stack[], int pos, char ch)
{
    stack[pos] = ch;
    return pos + 1;
}

/* Checks if a given character is the closing parenthesis of the stack top, and pops it 
* returns TRUE if the character matches, FALSE otherwise */
int compareAndPop(char stack[], int pos, char cmprTo)
{
    char popped;
    if (pos == 0) /* Nothing at the stack */
        return FALSE;
    popped = stack[pos-1];
    return (popped == '{' && cmprTo == '}')
        || (popped == '(' && cmprTo == ')')
        || (popped == '[' && cmprTo == ']');
}

/* Compares the previous character of a given string, in a given positon, to a given char.
* Returns TRUE if equal, FALSE if not */
int previousCharEq(char line[], int pos, char cmprTo)
{
    if (pos < 1 || pos >= MAX_ROW_LEN + 1)
        return FALSE;
    return line[pos-1] == cmprTo;
}