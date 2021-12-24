#include <stdio.h>
#include "../assembler/charsequence.h"

int main()
{
    char line[] = "label: operation 123, op2";
    char *colon, *non_alnum, *opstart, *opend, *digit, *num_end, *comma;
    
    puts(line);
    colon = next_white_or_colon(line); /* : */
    printf("\nnext white or colon: `%s`, extected :", colon);
    non_alnum = next_non_alnum(line); /* : */
    printf("\ncheck: next non alnum: `%s`, expected :", non_alnum);

    opstart = next_nonwhite(colon + 1); /* o */
    printf("\nnext non white: `%s`, expected o", opstart);
    opend = next_white(opstart); /* SPACE */
    printf("\nnext white or comma: `%s`, expected SPACE", opend);

    digit = next_nonwhite(opend + 1); /* 1 */
    printf("\nnext non white: `%s`, expected 1", digit);
    num_end = next_non_digital(digit); /* , */
    printf("\nnext non digital: `%s`, expected ,", num_end);
    comma = next_white_or_comma(digit); /* , */
    printf("\ncheck: next white or comma: `%s`, expected ,", comma);

    return 0;
}