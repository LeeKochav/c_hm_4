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

    printNode(root->head,str,0);
}

void printR(Trie* root)
{
    char str[WORD_SIZE]={};

    printNodeR(root->head,str,0);
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

void printNodeR(Node* node, char str[], int index)
{
    if(node!=NULL)
    {
    
    for(int i=NUM_LETTERS-1; i>=0; i--)
    {
        if(node->children[i]!=NULL)
        {
        str[index]=i+'a';
        printNodeR(node->children[i],str,index+1);
        }
    }
    if(node->wordEnd==TRUE)
    {
        str[index]='\0';
        printf("%s \t %ld \n",str, node->count);
    }
    }
}

int getWord(char w[])
{
    char c;
    int size=0;
    while(scanf("%c",&c)==1&&size<WORD_SIZE)
    {
    
        if((c=='\n')||(c=='\t')||(c==' '))
        {
            return size;
        }
        if((c>='a'&&c<='z')||(c>='A'&&c<='Z'))
        {
        if(c>='A'&&c<='Z')
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
    for(int i=NUM_LETTERS-1; i>=0; i--)
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
    while(size>0)
    {
        add(t,word,size);
        size=getWord(word);
    }
    if(argc==1)
    {
        print(t);
    }
    else if(argc==2)
    {
        if(strcmp(argv[1],"r")==0)
        {
        printR(t);
        }
    }
    trieFree(t);
    return 0;
    
}