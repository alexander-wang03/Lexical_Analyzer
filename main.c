#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function prototypes
int isLetter(char c);
int isDigit(char c);

// Global variables
char programBuffer[80], currentToken[8]; // Buffer for input program and current token
char currentChar; // Current character being analyzed
int tokenType, bufferPointer, i, j, numberValue; // Various counters and type indicators
char *reservedWords[6] = { // List of reserved words
  "begin", "if", "then", "while", "do", "end"
};

// Main function
int main(int argc, char const *argv[]) {
    bufferPointer = 0;
    printf("\nPlease enter a string:\n");

    // Reading input into programBuffer
    do {
        currentChar = getchar();
        programBuffer[bufferPointer++] = currentChar;
    } while(currentChar != '#'); // '#' signifies the end of input

    bufferPointer = 0; // Reset buffer pointer for tokenization

    // Main tokenization loop
    do {
        // Reset current token
        for (j = 0; j < 8; j++) {
            currentToken[j] = '\0';
        }

        // Skip whitespace characters
        currentChar = programBuffer[bufferPointer++];
        while(currentChar == ' ') {
            currentChar = programBuffer[bufferPointer++];
        }

        // If current character is a letter
        if (isLetter(currentChar)) {
            i = 0;
            // Build token from letters and digits
            while(isLetter(currentChar) || isDigit(currentChar)) {
                currentToken[i] = currentChar;
                i++;
                currentChar = programBuffer[bufferPointer++];
            }
            currentToken[i] = '\0'; // Null-terminate the token
            bufferPointer--; // Move pointer back to last non-token character
            tokenType = 10; // Default token type for identifiers

            // Check if token is a reserved word
            for (j = 0; j < 6; j++) {
                if (strcmp(currentToken, reservedWords[j]) == 0) {
                    tokenType = j + 1; // Token type is set based on reserved word
                    break;
                }    
            }
        } 
        // If current character is a digit
        else if (isDigit(currentChar)) {
            numberValue = 0;
            // Convert sequence of digits to a number
            while(isDigit(currentChar)) {
                numberValue = numberValue * 10 + currentChar - '0';
                currentChar = programBuffer[bufferPointer++];
            }
            bufferPointer--; // Move pointer back to last non-token character
            tokenType = 11; // Token type for numeric constants
        } 
        else {
            // Switch-case for handling operators and symbols
			switch(currentChar) {
				// Cases for '<', '>', ':', '+', '-', '*', '/', ';', '(', ')', '#'
				case '<':
					i = 0;
					currentToken[i++] = currentChar;
					currentChar = programBuffer[bufferPointer++];
					if (currentChar == '>') {
						tokenType = 21;
						currentToken[i++] = currentChar;
					} else if (currentChar == '=') {
						tokenType = 22;
						currentToken[i++] = currentChar;
					} else {
						tokenType = 20;
						bufferPointer--;
					}
					break;
				case '+': tokenType = 13; currentToken[0] = currentChar; break;
				case '-': tokenType = 14; currentToken[0] = currentChar; break;
				case '*': tokenType = 15; currentToken[0] = currentChar; break;
				case '/': tokenType = 16; currentToken[0] = currentChar; break;
				case ';': tokenType = 26; currentToken[0] = currentChar; break;
				case '(': tokenType = 27; currentToken[0] = currentChar; break;
				case ')': tokenType = 28; currentToken[0] = currentChar; break;
				case '#': tokenType = 0;  currentToken[0] = currentChar; break;
				default: tokenType = -1;
			}
        }

        // Output based on token type
        switch(tokenType) {
            case 11: printf("(%2d, %8d)\n", tokenType, numberValue); break;
            case -1: printf("Error in input\n"); break;
            default: printf("(%2d, %8s)\n", tokenType, currentToken);
        }
    } while (tokenType != 0);

    system("pause");
    return 0;
}

// Function to check if a character is a letter
int isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// Function to check if a character is a digit
int isDigit(char c) {
    return (c >= '0' && c <= '9');
}
