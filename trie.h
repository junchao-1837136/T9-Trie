// Copyright 2021 Carolina Sawyer & Jun Chao
// Carolina Sawyer & Jun Chao
// sawyercm & junchao
// CSE 374
// 12/02/2021
// Homework #5

#ifndef _TRIE
#define _TRIE
#define NUM_CHILDREN 10 // 2 - 9 correspond to possible digits, 10 corresponds to #

typedef struct TrieNode {
    char* word;
    struct TrieNode* children[NUM_CHILDREN];
} TrieNode;

typedef struct Trie {
    TrieNode* root; 
} Trie;

// Makes TrieNode* with children initialized to null
TrieNode* makeNode();

// Inserts node into trie with given word and returns key sequence corresponding
// to the word, if word is in trie already just returns key sequence
int node_insert(TrieNode *prev_node, char* word, int letter_index);

// Converts a letter to corresponding t9 digit
int letter_to_digit(char letter);

// Frees up memory allocated for trie
void delete_node(TrieNode* trie);

// Given a root node and key sequence returns the corresponding word in trie
char* search_node(TrieNode* trie, char* str);

#endif