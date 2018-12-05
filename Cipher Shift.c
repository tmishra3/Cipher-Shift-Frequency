//Written by Tanmay Mishra
//Class Assignment for ECE 190 in 2010

/*Header file declarations. You may not include any additional header files*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE         200000
#define NUM_LETTERS     26

/* 
Global variable Declarations. 
You may not include any additional global variables 
*/
int cntLetters[NUM_LETTERS], totalLetters; 
char cipherText[BUFSIZE]; 
/* You may not modify the table[] global variable */ 
const float table[] = {/* letter frequency table */
        0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 
        0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 
        0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987, 
        0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150, 
        0.01974, 0.00074}; 
int estimatedKey; 
float minimumError; 

void PrintMsg(int num);/*Function Prototype declaration.*/
void Count();/*Function Prototype declaration.*/
float calcError(int offset);/*Function Prototype declaration.*/
void printPlainText();/*Function Prototype declaration.*/

/* You may not modify the PrintMsg function */

void PrintMsg(int num) {
        int i; 

        switch(num) {
                case 0: 
                        printf("Please enter cipher text: "); 
                        fflush(stdout); 
                        break; 
                case 1: 
                        printf("Letter frequency table: \n"); 
                        for(i=0; i<NUM_LETTERS; i++) 
                                printf("%c - %f\n", ('a'+i), 
                                        ((float)cntLetters[i])/
                                        ((float)totalLetters)); 
                        break; 
                case 2: 
                        printf("Estimated key = %d\n", estimatedKey); 
                        break; 
                case 3: printf("Estimation error = %f\n", minimumError); 
                        break; 
                case 4: printf("Plain text: \n"); 
                        break; 
                default: 
                        fprintf(stderr, "Error - unknown message number.\n");
                        break; 
        }/* switch */

}/* function PrintMsg */

/* You may not modify the calcError function */

float calcError(int offset) {
        int i; 
        float accum=0.0, temp; 

        for(i=0; i<NUM_LETTERS; i++) {
                temp = ((float)cntLetters[i] / 
                        (float) totalLetters) - 
                        table[(i+(NUM_LETTERS-offset))%NUM_LETTERS]; 
                accum += temp*temp; 
        }/* for */

        return accum; 
}/* function calcError */

void printPlainText() {

        char decipherText[BUFSIZE]; /*Stores the deciphered text.*/
        int cycle_char; /*Used as a counter for the for loop*/
        char temp3; /*Stores the char at cipherText minus the key.*/
        char temp4;/*Stores simply the char at cipherText.*/
        int length = strlen(cipherText);/*Computes the length of the text
entered into cipherText*/

        for (cycle_char=0; cycle_char<length; cycle_char++)/*Cycling through
the length of cipherText.*/
        {
                if (((cipherText[cycle_char]>='a') && 
                (cipherText[cycle_char]<='z')) || 
                ((cipherText[cycle_char]>='A') && 
                (cipherText[cycle_char]<='Z')))/*If the char read is any letter
, whether upper or lower case.*/
                {

                        temp3 = cipherText[cycle_char]-estimatedKey;
                        temp4 = cipherText[cycle_char];/*Store the char minus
the key and the char itself into the respective two variables.*/

                        if ((temp4>='a')&&(temp4<='z'))/*If the char read is a
lowercase character.*/
                        {

                                if (temp3>='a')/*If the respective char minus
the key stays within 'a' to 'z', then simply store the char-key to decipher
Text.*/
                                        decipherText[cycle_char] = temp3;
                                else/*However, if it is not in the range of 'a'
to 'z', then "wrap" the text around.*/
                                {
                                        temp3 = cipherText[cycle_char]+
                                        (26-estimatedKey);
                                        decipherText[cycle_char] = temp3;
                                }

                        }

                        if ((temp4>='A')&&(temp4<='Z'))/*If the char read is an
uppercase character.*/
                        {

                                if (temp3>='A')/*If the respective char minus
the key stays within 'A' to 'Z, then simply store the char-key to decipher
Text.*/
                                        decipherText[cycle_char] = temp3;
                                else/*However, if it is not in the range of 'A'
to 'Z', then "wrap" the text around.*/
                                {
                                        temp3 = cipherText[cycle_char]+
                                        (26-estimatedKey);
                                        decipherText[cycle_char] = temp3;
                                }

                        }

                }
                else
                {
                        decipherText[cycle_char] = cipherText[cycle_char];
                }
        }

        PrintMsg(2);/*Print the key.*/
        PrintMsg(4);/*Print "Plain Text."*/

        for (cycle_char=0; cycle_char<length; cycle_char++)
        {
                printf("%c", decipherText[cycle_char]);/*Printing the contents
of decipherText from start to finish to print out the entire decrypted string.
*/
        }

        printf ("\n");/*Produce a newline after.*/


}/* function printPlainText */

