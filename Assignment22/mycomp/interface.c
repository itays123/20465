#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h> /* for atof */
#include "interface.h"

static cmdtype strtocmd(char []);

static int goto_arg(char **, int);

static int var_name_validate(char *);

static char line[MAX_LINE_LENGTH];

/* Requests the user for a new input line, and collects the command from the line.
points the argument given to the function to the first non-white, non-comma character after the command.
handles the validation for the STOP command, so no invalid stop lines will be executed */
cmdtype getcmd(char **rest)
{
    char *scanRes;
    char *command;
    cmdtype result;

    printf("\n\n > ");

    scanRes = fgets(line, MAX_LINE_LENGTH, stdin);

    /* handle scanRes */
    if (scanRes == NULL) /* End of file occured */
    {
        printf("\nError: not exited using the stop command");
        return STOP;
    }

    printf("\n < %s", line);

    /* find command */
    command = strtok(line, "\t \n");
    *rest = command + strlen(command) + 1;

    if (command == NULL)
        return NONE;
    
    result = strtocmd(command);

    /* Handle special case of STOP command */
    if (result == STOP)
        return endofcmd(*rest) ? STOP : ERROR;
    
    /* point the rest pointer to the first argument */
    if (goto_arg(rest, TRUE))
        return result;
    
    return ERROR;

}

static cmdtype strtocmd(char command[])
{
    if (!strcmp(command, "read_comp"))
        return READ;
    else if (!strcmp(command, "print_comp"))
        return PRINT;
    else if (!strcmp(command, "add_comp"))
        return ADD_COMP;
    else if (!strcmp(command, "sub_comp"))
        return SUB_COMP;
    else if (!strcmp(command, "mult_comp_real"))
        return MULT_COMP_REAL;
    else if (!strcmp(command, "mult_comp_img"))
        return MULT_COMP_IMG;
    else if (!strcmp(command, "mult_comp_comp"))
        return MULT_COMP_COMP;
    else if (!strcmp(command, "abs_comp"))
        return ABS_COMP;
    else if (!strcmp(command, "stop"))
        return STOP;
    else
    {
        printf("\nError: undefined command name");
        return ERROR;
    }
}

/* Searches for a first non-white character and moves the pointer to it.
If runs into a comma before that, returns FALSE and exists the function with an error message
If doesn't find such a character, returns FALSE is well */
static int goto_arg(char **p, int firstArg)
{
    while (**p && ((**p == ' ') || (**p == '\t')))
        (*p)++;
    
    /* encountered a non-white character */
    if (!(**p) || (**p == '\n'))
    {
        /* Argument not found */
        printf("\nError: missing argument");
        return FALSE;
    }
    if (**p != ',')
        return TRUE;
    
    /* Found illegal comma */
    if (firstArg)
        printf("\nError: Illegal comma");
    else
        printf("\nError: Multiple consecutive commas");
    return FALSE;
}

/* Gets a pointer to somewhere along a string, assuming it's after the command.
in the characters between the pointer and the next comma char,
it ignores white chars and finds an argument in a desired type
Moves the pointer to beyond the comma, or to a NULL character, whichever comes first
returns TRUE if the argument is valid, FALSE otherwise */
int arg(char **rest, argtype type, void *to_assign)
{
    /* Start and end will mark the start and end of the argument string without white chars and commas */
    char *curr, *start;
    char temp_end; /* To temporarly replace the char after the argument with \0 */
    start = *rest;
    if (!goto_arg(&start, FALSE)) /* We assume that for the first arg rest is already pointing towards it */
        return FALSE; 
    for (curr = start; *curr && (*curr != ',') && !isspace(*curr); curr++)
    {
        if (type == NUMBER && !isdigit(*curr) && *curr != '.' && *curr != '-')
        {
            printf("\nError: invalid parameter - not a number");
            return FALSE;
        }
    }

    /* Assign the result, as the desired type, in the given pointer.
    Note: Curr is now pointing to the first character in the sequence which isn't a part of the arg */
    temp_end = *curr;
    *curr = '\0';

    if (type == NUMBER)
        *(double *)to_assign = atof(start);

    if (type == VARIABLE) {
        if (var_name_validate(start))
            *(char *)to_assign = *start;
        else
        {
            printf("\nError: undefined complex variable");
            return FALSE;
        }
    }
    
    *curr = temp_end;

    /* Before we return true, move the pointer to beyond the next comma or to the end of the line */
    for (; *curr && *curr != ','; curr++)
        /* Check for other arguments given without a seperating comma */
        if (!isspace(*curr))
        {
            printf("\nError: Missing comma");
            return FALSE;
        }
    
    /* Point rest to the next character (if current one is comma) or two the current (if end of string) */
    *rest = *curr ? (curr + 1) : curr;
    return TRUE;
}

/* Validates the string name of the variable. Returns a boolean value.
If name is invalid, it prints an error message to the user */
static int var_name_validate(char *start)
{
    return strlen(start) == 1 && (*start >= 'A') && (*start < 'A' + NUMBER_OF_VARIABLES);
}



/* Checks if a pointer points to the end of a command (only white chars are left),
assuming the command has more than one character before the pointer.
Edge case: if the character before the pointer is a comma, 
like in the command "read_comp A,3.5,-3," it will mark the end of command as false */
int endofcmd(char *rest)
{
    char *c;
    /* Handle comma edge case */
    if (*(rest-1) == ',')
    {
        printf("\nError: Extraneous text after end of command");
        return FALSE;
    }

    for (c=rest; *c; c++)
        if (!isspace(*c))
        {
            printf("\nError: Extraneous text after end of command");
            return FALSE;
        }
    
    return TRUE;
}