// Copyright 2021 Carolina Sawyer & Jun Chao
// Carolina Sawyer & Jun Chao
// sawyercm & junchao
// CSE 374
// 12/02/2021
// Homework #5

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "trie.h"

TrieNode* makeNode() {
    TrieNode* t = (TrieNode*) malloc(sizeof(TrieNode));
    if (t == NULL) {
        return NULL;
    }
    for (int i = 0; i < NUM_CHILDREN; i++) {
        t -> children[i] = NULL;
    }
    t -> word = NULL;
    return t; 
}

int node_insert(TrieNode* prev_node, char* word, int letter_index) {
    int digit;
    if (letter_index == -1) {
        digit = 0;
    } else {
        digit = letter_to_digit(word[letter_index]);
    }
    TrieNode* curr_node;
    // create node if child is null and assign current to node
    if (prev_node -> children[digit] == NULL) {
        prev_node -> children[digit] = makeNode();
    }
    curr_node = prev_node -> children[digit];
    if (word[letter_index + 1] == '\0' || letter_index == -1) { // at the end of the word     
        if (curr_node -> word == NULL) { // current node doesn’t have a word yet
            curr_node -> word = (char*) malloc(sizeof(char) * (strlen(word) + 1));
            if (curr_node -> word == NULL) {
                return EXIT_FAILURE;
            }
            strncpy(curr_node -> word, word, strlen(word) + 1);
            return 0;
        } else if (curr_node -> word != word) {  // different word same sequence, add as #
            node_insert(curr_node, word, -1); // if letter index is -1 digit = 0
            return 0;
        } else { // word at this node is same as given word so return value
            return 0;
        }
    } else { // not at the end of the string, so continue to the next letter
        return node_insert(curr_node, word, letter_index + 1);
    }
}

int letter_to_digit(char letter) {
    int digits[26];
    int digit = 2;
    for (int i = 0; i < 26; i += 3) {
        digits[i] = digit;
        digits[i + 1] = digit;
        digits[i + 2] = digit;
        if (digit == 7 || digit == 9) {
            digits[i + 3] = digit;
            i++;
        }
        digit++;
    }
    int index = tolower(letter) - 'a';
    int letterDigit = digits[index];
    return letterDigit;
}

char* search_node(TrieNode* trie, char* str) {
    if (trie == NULL){
        return NULL;
    }
    TrieNode* curr = trie;
    int position = 0;
    while (position < strlen(str)) {
        int index;
        if (str[position] == '#') {
            index = 0;
        } else {
            char c = str[position];
            index = c - '0';
        }
        if (index == 1 || index > 9) {
            return NULL;
        }
        if (curr -> children[index] == NULL) {
            return NULL;
        } else {
            curr = curr -> children[index];
            position++;
        }
    }
    if (curr -> word == NULL) {
        return NULL;
    } else {
        return curr -> word;
    }
}

void delete_node(TrieNode* trie) {
    if (trie) {
        for (int i = 0; i < NUM_CHILDREN; i++) {
            delete_node(trie -> children[i]);
        }
        if (trie -> word != NULL) {
            free(trie -> word);
        }
        free(trie);
        trie = NULL;
    }
}
