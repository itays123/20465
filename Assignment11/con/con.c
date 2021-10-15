/*
* Program will recieve a string from the user and contract it
*/
#include <stdio.h>
#define maxStrLength 81 /* 80 characters + '\0' */

/* a function that contracts the string in the first parameter and places the contracted string in the second */
void contract(char [], char []);

int main() {
    char inputStr[maxStrLength];
    char contractedStr[maxStrLength];

    printf("\nPlease enter a string to contract: \n");
    fgets(inputStr, maxStrLength, stdin);
    contract(inputStr, contractedStr);

    printf("\nContracted the string - %s", inputStr);
    printf("\n to string - %s ", contractedStr);

    return 0;
}
