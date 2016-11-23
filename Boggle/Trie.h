#include "types.h"

#ifndef TRIE
#define TRIE

struct TrieStruct
{	
	char8_t character;
	bool8_t hasWordEnded;
	bool8_t hasWordPrinted;
	bool8_t isChildNode;
	struct TrieStruct *next, *children, *parent;	
};

typedef struct TrieStruct Trie;

#endif

void createTrieRootNode(Trie** root);
void addTrieNodes(char8_t *word, Trie* root);
Trie* createEmptyNode(char8_t letter);
void deleteTrieNodes(Trie** root);