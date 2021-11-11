
#define MAX_LINE_LENGTH 100
#define NUMBER_OF_VARIABLES 6

typedef enum { EMPTY, VARIABLE, NUMBER } argtype;

typedef enum { NONE, ERROR, READ, PRINT, ADD_COMP, SUB_COMP, MULT_COMP_REAL, MULT_COMP_IMG, MULT_COMP_COMP, ABS_COMP, STOP } cmdtype;

cmdtype getcmd(char []);

static cmdtype strtocmd(char []);

static int iswhitecharsonly(char *);

int arg_validate(char**, argtype, void*);

int arg_count_validate(char [], int );