#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 10         // Size of the hash table
#define MAX_INPUT 50          // Maximum length for input tokens

// Define a structure to represent a token
typedef struct Token {
    char word[20];            // The token itself (e.g., "int", "+")
    char category[20];        // Category (e.g., keyword, operator, etc.)
    struct Token* next;       // Pointer to next token in case of collision (chaining)
} Token;

Token* hashTable[TABLE_SIZE]; // Hash table to store predefined tokens

// Hash function to map token strings to indices in the hash table
int hash(char* word) {
    int sum = 0;
    for (int i = 0; word[i] != '\0'; i++)
        sum += word[i];
    return sum % TABLE_SIZE;
}

// Insert a token into the hash table
void insertToken(char* word, char* category) {
    int index = hash(word);
    Token* newToken = (Token*)malloc(sizeof(Token));
    strcpy(newToken->word, word);
    strcpy(newToken->category, category);
    newToken->next = hashTable[index];
    hashTable[index] = newToken;
}

// Search for a token in the hash table and return its category if found
char* searchToken(char* word) {
    int index = hash(word);
    Token* current = hashTable[index];
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            return current->category;
        }
        current = current->next;
    }
    return NULL; // Token not found
}

// Initialize the hash table with some predefined tokens
void initTokens() {

    insertToken("agr", "keyword");
    insertToken("wrna", "keyword");
    insertToken("jbtk", "keyword");
    insertToken("jb", "keyword");
    insertToken("wapis", "keyword");
    insertToken("void", "keyword");
    insertToken("class", "keyword");
    insertToken("sach", "keyword");
    insertToken("jhoot", "keyword");
    insertToken("wapis", "keyword");

    insertToken("int", "datatype");
    insertToken("float", "datatype");
    insertToken("double", "datatype");
    insertToken("char", "datatype");
  
    insertToken("+", "operator");
    insertToken("-", "operator");
    insertToken("*", "operator");
    insertToken("/", "operator");
    insertToken("++", "operator");
    insertToken("--", "operator");
  
    insertToken("==", "comparison operator");
    insertToken("!=", "comparison operator");
    insertToken("&&", "comparison operator");
    insertToken("||", "comparison operator");
    insertToken("<", "comparison operator");
    insertToken(">", "comparison operator");
    insertToken(">=", "comparison operator");
    insertToken("<=", "comparison operator");

    insertToken("main", "identifier"); // Reserved identifier

    insertToken(")", "syntax");
    insertToken("(", "syntax");
    insertToken("}", "syntax");
    insertToken("{", "syntax");
    insertToken(";", "syntax");
    insertToken(",", "syntax");
    insertToken("=", "syntax");
    insertToken("()", "syntax");


    
}

// Check if a string is a valid identifier (i.e., variable)
int isValidIdentifier(const char* token) {
    // Must start with a letter or underscore
    if (!isalpha(token[0]) && token[0] != '_') {
        return 0;
    }
    // All characters must be alphanumeric or underscore
    for (int i = 1; token[i] != '\0'; i++) {
        if (!isalnum(token[i]) && token[i] != '_') {
            return 0;
        }
    }
    return 1;
}

int main() {
    char input[MAX_INPUT];
    initTokens(); // Load predefined tokens into the hash table

    printf("Simple Token Validator\n");
    printf("Type 'exit' to quit.\n");

    while (1) {
        printf("\nEnter a token: ");
        scanf("%s", input);

        // Exit the loop if the user types 'exit'
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // First try to find it in the hash table
        char* category = searchToken(input);
        if (category != NULL) {
            printf("Valid token. Category: %s\n", category);
        }
        // If not found, check if it's a valid identifier
        else if (isValidIdentifier(input)) {
            printf("Valid identifier (variable).\n");
        }
        // Otherwise, it's an invalid token
        else {
            printf("Invalid token.\n");
        }
    }

    printf("Program exited.\n");
    return 0;
}
