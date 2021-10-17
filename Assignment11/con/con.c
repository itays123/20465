/*
* Program will recieve a string from the user and contract it
*/
#include <stdio.h>
#define maxStrLength 81 /* 80 characters + '\0' */
#define minSequenceLength 3
#define DASH '-'

/* a function that contracts the string in the first parameter and places the contracted string in the second */
void contract(char [], char []);

/* a function that adds a given sequence to a string and returns the new string length */
int addSequenceToString(char [], int , int , char , char );

int main() {
    char inputStr[maxStrLength];
    char contractedStr[maxStrLength];

    printf("\nPlease enter a string to contract: \n");
    fgets(inputStr, maxStrLength, stdin);
    contract(inputStr, contractedStr);

    printf("\nContracted the string - %s", inputStr);
    printf("\n to string - %s \n", contractedStr);

    return 0;
}

/* contracts the string in the first parameter and places it in the second one.
* Does it by running through every character in the first string and comparing its code to the pervious one */
void contract(char s1[], char s2[]) {
    int sequenceStartIdx = 0; /* saves the position of the start index */
    int s2Length = 0; /* saves the next available cell index of s2 */
    int i;
    char prev, curr;
    curr = s1[0]; /* First character will definately be the first in the contracted string */

    for (i=1; s1[i]; i++) {
        prev = curr;
        curr = s1[i];
        if (curr != prev + 1) {
            /* current char is NOT in the same sequence as the char before. Meaning, a sequence has ended */
            s2Length = addSequenceToString(s2, s2Length, i-sequenceStartIdx, s1[sequenceStartIdx], prev);
            sequenceStartIdx = i;
        }
    }

    /* Add last sequence */
    s2Length = addSequenceToString(s2, s2Length, i-sequenceStartIdx, s1[sequenceStartIdx], curr);

    s2[s2Length] = '\0'; /* End the string */
}

/* a function that adds a given sequence to a string and returns the new string length.
* Diffrenciuates between various cases: 1 char, 2 char and 3+ char long sequences. */
int addSequenceToString(char str[], int strLength, int sequenceLength, char start, char end) {
    if (sequenceLength == 1) {
        str[strLength] = start;
        return strLength + 1;
    }

    /* There are at least 2 characters in the sequence. Add the first */
    str[strLength] = start;
    strLength++;

    /* Add a "-" if needed */
    if (sequenceLength >= minSequenceLength) {
        str[strLength] = DASH;
        strLength++;
    }

    str[strLength] = end;
    strLength++;

    return strLength;

}