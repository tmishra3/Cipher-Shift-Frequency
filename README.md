# Cipher-Shift-Frequency

The purpose of this program is to allow the user to enter a string of text
which has been encoded with a cipher shift. Then, the program will calculate
the frequencies of the entered text and compare it with the frequencies of
the standard alphabet using ciphers ranging from 0 to 25. The errors for each
cipher will be calculated and the cipher with the least error will be the
supposed cipher used to encode the text. The text will then be decoded using
that cipher and the text will be displayed on screen.The way the program works
is that first the text that the user has inputted is stored into cipherText,a
global variable array. While the text is being stored into cipherText, the
letters, uppercase or lowercase, are counted and each instance of each letter
results in an increment in the NUM_LETTERS array. For example, if 'a' or 'A'
is detected, then location 0 of the NUM_LETTERS array is incremented. Once all
the text has been entered, there is a new array created within main of 26
spaces. This array will store the error calculated by the given calcError()
function for keys 0 t 25. For example, the error that we obtain if our key is
5 is stored into spot 4 of the new array that we created. After all the errors
are calculated, another for loop is used to calculate which error was the
smallest. The location at which the smallest error occurs is essentially the
key and is then stored into estimatedKey.From there, we invoke the function
named printPlainText(). The printPlainText function uses the key that we
found within the main function and uses cipherText to print out the actual
decoded message. It does this by subtracting the key from each element of
cipherText that is a letter. However, sometimes we may subtract a number from a
letter and it will end up being "less" than the letter. In this case, we have
to wrap around the letter.If the element is not a letter, it is simply printed
out as is. 
