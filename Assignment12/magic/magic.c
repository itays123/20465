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

/* Gets and validates N^2 numbers from the user, and arranges it in the array */
int buildSquare(square sq)
{
    int rowsFilled = 0, valuesInRowFilled = 0, scanRes, current;
    printf("Please enter %d integers to build the magic square, separates by spaces", N * N);
    while (rowsFilled < N
        && (scanRes = scanf("%d", &current)) != EOF
        && scanRes != 0)
    {
        /* There is a number to recieve in the input - put it in the right index of sq */
        sq[rowsFilled][valuesInRowFilled] = current;
        /* Move the indexes forward */
        if((++valuesInRowFilled) == N)
        {
            rowsFilled++;
            valuesInRowFilled = 0;
        }
    }
    /* Nothing in the input anymore - why did we get out of the loop? */
    if (scanRes == 0) /* Non-integer input was received */
    {
        printf("Error: non-integer input was received");
        return FALSE;
    }
    if  (scanRes == EOF && rowsFilled < N)
    {
        printf("Error: not enough numbers in the input");
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
            return 0;
        currRowSum = currColSum = 0;
    }
    /* Sums of diagons are complete - compare them */
    if (sum != mainDiagSum || sum != secDiagSum)
        return 0;
    return sum;
}
