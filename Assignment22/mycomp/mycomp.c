#include "interface.h"
#include "mycomp.h"

static complex variables[NUMBER_OF_VARIABLES];

int main() {
    char line[MAX_LINE_LENGTH];
    char *lineptr;
    cmdtype cmd;
    char chararg1, chararg2;
    double numarg1, numarg2;
    while((cmd = getcmd(line)) != STOP)
    {
        lineptr = line;
        switch (cmd)
        {
            case READ:
                if (arg_count_validate(line, 3) 
                    && arg_validate(&lineptr, VARIABLE, &chararg1)
                    && arg_validate(&lineptr, NUMBER, &numarg1)
                    && arg_validate(&lineptr, NUMBER, &numarg2))
                    *(get_variable(chararg1)) = read_comp(numarg1, numarg2);
                break;
            case PRINT:
                if (arg_count_validate(line, 1) 
                    && arg_validate(&lineptr, VARIABLE, &chararg1))
                    print_comp(*(get_variable(chararg1)));
                break;
            case ADD_COMP:
                if (arg_count_validate(line, 2) 
                    && arg_validate(&lineptr, VARIABLE, &chararg1)
                    && arg_validate(&lineptr, VARIABLE, &chararg2))
                    add_comp(*(get_variable(chararg1)), *(get_variable(chararg2)));
                break;
            case SUB_COMP:
                if (arg_count_validate(line, 2) 
                    && arg_validate(&lineptr, VARIABLE, &chararg1)
                    && arg_validate(&lineptr, VARIABLE, &chararg2))
                    subtract_comp(*(get_variable(chararg1)), *(get_variable(chararg2)));
                break;
            case MULT_COMP_REAL:
                if (arg_count_validate(line, 2) 
                    && arg_validate(&lineptr, VARIABLE, &chararg1)
                    && arg_validate(&lineptr, NUMBER, &numarg1))
                    mult_comp_real(*(get_variable(chararg1)), numarg1);
                break;
            case MULT_COMP_IMG:
                if (arg_count_validate(line, 2) 
                    && arg_validate(&lineptr, VARIABLE, &chararg1)
                    && arg_validate(&lineptr, NUMBER, &numarg1))
                    mult_comp_img(*(get_variable(chararg1)), numarg1);
                break;
            case MULT_COMP_COMP:
                if (arg_count_validate(line, 2) 
                    && arg_validate(&lineptr, VARIABLE, &chararg1)
                    && arg_validate(&lineptr, VARIABLE, &chararg2))
                    mult_comp_comp(*(get_variable(chararg1)), *(get_variable(chararg2)));
                break;
            case ABS_COMP:
                if (arg_count_validate(line, 1) 
                    && arg_validate(&lineptr, VARIABLE, &chararg1))
                    abs_comp(*(get_variable(chararg1)));
                break;
            default: /* Undefined command name or error accured */
                break;
        }
    }

    return 0;
}