#include "interface.h"
#include "mycomp.h"

static complex *variables[NUMBER_OF_VARIABLES];

int main() {
    char *rest;
    cmdtype cmd;
    char chararg1, chararg2;
    double numarg1, numarg2;
    while((cmd = getcmd(&rest)) != STOP)
    {
        switch (cmd)
        {
            case READ:
                if (arg(&rest, VARIABLE, &chararg1)
                    && arg(&rest, NUMBER, &numarg1)
                    && arg(&rest, NUMBER, &numarg2)
                    && endofcmd(rest))
                    read_comp(get_variable(chararg1), numarg1, numarg2);
                break;
            case PRINT:
                if (arg(&rest, VARIABLE, &chararg1)
                    && endofcmd(rest))
                    print_comp(get_variable(chararg1));
                break;
            case ADD_COMP:
                if (arg(&rest, VARIABLE, &chararg1)
                    && arg(&rest, VARIABLE, &chararg2)
                    && endofcmd(rest))
                    add_comp(get_variable(chararg1), get_variable(chararg2));
                break;
            case SUB_COMP:
                if (arg(&rest, VARIABLE, &chararg1)
                    && arg(&rest, VARIABLE, &chararg2)
                    && endofcmd(rest))
                    subtract_comp(get_variable(chararg1), get_variable(chararg2));
                break;
            case MULT_COMP_REAL:
                if (arg(&rest, VARIABLE, &chararg1)
                    && arg(&rest, NUMBER, &numarg1)
                    && endofcmd(rest))
                    mult_comp_real(get_variable(chararg1), numarg1);
                break;
            case MULT_COMP_IMG:
                if (arg(&rest, VARIABLE, &chararg1)
                    && arg(&rest, NUMBER, &numarg1)
                    && endofcmd(rest))
                    mult_comp_img(get_variable(chararg1), numarg1);
                break;
            case MULT_COMP_COMP:
                if (arg(&rest, VARIABLE, &chararg1)
                    && arg(&rest, VARIABLE, &chararg2)
                    && endofcmd(rest))
                    mult_comp_comp(get_variable(chararg1), get_variable(chararg2));
                break;
            case ABS_COMP:
                if (arg(&rest, VARIABLE, &chararg1)
                    && endofcmd(rest))
                    abs_comp(get_variable(chararg1));
                break;
            default: /* Undefined command name or error accured */
                break;
        }
    }

    return 0;
}