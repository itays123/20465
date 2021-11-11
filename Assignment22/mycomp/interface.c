#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h> /* for atof */
#include "interface.h"

cmdtype getcmd(char line[])
{
    int scanRes;
    char *command, *rest;
    cmdtype result;
    /* if EOF, return stop */
    printf("\n\t>");

    scanRes = fgets(line, MAX_LINE_LENGTH, stdin);

    /* handle scanRes */

    /* find command */
    command = strtok(line, "\t \n");
    rest = command + strlen(command) + 1;

    if (command == NULL)
        return NONE;
    
    result = strtocmd(command);
    /* Handle special case of STOP command */
    if (result == STOP && !iswhitecharsonly(rest))
        return ERROR;
    
    return result;

}