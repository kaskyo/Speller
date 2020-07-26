/**
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 46
#define SYMBOLS 27

typedef struct trie
{
  // Маркер конца слова
  bool is_word;
  // Указатели на другие элементы
  struct trie * children [SYMBOLS];
} trie;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

bool search_word (trie* head,const char* word);
struct trie* get_new_trie_node ();
void insert_word (trie* head,const char* word);
void free_mem (trie* head);

#endif // DICTIONARY_H
