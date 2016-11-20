#include "types.h"

#ifndef TRIE
#define TRIE

struct TrieStruct
{
	char8_t character;
	struct TrieStruct *next, *children, *parent;
	bool8_t hasWordEnded;
	bool8_t hasWordPrinted;
	bool8_t isChildNode;
};

//next is linked list

typedef struct TrieStruct Trie;

#endif

void createTrieRootNode(Trie** root);
void addTrieNodes(char8_t *word, Trie* root);
void printTrie(Trie* mainRoot);
Trie* createEmptyNode(char8_t letter);