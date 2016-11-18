#include "types.h"

#ifndef TRIE
#define TRIE

struct TrieStruct
{
	char8_t character;
	struct TrieStruct *next, *children;
	bool8_t hasWordEnded;
};

//next is linked list

typedef struct TrieStruct Trie;

#endif

void CreateTrieRootNode(Trie** root);
void AddTrieNode(char8_t *word, Trie* root);
void PrintTrie(Trie* mainRoot);