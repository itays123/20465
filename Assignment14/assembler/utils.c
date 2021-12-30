/* Utils.c - small, useful utility functions */
#include "utils.h"
#include "stdlib.h" /* For malloc(), free(), .... */
#include "string.h" /* For strlen(), strcpy() */

void *malloc_safe(int bytes)
{
    void *result = malloc(bytes);
    if (result == NULL)
    {
        printf("Fatal: memory allocation failed");
        exit(1);
    }
    /* result is safe */
    return result;
}

char *strcat_safe(char *str1, char *str2)
{
    int length1, length2;
    char *result;
    /* malloc length1 + length2 + 1 (for \0) characters */
    length1 = strlen(str1);
    length2 = strlen(str2);
    result = malloc_safe(sizeof(char) * (length1 + length2 + 1));
    memcpy(result, str1, length1);
    memcpy(result+length1, str2, length2);
    result[length1 + length2] = '\0';
    return result;
}

FILE *fopen_safe(char *filename, char *postfix, char *permissions)
{
    char *full_filename = strcat_safe(filename, postfix);
    FILE *target = fopen(full_filename, permissions);
    free(full_filename);
    if (target == NULL)
    {
        printf("Fatal: Opening file %s failed", full_filename);
        exit(1);
    }
    return target;
}

void get_integer_hexbits(hexbits bits, int data)
{
    int i, currentMask, bitsToMove;
    /* Skip most significat hexbit - will be kept for the ARE status */
    for (i = 1; i < HEXBITS_IN_WORD; i++)
    {
        /* Calculate mask:
        1 => 0xF000, 2 => 0x0F00, 3 => 0x00F0, 4 => 0x000F */
        bitsToMove = (BITS_IN_HEXBIT * (HEXBITS_IN_WORD - 1 - i));
        currentMask = HEXBIT_MASK << bitsToMove;
        bits[i] = (data & currentMask) >> bitsToMove;
    }
}
