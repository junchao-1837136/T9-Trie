// Copyright 2021 Carolina Sawyer & Jun Chao
// Carolina Sawyer & Jun Chao
// sawyercm & junchao
// CSE 374
// 12/02/2021
// Homework #5

// Creates a trie for t9 and runs interactive program with user
// user types in a key sequence and a word is returned if found
// in the provided dictionary

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h> 
#include "trie.h"

#define MAX_WORD_SIZE 50

int main(int argc, char **argv);

void usage(char* program);

int main(int argc, char **argv) {
    // check arguments
    if (argc != 2) {
        usage(argv[0]);
    }
    char* dictionary = argv[1]; // dictionary name
    FILE* text = fopen(dictionary, "r");
    if (!text) {
        fprintf(stderr, "Failed to open %s for input.\n", dictionary);
        return EXIT_FAILURE;
    }
    //insert each dictionary word into trie
    char* buffer = (char*) malloc(MAX_WORD_SIZE * sizeof(char));
    if (buffer == NULL) {
        return EXIT_FAILURE;
    }
    TrieNode* trie = makeNode();
    while(fgets(buffer, MAX_WORD_SIZE, text) != NULL) {     
        buffer[strcspn(buffer, "\n")] = '\0';
        int num = node_insert(trie, buffer, 0);
    }
    // begin interactive session
    char* input = (char*) malloc(MAX_WORD_SIZE * sizeof(char));
    if (input == NULL) {
        return EXIT_FAILURE;
    }
    printf("Enter \"exit\" to quit.\n");
    printf("Enter Key Sequence (or \"#\" for next word):\n> ");
    bool done = false;
    char* result;
    char* prevWord = (char*) malloc(MAX_WORD_SIZE * sizeof(char));
    // if more #'s entered then t9onyms print "There are no more T9onyms"
    while (!done) {
        if (fgets(input, MAX_WORD_SIZE, stdin) == NULL) {
            printf("\n");
            done = true;
        } else {
            if (sscanf(input, "%s") == 1) {
                if (strcmp(input, "exit") == 0) {
                    done = true;
                } else {
                    if (strcmp(input, "#") == 0) {
                        strncat(prevWord, input, 1);
                        result = search_node(trie, prevWord);
                        if (result == NULL) {
                            printf("There are no more T9onyms.\n");
                        } else {
                            printf("\'%s\'\n", result);
                        }
                    } else if (isdigit(input[0])) {
                        result = search_node(trie, input);
                        strcpy(prevWord, input);
                        if (result == NULL) {
                            printf("Not found in current dictionary.\n");
                        } else {
                            printf("\'%s\'\n", result);
                        }
                    }
                    printf("Enter Key Sequence (or \"#\" for next word):\n> ");
                }
            }
        }
    }
    free(prevWord);
    free(buffer);
    fclose(text);
    free(input);
    delete_node(trie);
    return EXIT_SUCCESS;
}

void usage(char* program) {
    printf("Usage: %s dictionary\n", program);
    exit(EXIT_FAILURE);
}