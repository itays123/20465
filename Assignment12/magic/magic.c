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

