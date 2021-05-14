// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 500;

// Hash table
node *table[N];

//keep track of how many words are in the file
int number_of_words = 0;




// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
   
    return false;
}

// Hashes word to a number
//this function is from https://github.com/hathix/cs50-section/blob/master/code/7/sample-hash-functions/good-hash-function.c
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;

    for (const char *ptr = word; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //open file
    FILE *dic = fopen(dictionary, "r");
    //make sure the file was open successfully
    if (dic == NULL)
    {
        return false;
    }
    
    //create a string that will store the word in temperaraly
    char wordtemp[LENGTH + 1];
    //iterate throught the file reading every char
    while (fscanf(dic, "%s", wordtemp) != EOF)
    {

        //Keep track of how many words are in the file
        number_of_words++;

        //create a node for this word
        node *temp = malloc(sizeof(node));
        //make sure mallac allecated memory
        if (temp == NULL)
        {
            fclose(dic);
            return false;
        } 
   
        //store the word in the new node
        strcpy(temp->word, wordtemp);
        
        //call on hash
        int index = hash(wordtemp);
            
        //make the node point to the same address as the node in the array
        
        temp->next = table[index];
        //take the node of the array and make it point to the new node
        table[index] = temp;
            
        

    }
    
    //close file
    fclose(dic);
    //end function
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return number_of_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *temp = table[i];
        
        while (cursor != NULL)
        {
            
            cursor = cursor->next;
            free(temp);
            temp = cursor;
             
        }
    }

    return true;
}
