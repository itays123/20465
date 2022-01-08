#include "firstpass.h"
#include "command.h" /* For every method in the module */
#include "charsequence.h" /* For every method in the module */
#include "symbols.h" /* For add_symbol, add_extern_symbol */

#define EXECUTE(status, func) \
    if ((status = func) != PASS) \
        return status;

/* Process a single line. Return an input status */
static input_status fpass_process_line(char *, word **, int *, int *, int *, table *);

boolean first_pass(FILE *src, char *filename, 
    word **code_image, int *ic, int *data_image, int *dc, table *symbols_table)
{
    boolean is_success = TRUE;
    int line_num;
    char line[MAX_LINE_LENGTH];
    input_status status;
    for (line_num = 1; fgets(line, MAX_LINE_LENGTH, src) != NULL; line_num++)
    {
        status = fpass_process_line(line, code_image, ic, data_image, dc, symbols_table);
        if (!passed(status)) /* Not PASS or a warning */
            is_success = FALSE;
        if (status != PASS) /* Error or warning. Notify user */
        {
            printf("%s%s:%d - %s", filename, ASSEMBLY_POST_MACRO_POSTFIX, line_num, get_error(status));
            status = PASS; /* Restore state */
        }
    }
    return is_success;
}

/*************** Method declarations for processing a line **********/

/* Get two pointers to the start and end of the opword,if it starts with a dot and not entry or extern,
as well as the data image and the current data counter.
process a .string or .data instruction, return any input status stumbed upon */
static input_status process_instruction(char *, char *, int *, int *);

/* Get two pointers to the start and end of the opword, if not starts with a dot.,
as well as the code image and the current instruction counter.
process it as much as possible (add any words except for symbol references), return any input status stumbed upon */
static input_status process_operation(char *, char *, word **, int *);

/* Check the grammar of a line containing .entry or .extern instruction
redirect the last two pointers to point to the start and end of the symbol.
return any input status stumbed upon */
static input_status check_entry_extern_inst(char *, char *, char **, char **);

static input_status fpass_process_line(char *line, word **code_image, int *ic, 
    int *data_image, int *dc, table *symbols_table)
{
    input_status status;
    char *label_start_maybe, *label_end_maybe, *opstart, *opend, *symb_start, *symb_end;
    boolean label_exists;
    int label_points_to;
    symbol_purpose label_purpose;

    /* Find label & opword */
    label_start_maybe = next_nonwhite(line);
    label_end_maybe = next_white_or_colon(label_start_maybe);
    label_exists = find_opword(label_start_maybe, label_end_maybe, &opstart, &opend);

    /* Find line purpose and redirect */
    if (str_equal(opstart, opend, ".entry"))
    {
        EXECUTE(status, check_entry_extern_inst(opstart, opend, &symb_start, &symb_end))
        /* Do nothing. Entry instructions will be handles in the second pass */
        return label_exists ? WARN_LABEL_TO_ENTRY : PASS;
    }

    if (str_equal(opstart, opend, ".extern"))
    {
        EXECUTE(status, check_entry_extern_inst(opstart, opend, &symb_start, &symb_end))
        /* Valid extern instruction. Add it */
        EXECUTE(status, add_extern_symbol(symbols_table, symb_start, symb_end))
        return label_exists ? WARN_LABEL_TO_EXTERN : PASS;
    }

    if (*opstart == '.') /* Another instruction */
    {
        label_points_to = *dc;
        label_purpose = DATA;
        EXECUTE(status, process_instruction(opstart, opend, data_image, dc))
    }
    else /* Operation */
    {
        label_points_to = *ic;
        label_purpose = CODE;
        EXECUTE(status, process_operation(opstart, opend, code_image, ic))
    }

    /* Line was handles. Add label to the symbol table if needed */
    if (label_exists)
        EXECUTE(status, add_symbol(symbols_table, label_start_maybe, label_end_maybe, label_purpose, label_points_to))
    return PASS;
}

static input_status process_instruction(char *opstart, char *opend, int *data_image, int *dc)
{
    char *str, *argstart, *argend, *curr_char;
    int curr_arg;
    input_status status;

    if (str_equal(opstart, opend, ".data"))
    {
        str = next_nonwhite(opend);
        if (!(*str))
            return NO_NUMBERS_FOR_DATA_INST;
        if (*str == ',')
            return ILLEGAL_COMMA_AFTER_INST;
        
        while (*str)
        {
            EXECUTE(status, find_operand(&str, &argstart, &argend, EXPECTED_NUMBER_AFTER_COMMA))
            if (!str_to_int(argstart, argend, &curr_arg))
                return INVALID_OPERAND_NOT_NUMBER;
            data_image[(*dc)++] = curr_arg;
        }
        if (*argend == ',')
            return EXPECTED_NUMBER_AFTER_COMMA;
        EXECUTE(status, end_of_command(*argend))
        return PASS;
    }
    
    if (str_equal(opstart, opend, ".string"))
    {
        argstart = next_nonwhite(opend);
        if (!(*argstart))
            return STRING_INST_EXPECTS_OPERAND;
        if (*argstart != '"')
            return STRING_MUST_BEGIN_WITH_QUOT;

        argend = next('"', argstart);
        if (!(*argend))
            return STRING_MUST_END_WITH_QUOT;
        
        for (curr_char = argstart + 1; curr_char < argend; curr_char++)
            data_image[(*dc)++] = *curr_char;
        /* Terminate with 0 */
        data_image[(*dc)++] = '\0';
        return PASS;
    }

    return UNREC_INSTRUCTION;
}