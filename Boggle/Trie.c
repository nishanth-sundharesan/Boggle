#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "types.h"
#include "Trie.h"

void addTrieNodes(char8_t *word, Trie* root)
{
	while (true)
	{
		if (*word == '\n' || *word == '\0')
		{
			root->hasWordEnded = true;
			break;
		}

		if (root->children == NULL)
		{
			Trie* node = createEmptyNode(*word);

			node->isChildNode = true;
			node->parent = root;

			root->children = node;
			root = node;
		}
		else
		{
			root = root->children;
			Trie* parentNode = root;

			if (root->character != *word)
			{
				while (root->next != NULL && root->character != *word)
				{
					root = root->next;
				}

				if (root->character != *word)
				{
					Trie* node = createEmptyNode(*word);

					node->isChildNode = false;
					node->parent = parentNode;

					root->next = node;
					root = node;
				}
			}
		}
		word++;
	}
}

Trie* createEmptyNode(char8_t letter)
{
	Trie* node = (Trie *)malloc(sizeof(Trie));
	assert(node != NULL);

	node->character = letter;
	node->children = NULL;
	node->next = NULL;
	node->hasWordEnded = false;
	node->hasWordPrinted = false;

	return node;
}

void createTrieRootNode(Trie** root)
{
	*root = createEmptyNode('\0');
	(*root)->isChildNode = true;
	(*root)->parent = NULL;
}

void printTrie(Trie* mainRoot)
{
	mainRoot = mainRoot->children;
	printf("%c\n", mainRoot->character);

	mainRoot = mainRoot->next;
	while (mainRoot != NULL)
	{
		printf("%c\n", mainRoot->character);
		mainRoot = mainRoot->next;
	}
}