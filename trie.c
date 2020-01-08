#include "trie.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define WORD_SIZE 30

Trie* initTrie()
{
    Trie* root=(Trie*)malloc(sizeof(Trie));
    root->head=newNode(0);
    return root;
}

Node* newNode(char let)
{
    Node* node=(Node*)malloc(sizeof(Node));
    node->letter=let;
    for(int i=0; i<NUM_LETTERS; i++)
    {
        node->children[i]=NULL;
    }
    node->count=0;
    return node;
}

void add(Trie* root, char word[],int sizeWord)
{
    Node* curr=root->head;

    for(int i=0; i<sizeWord; i++)
    {
        char c=word[i];
        if(curr->children[c-'a']==NULL)
        {
            curr->children[c-'a']=newNode(c);
        }
        
        curr=curr->children[c-'a'];
        
    }
    curr->wordEnd=TRUE;
    curr->count++;
}

void print(Trie* root)
{
    char str[WORD_SIZE]={};

    printNode2(root->head,str,0);
}

void printNode(Node* node, char str[], int index)
{
    if(node!=NULL)
    {
    if(node->wordEnd==TRUE)
    {
        str[index]='\0';
        printf("%s \t %ld \n",str, node->count);
    }
    
    for(int i=0; i<NUM_LETTERS; i++)
    {
        if(node->children[i]!=NULL)
        {
        str[index]=i+'a';
        printNode(node->children[i],str,index+1);
        }
    }
    }
}

void printNode2(Node* node, char str[], int index)
{
    if(node!=NULL)
    {
    
    for(int i=NUM_LETTERS-1; i>=0; i--)
    {
        if(node->children[i]!=NULL)
        {
        str[index]=i+'a';
        printNode2(node->children[i],str,index+1);
        }
    }
    if(node->wordEnd==TRUE)
    {
        str[index]='\0';
        printf("%s \t %ld \n",str, node->count);
    }
    }
}


int main()
{
 
 char word[]="lee";
Trie* t=initTrie();
add(t,word,strlen(word));
add(t,"abc",3);
add(t,"abcc",4);
add(t,"abcd",5);
print(t);
    
}