#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h> /* for atof */
#include "interface.h"

char line[MAX_LINE_LENGTH];

cmdtype getcmd(char **rest)
{
    int scanRes;
    char *command;
    cmdtype result;
    /* if EOF, return stop */
    printf("\n\t>");

    scanRes = fgets(line, MAX_LINE_LENGTH, stdin);

    /* handle scanRes */

    /* find command */
    command = strtok(line, "\t \n");
    *rest = command + strlen(command) + 1;

    if (command == NULL)
        return NONE;
    
    result = strtocmd(command);
    /* Handle special case of STOP command */
    if (result == STOP && !endofcmd(*rest))
        return ERROR;
    
    return result;

}