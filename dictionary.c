/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

#define DICTIONARY_LENGTH 143091

trie dict;



unsigned int count = 0;
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    return search_word(&dict, word);
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{   
    for (int i = 0; i < SYMBOLS; i++)
    {
        dict.children[i] = NULL;
    }
    unsigned int counter = 0;
    char* word = malloc(sizeof(char) * LENGTH); 
    FILE* fp = fopen(dictionary, "r");
    while(fgets(word, LENGTH, fp) != NULL)
    {
        if  (search_word(&dict, word) == false)
            insert_word(&dict, word);
        counter++;
    }
    count = counter;
    if (size() == DICTIONARY_LENGTH)
        {
            free(word);
            return false;
        }
    fclose(fp);
    free(word);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    free_mem(&dict);
    return true;
}

bool search_word (trie* head, const char* word)
{
    struct trie* curr = head;
    int word_length = strlen(word);
    if (word[word_length - 1] == '\n')
        word_length--;
    char* current_word = malloc(sizeof(char) * word_length + 2);
    strcpy(current_word, word);
    for (int i = 0; i < word_length; i++)
    {
        if ((current_word[i] >= 'A') && (current_word[i] <= 'Z'))
            current_word[i] = current_word[i] + 'a' - 'A';
        if (current_word[i] == '\'')
            current_word[i] = 'a' + 26;
        if (curr->children[current_word[i] - 'a'] == NULL)
            {
                free(current_word);
                return false;
            }
        curr = curr->children[current_word[i] - 'a'];
    }
    if (curr->is_word == true)
        {
            free(current_word);
            return true;
        }        
    free(current_word);
    return false;  
}

struct trie* get_new_trie_node ()
{
    struct trie* new_node = malloc(sizeof(struct trie));
    new_node->is_word = false;

    for (int i = 0; i < SYMBOLS; i++)
        new_node->children[i] = NULL;
    return new_node;
}

void insert_word (trie* head, const char* word)
{
    struct trie* curr = head;
    const int word_length = strlen(word) - 1;
    char* current_word = malloc(sizeof(char) * (word_length + 2));
    strcpy(current_word, word);
    for (int i = 0; i < word_length; i++)
    {   
        if ((current_word[i] >= 'A') && (current_word[i] <= 'Z'))
            current_word[i] = current_word[i] + 'a' - 'A';
        if (current_word[i] == '\'')
            current_word[i] = 'a' + 26;
        if (curr->children[current_word[i] - 'a'] == 0x0)
            curr->children[current_word[i] - 'a'] = get_new_trie_node();
        curr = curr->children[current_word[i] - 'a'];
    }
    curr->is_word = true;
    free(current_word); 
}

void free_mem (trie* ptr)
{
    for (int i = 0; i < SYMBOLS; i++)
    {
        if (ptr->children[i] != NULL)
            free_mem(ptr->children[i]);
    }
    if (ptr != &dict)
        free(ptr);
}