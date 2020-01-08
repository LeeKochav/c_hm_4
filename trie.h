#ifndef _TRIE_H_
#define _TRIE_H_

#define NUM_LETTERS ((int)26)

typedef enum{FALSE=0, TRUE=1} boolean;

typedef struct Node
{
    char letter;
    long unsigned int count;
    struct Node* children[NUM_LETTERS];
    boolean wordEnd;

}Node;

typedef struct Trie
{
    Node* head;

}Trie;

Trie* initTrie();
Node* newNode(char letter);
void add(Trie* root, char word[],int sizeWord);
void print(Trie* root);
void printR(Trie* root);
void printNode(Node* node, char str[], int index);
void printNodeR(Node* node, char str[], int index);
int getWord(char w[]);
void trieFree(Trie* root);
void nodeFree(Node* node);


#endif