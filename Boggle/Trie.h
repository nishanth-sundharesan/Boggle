#include "types.h"
/*******************************************************
Consider the words: amy, and, emma, rob, roger
The graphical representation of the Trie data structure for the above mentioned words looks like.

			\0
			|
			a --------- e ----- r
			|           |       |
			m --- n     m       o
			|     |     |       |
			y     d     m       b ----- g
			            |               |
			            a               e
										|
										r
										
1. \0 node will be the Root node.
2. character = Each node will contain a character in it.
3. hasWordEnded = This will be set to true for the last letter of every word.
				  For example: The letter 'y' in the word amy will have the boolean 'hasWordEnded' set to true.
4. hasWordPrinted = This boolean will be set to true if the word has already printed. We will need this boolean such that we don't
					print the same word again while traversing upwards of the data structure.
5. isChildNode = This will be set to true if the node is a child node, false otherwise.
				 Consider the example 'amy' and 'and'. All the letters in the word 'amy' are child nodes.
				 However, for the word 'and'.
					a) a = child node
					b) n = not a child node
					c) d = child node
6. *next = This pointer will point to the next node or the siblings if it is available. Or else it will be set to NULL.
			Consider the example 'amy'
			a) a = *next will point to 'e'
			b) m = *next will point to 'n'
			c) y = *next will point to NULL
7. *children = This pointer will simply point to it's child node
			Consider the example 'amy'
			a) a = *children will point to 'm'
			b) m = *children will point to 'y'
			c) y = *children will point to NULL
8. *parent = This pointer will point to it's parent node. But it's a little tricky for the nodes that extend from *next pointer or for the sibling nodes.
			Consider the example 'amy'
			a) a = *parent will point to '\0' or the root node
			b) m = *parent will point to 'a'
			c) y = *parent will point to 'm'

			But for the example 'and'
			a) a = *parent will point to '\0' or the root node
			b) n = *parent will point to 'm'
			c) d = *parent will point to 'n'

A detailed explanation of the data structure is provided in the link https://www.cs.bu.edu/teaching/c/tree/trie/. But the data structure used in this program is modified for the given problem.
*******************************************************/
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
Trie* createTrieNode(char8_t letter);
void deleteTrieNodes(Trie** root);