#include "magic.h"

int main() {
    square sq;
    int sum;
    if (buildSquare(sq)) {
        printSquare(sq);
        sum = checkSquare(sq);
        if (sum) 
            printf("\nThe given square is a magic square! (Sum of each row, column and digaon: %d)\n", sum);
        else
            printf("\nThe given square is not a magic square:( \n");
    }
    return 0;
}

/* Gets and validates N^2 numbers from the user, and arranges it in the array */
int buildSquare(square sq)
{
    int *p = *sq;
    int scanRes;
    printf("\nPlease enter %d integers to build the magic square, separated by spaces (^d to stop):\n", N * N);
    while ((scanRes = scanf("%d", p)) != EOF && scanRes)
    {
        if (p >= *sq + N*N) 
        {
            /* Too much input */
            printf("\nError: too much integers were inputted.\n");
            return FALSE;
        }
        /* move p forward */
        p++;
    }
    /* Nothing in the input anymore - why did we get out of the loop? */
    if (!scanRes) /* Non-integer input was received */
    {
        printf("\nError: non-integer input was received\n");
        return FALSE;
    }
    if  (scanRes == EOF && p < *sq + N*N)
    {
        printf("\nError: not enough numbers in the input\n");
        return FALSE;
    }
    return TRUE;
}

/* Prints the square in a nice N * N format */
void printSquare(square sq)
{
    int i, j; /* Iterators */
    printf("\nThe square you entered is: \n");
    for (i=0; i<N; i++)
    {
        for (j=0; j<N; j++)
            printf("%d\t", sq[i][j]);
        printf("\n");
    }
}

/* Sums and compares each row, column and diagon of a N*N square, assuming it's valid. 
* Returns NULL if the sums aren't equal */
int checkSquare(square sq)
{
    int i,j; /* Iterators */
    int sum, curr;
    int currRowSum, currColSum, mainDiagSum, secDiagSum;

    sum = currRowSum = currColSum = mainDiagSum = secDiagSum = 0;
    for (i=0; i<N; i++)
    {
        for (j=0; j<N; j++)
        {
            curr = sq[i][j];
            /* check if current value is in the range 1-N^2 */
            if (curr < 1 || curr > N * N)
                return FALSE;
            /* Add values to sums */
            currRowSum += curr;
            currColSum += sq[j][i];
            if (j == i)
                mainDiagSum += curr;
            if (j == N - i - 1)
                secDiagSum += curr;
        }
        /* sums of rows and columns are complete - compare them */
        if (!sum)
            sum = currRowSum;
        if (sum != currRowSum || sum != currColSum)
            return FALSE;
        currRowSum = currColSum = 0;
    }
    /* Sums of diagons are complete - compare them */
    if (sum != mainDiagSum || sum != secDiagSum)
        return FALSE;
    return sum;
}
