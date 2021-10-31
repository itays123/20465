#define N 5

/* Booleans */
#define TRUE 1
#define FALSE 0

/* Magic square type definition */
typedef int square[N][N];

/* Scans the standard input and builds the square from N^2 given numbers 
* without any limitations on the format of them. Returns the pointer to the square.
* If there's an invalid input, the program will return NULL and output the error */
square *buildSquare(square );

/* Sums every row, column and diagon. 
* WIll return TRUE if they have the same value, false otherise */
int checkSquare(square );