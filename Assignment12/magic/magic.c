#include "magic.h"

int main() {
    square sq;
    int sum;
    if (buildSquare(sq)) {
        printSquare(sq);
        sum = checkSquare(sq);
        if (sum) 
            printf("The given square is a magic square! (Sum of each row, column and digaon: %d)", sum);
        else
            printf("The given square is not a magic square:(");
    }
    return 0;
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
    int sum;
    int currRowSum, currColSum, mainDiagSum, secDiagSum;

    sum = currRowSum = currColSum = mainDiagSum = secDiagSum = 0;
    for (i=0; i<N; i++)
    {
        for (j=0; j<N; j++)
        {
            /* Add values to sums */
            currRowSum += sq[i][j];
            currColSum += sq[j][i];
            if (j == i)
                mainDiagSum += sq[i][i];
            if (j == N - i)
                secDiagSum += sq[i][N-i];
        }
        /* sums of rows and columns are complete - compare them */
        if (!sum)
            sum = currRowSum;
        if (sum != currRowSum || sum != currColSum)
            return NULL;
        currRowSum = currColSum = 0;
    }
    /* Sums of diagons are complete - compare them */
    if (sum != mainDiagSum || sum != secDiagSum)
        return NULL;
    return sum;
}