void Count() {
        char alphabet[27]="abcdefghijklmnopqrstuvwxyz"; /*I am defining an
array that will sequentially store abcdef...to z. The first space, space 0,
denotes a while the second space, space 1, denotes b.What i am planning to
do is to match the inputted char to one char in the alphabet array. Whichever
space I match the inputted char to the alphabet array, that space will be the
space in cntLetters that I increment by 1.*/

        int spot=0, user_char=0, k=0; /*Integer Spot will be used as a counter
to cycle through the alphabet array. Int user_char  will be the input char that
is taken in. We can define it as an int because it is*/


        while ( ( user_char = getchar() ) != '\n' ) /*While the input stored to
the user_char is not equal enter or newline, keep on processing one char at a
time.*/
        {
                cipherText[k] = user_char;/*Adding the character we
have encountered into cipherText sequentially.*/

                k++;/*Our sentinel counter which will take care of the location
at which our char is to be stored in cipherText.*/

                if (( user_char >= 'a'  ) && ( user_char <= 'z' )) /*While the
char that is iputted is in the range of a to z inclusive,do the tasks enclosed
within the if.*/
                {
                        for (spot=0; spot<=25; spot++) /*Cycling through spot
from 0 to 25 so we can compare the user_char to each element in alphabet.*/
                        {
                                if (user_char==alphabet[spot]) /*Comparing the
input_char to the current char being read in alphabet.*/
                                {
                                        ++cntLetters[spot]; /*if a match is
found, add 1 to spot at which we found a match in cntLetters. For example, if
our input_char is 'c', we need to match 'c' to 'c' in alphabet - which is at
space 2 in alphabet. The+refore, since spot is 2, we will increment space 2 in
cntLetters by 1.*/
                                         break;
                                }

                        }
                }
                if (( user_char >= 'A'  ) && ( user_char <= 'Z' ))
                {
                        char capA = 'A';/*Comparing the capital chars in a
different way. Here, I will be subtracting the current character minus A to
get the offset.*/
                        int difference = user_char - capA;              

                        ++cntLetters[difference];
                }
                if ((user_char>='a' && user_char<='z') 
                || (user_char>='A' && user_char<='Z')) 
                /*Spaces do not count in the totalletters
so we are excluding them.*/
                {
                        totalLetters++; /*Increment totalLetters by 1 if the
inputted char is not a space.*/
                }
        }


}/* function Count */

int main(int argc, char *argv[]) {

        float key_error[26]; /*Will store the errors for each offset.*/

        PrintMsg(0); /*Call the PrintMsg function with inputs 0 that allow it
to run a case with the decision decided by 0, which is to print a message and
ask the user to input text.*/

        Count(); /*Calls the count function. Explained in more detail within
the function itself.*/

        PrintMsg(1); /*Calls the PrintMsg function with inputs 1 which allows
it compute the frequency of each letter and display it on the screen for the
user.*/
        int cycle; /*Used as a counter.*/

        for (cycle=0; cycle<=25; cycle++)
        {
                key_error[cycle]=calcError(cycle);/*Store the error resulting
from each offset into the resulting location of the offset. For example, error
for offset 0 stored in location 0 of key_error and error for offset 5 stored
in location 5 of key_error.*/
        }

        float least_error = key_error[0];/*This variable will store the least
error encountered.*/

        int offset_num = 0;/*This variable will store the location of the least
error, which effectively allows it to store the key for the offset since each
location corresponds to the key.*/

        for (cycle=0; cycle<=25; cycle++)/*This for loop cycles through the
code and looks for the smallest key. The initial key that is stored as the
smallest is the key at location 0. If anything smaller is encountered, it is
stored within offset_num and repeatedly is changed if something even smaller
is encountered.*/
        {
                if (key_error[cycle]<least_error)
                {
                        least_error = key_error[cycle];
                        offset_num = cycle;
                }
        }

        estimatedKey = offset_num;/*Once we have isolated the smallest error
,its location is stored at offset_num and that is the key which can then be
stored within estimatedKey.*/

        minimumError = key_error[estimatedKey];/*Stores the actual error of the
estimatedKey.*/

        printPlainText();/*Calls the printPlainText function so we can start to
decode the text.*/

        return 0;

}/* function main */