#include "trie.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define WORD_SIZE 30

//consructor for Trie
Trie* initTrie()
{
    Trie* root=(Trie*)malloc(sizeof(Trie));
    root->head=newNode(0);
    return root;
}

//constructor for node Trie
Node* newNode(char let)
{
    Node* node=(Node*)malloc(sizeof(Node));
    node->letter=let;
    for(int i=0; i<NUM_LETTERS; i++)
    {
        node->children[i]=NULL;
    }
    node->wordEnd=FALSE;
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
            curr->children[c-'a']=newNode(c);//create new node in the trie with the word letter
        }
        
        curr=curr->children[c-'a']; //node with the word letter already exist 
        
    }
    curr->wordEnd=TRUE; //reaced the last letter of the word, update this is the last letter
    curr->count++; // word occured 
}

void print(Trie* root)
{
    char str[WORD_SIZE]={};

    printNode(root->head,str,0);
}

void printR(Trie* root)
{
    char str[WORD_SIZE]={}; // represnt the word in the tree that will be printed

    printNodeR(root->head,str,0);
}

void printNode(Node* node, char str[], int index)
{
    if(node!=NULL)
    {
    if(node->wordEnd==TRUE) //reached last word, print word
    {
        str[index]='\0';
        printf("%s \t %ld \n",str, node->count); // print word+ number of occurrences
    }
    
    for(int i=0; i<NUM_LETTERS; i++)// ascending order a-->z
    {
        if(node->children[i]!=NULL) 
        {
        str[index]=i+'a';
        printNode(node->children[i],str,index+1); //move to next letter
        }
    }
    }
}

void printNodeR(Node* node, char str[], int index)
{
    if(node!=NULL)
    {
    
    for(int i=NUM_LETTERS-1; i>=0; i--) //descending order from z-->a 
    {
        if(node->children[i]!=NULL)
        {
        str[index]=i+'a';
        printNodeR(node->children[i],str,index+1); //move to next letter 
        }
    }
    if(node->wordEnd==TRUE) //print when reached last word descending order
    {
        str[index]='\0';
        printf("%s \t %ld \n",str, node->count);
    }
    }
}

//initialize array of chars= word, within input characters
int getWord(char w[])
{
    char c;
    int size=0;
    while(scanf("%c",&c)==1&&size<WORD_SIZE) 
    {
    
        if((c=='\n')||(c=='\t')||(c==' ')) //indicated that this is the end of the word
        {
            return size;
        }
        if((c>='a'&&c<='z')||(c>='A'&&c<='Z'))
        {
        if(c>='A'&&c<='Z') //to lowercase
        {
            c=c+32;
        }
        w[size++]=c;
        }
     
    }
    return size;

}
void trieFree(Trie* root)
{
   if(root!=NULL)
   {
     nodeFree(root->head); 
   } 
   free(root); 
}

void nodeFree(Node* node)
{
    for(int i=NUM_LETTERS-1; i>=0; i--) //travese nodes in trie to release memory 
    {
        if(node->children[i]!=NULL)
        {
         nodeFree(node->children[i]);
        }
    }
    if(node!=NULL)
    {
    free(node);
    }
}

int main(int argc, char* argv[])
{
    int size;
    char word [WORD_SIZE];
    Trie* t=initTrie();
    size=getWord(word);
    while(size>0) //size=0->empty word means end of input , trie does not contain empty words.
    {
        add(t,word,size);
        size=getWord(word);
    }
    if(argc==1) // no operation in the execution program command 
    {
        print(t);
    }
    else if(argc==2) // operation appears in the execution program command 
    {
        if(strcmp(argv[1],"r")==0) //operation is valid if and only if operatopn = 'r'
        {
        printR(t);
        }
    }
    trieFree(t); //free trie memory allocation 
    return 0;
    
}